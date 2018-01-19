//
// Created by Lou Landry on 16/01/2018.
//

#include <NoiseManager.hpp>
#include <ProgramManager.hpp>
#include <TextureManager.hpp>
#include "ProceduralMap.hpp"


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
    createSea();
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
    renderObject = new RenderMap(programManager->getMapProgram(), chooseTextures(textureManager));
    renderObject->fillData(vertices, indices);
    sea->createRenderObject(programManager, textureManager);
}

glimac::ShapeVertex ProceduralMap::getVertices(int i, int j){
    return vertices[i*(Tools::nbSub+1)+j];
}

std::vector<glimac::ShapeVertex> ProceduralMap::getVerticesTab(){
    return vertices;
}

void ProceduralMap::createBiomes() {
    //utiliser un loader
    //RenderMap::biomesNumber = 6;
    for(int i = 0; i<RenderMap::biomesNumber ; i++){
        biomes.push_back(new ProceduralBiome());
    }
    for(int i = 0; i<vertices.size(); i++){
        if (vertices[i].position.y < 0.25){
            if (moistureMap[i] < 2.f/6.f){
                biomes[0]->addVertex(&vertices[i]); // desert
                biomes[0]->setColor(RenderMap::sand);
            } else {
                biomes[1]->addVertex(&vertices[i]); //herbe
                biomes[1]->setColor(RenderMap::grass);
            }

        } else if (vertices[i].position.y < 0.5){
            if (moistureMap[i] < 2.f/6.f){
                biomes[2]->addVertex(&vertices[i]); //savane
                biomes[2]->setColor(RenderMap::savannah);
            } else {
                biomes[1]->addVertex(&vertices[i]); //herbe
            }

        } else if (vertices[i].position.y < 0.75){
            if (moistureMap[i] < 2.f/6.f){
                biomes[3]->addVertex(&vertices[i]); //roche
                biomes[3]->setColor(RenderMap::rock);
            } else if (moistureMap[i] < 4.f/6.f){
                biomes[4]->addVertex(&vertices[i]); //toundra
                biomes[4]->setColor(RenderMap::toundra);
            }
        } else {
            if (moistureMap[i] < 2.f/6.f){
                biomes[3]->addVertex(&vertices[i]); //roche
            } else if (moistureMap[i] < 3.f/6.f){
                biomes[4]->addVertex(&vertices[i]); //toundra
            } else {
                biomes[5]->addVertex(&vertices[i]); //toundra neige
                biomes[5]->setColor(RenderMap::snow);
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

    delete sea;
    delete[] biomes.data();
}

void ProceduralMap::createMoistureMap() {
    float ** humidite = NoiseManager::getInstance().getElevationMap(Tools::nbSub +1, Tools::nbSub +1);
    for(int i = 0; i < Tools::nbSub +1; i++){
        for(int j = 0 ; j < Tools::nbSub +1; j++){
            moistureMap.push_back(humidite[i][j]);
        }
    }
}

void ProceduralMap::createSea() {
    sea = new ProceduralSea();
}

void ProceduralMap::draw(const glm::mat4 &viewMatrix) {
    sea->draw(viewMatrix);
    ProceduralObject::draw(viewMatrix); //draw the map vertex
    //draw the elements
    for(ProceduralObject * biome : biomes){
        biome->draw(viewMatrix);
    }
}

