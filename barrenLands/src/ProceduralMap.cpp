//
// Created by Lou Landry on 16/01/2018.
//

#include <NoiseManager.hpp>
#include <ProgramManager.hpp>
#include <TextureManager.hpp>
#include "ProceduralMap.hpp"

/**BIOMES COLORS**/
Color *ProceduralMap::sand = new Color(255.f/255.f, 255.f/255.f, 153.f/255.f);
Color *ProceduralMap::grass = new Color(153.f/255.f, 204.f/255.f, 0.f/255.f);

void ProceduralMap::generateVertices(NoiseManager *noise) {
    vertices.clear();
    int width = Tools::width;
    int i, j;
    //test génération bruit
    float** terrain = noise->getElevationMap(Tools::nbSub+1, Tools::nbSub+1);
    for(i=0; i<Tools::nbSub+1; ++i){
        for(j=0; j<Tools::nbSub+1; j++){
            vertices.push_back(glimac::ShapeVertex(
                    glm::vec3(-width*Tools::nbSub/2.0+j*width, terrain[i][j], -width*Tools::nbSub/2.0+i*width),
                    glm::vec3(0, 0, 0),
                    glm::vec2(i, j)
            ));
        }
    }
}

void ProceduralMap::generateIndices() {
    indices.clear();
    int i, j;
    for(i=0; i<Tools::nbSub; ++i){
        for(j=0; j<Tools::nbSub; ++j){
            indices.push_back(i*Tools::nbSub + j + i); //0
            indices.push_back(i*Tools::nbSub + j + 1 + i); //1
            indices.push_back((i+1)*Tools::nbSub + j + 1 + i);  //2
            indices.push_back(i*Tools::nbSub + j + 1 + i); //1
            indices.push_back((i+1)*Tools::nbSub + j + 1 + i); //2
            indices.push_back((i+1)*Tools::nbSub + j + 2 + i); //3
        }
    }

}

ProceduralMap::ProceduralMap(NoiseManager *noise) : ProceduralObject(), sea(nullptr){
    generateVertices(noise);
    generateIndices();
    generateNormals();
    createMoistureMap();
    createBiomes();
}

void ProceduralMap::generateNormals() {
    int i, j;
    glm::vec3 dir1;
    glm::vec3 dir2;
    glm::vec3 norm;

    for(i=0; i < Tools::nbSub*Tools::nbSub*2; ++i){
        if(i%2 == 0){
            dir1 = vertices[indices[3*i+1]].position - vertices[indices[3*i]].position;
            dir2 = vertices[indices[3*i+2]].position - vertices[indices[3*i]].position;
        }
        else{
            dir1 = vertices[indices[3*i]].position - vertices[indices[3*i+1]].position;
            dir2 = vertices[indices[3*i+2]].position - vertices[indices[3*i+1]].position;
        }
        norm = glm::normalize(glm::cross(dir2, dir1));
        vertices[indices[3*i]].normal += norm;
        vertices[indices[3*i+1]].normal += norm;
        vertices[indices[3*i+2]].normal += norm;


    }

    for(i=0; i < vertices.size(); ++i){
        vertices[indices[i]].normal = glm::normalize(vertices[indices[i]].normal);
    }
}

void ProceduralMap::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    for(ProceduralBiome * b : biomes){
        b->createRenderObject(programManager, textureManager);
    }
    renderObject = new RenderMap(programManager->getLightProgram(), chooseTextures(textureManager));
    renderObject->fillData(vertices, indices);
    createRenderSea(programManager, textureManager);
}

glimac::ShapeVertex ProceduralMap::getVertices(int i, int j){
    return vertices[i*(Tools::nbSub+1)+j];
}

std::vector<glimac::ShapeVertex> ProceduralMap::getVerticesTab(){
    return vertices;
}

void ProceduralMap::createBiomes() {
    //utiliser un loader
    for(int i = 0; i<8 ; i++){
        biomes.push_back(new ProceduralBiome());
    }
    for(int i = 0; i<vertices.size(); i++){
        if (vertices[i].position.y < 0.25){
            if (moistureMap[i] < 2.f/6.f){
                biomes[0]->addVertex(&vertices[i]); // desert
                biomes[0]->setColor(ProceduralMap::sand);
            } else {
                biomes[1]->addVertex(&vertices[i]); //herbe
                biomes[1]->setColor(ProceduralMap::grass);
            }

        } else if (vertices[i].position.y < 0.5){
            if (moistureMap[i] < 2.f/6.f){
                biomes[3]->addVertex(&vertices[i]); //craquelé
            } else if (moistureMap[i] < 5.f/6.f){
                biomes[4]->addVertex(&vertices[i]); //savane
            } else {
                biomes[1]->addVertex(&vertices[i]); //herbe
            }

        } else if (vertices[i].position.y < 0.75){
            if (moistureMap[i] < 2.f/6.f){
                biomes[5]->addVertex(&vertices[i]); //roche
            } else if (moistureMap[i] < 4.f/6.f){
                biomes[6]->addVertex(&vertices[i]); //toundra
            } else {
                biomes[7]->addVertex(&vertices[i]); //toundra herbe
            }
        } else {
            if (moistureMap[i] < 2.f/6.f){
                biomes[5]->addVertex(&vertices[i]); //roche
            } else if (moistureMap[i] < 3.f/6.f){
                biomes[6]->addVertex(&vertices[i]); //toundra
            } else {
                biomes[2]->addVertex(&vertices[i]); //toundra neige
            }

        }

    }
}

std::vector<glcustom::Texture *> ProceduralMap::chooseTextures(TextureManager *textureManager) {
    glcustom::Texture * moistureTexture = new glcustom::Texture(Tools::nbSub +1, Tools::nbSub +1, moistureMap.data(), GL_RED);
    std::vector<glcustom::Texture *> textures;
    textures.push_back(moistureTexture);
    textures.push_back(textureManager->getRandomTexture("sand"));
    textures.push_back(textureManager->getRandomTexture("rock"));
    return textures;

    /* plus tard
    Récupérer les textures depuis les biomes
    for(int i = 0; i<8 ; i++){
        //textures.push_back(biomes[i]->getTexture());

    }
    return textures;
     */
}

ProceduralMap::~ProceduralMap() {
    /*
    delete proceduralObject;
    delete bio
     */
}

void ProceduralMap::createMoistureMap() {
    float ** humidite = NoiseManager::getInstance().getElevationMap(Tools::nbSub +1, Tools::nbSub +1);
    for(int i = 0; i < Tools::nbSub +1; i++){
        for(int j = 0 ; j < Tools::nbSub +1; j++){
            moistureMap.push_back(humidite[i][j]);
        }
    }
}

void ProceduralMap::createRenderSea(ProgramManager *programManager, TextureManager *textureManager) {
    std::vector<glimac::ShapeVertex> _vertices;
    _vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,0,-1), glm::vec3(0,1,0), glm::vec2(0,0)));
    _vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,0,1), glm::vec3(0,1,0), glm::vec2(1,0)));
    _vertices.push_back(glimac::ShapeVertex(glm::vec3(1,0,1), glm::vec3(0,1,0), glm::vec2(1,1)));
    _vertices.push_back(glimac::ShapeVertex(glm::vec3(1,0,-1), glm::vec3(0,1,0), glm::vec2(0,1)));

    std::vector<uint32_t> indices = {0,1,2,2,0,3};

    sea = new RenderObject(programManager->getTestProgram(), std::vector<glcustom::Texture*>(1, textureManager->getRandomTexture("sand")));
    sea->fillData(vertices, indices);
}

void ProceduralMap::draw(const glm::mat4 &viewMatrix) {
    sea->transform(glm::vec3(0), 0, glm::vec3(0,1,0), glm::vec3(100,100,100));
    sea->render(viewMatrix);
    ProceduralObject::draw(viewMatrix);
}

