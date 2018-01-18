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

ProceduralMap::ProceduralMap(NoiseManager *noise) : ProceduralObject(){
    generateVertices(noise);
    generateIndices();
    generateNormals();
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
}

glimac::ShapeVertex ProceduralMap::getVertices(int i, int j){
    return vertices[i*(Tools::nbSub+1)+j];
}

std::vector<glimac::ShapeVertex> ProceduralMap::getVerticesTab(){
    return vertices;
}

void ProceduralMap::setTextures(const std::vector<glcustom::Texture *> &textures) {
    ProceduralMap::textures = textures;
}


void ProceduralMap::createBiomes(glcustom::Texture * moisture) {
    //utiliser un loader
    for(int i = 0; i<8 ; i++){
        biomes.push_back(new ProceduralBiome());
    }
    /*
    for( glimac::ShapeVertex & vertex : vertices ){
        if (vertex.position.y < 0.25){
            if (moisture < 2.f/6.f){
                biomes[0]->addVertex(&vertex); // desert
            } else {
                biomes[1]->addVertex(&vertex); //herbe
            }

        } else if (vertex.position.y < 0.5){
            if (moisture < 2.f/6.f){
                biomes[3]->addVertex(&vertex); //craquelé
            } else if (moisture < 5.f/6.f){
                biomes[4]->addVertex(&vertex); //savane
            } else {
                biomes[1]->addVertex(&vertex); //herbe
            }

        } else if (vertex.position.y < 0.75){
            if (moisture < 2.f/6.f){
                biomes[5]->addVertex(&vertex); //roche
            } else if (moisture < 4.f/6.f){
                biomes[6]->addVertex(&vertex); //toundra
            } else {
                biomes[7]->addVertex(&vertex); //toundra herbe
            }
        } else {
            if (moisture < 2.f/6.f){
                biomes[5]->addVertex(&vertex); //roche
            } else if (moisture < 3.f/6.f){
                biomes[6]->addVertex(&vertex); //toundra
            } else {
                biomes[8]->addVertex(&vertex); //toundra neige
            }

        }

    }
     */
}

std::vector<glcustom::Texture *> ProceduralMap::chooseTextures(TextureManager *textureManager) {
    std::vector<glcustom::Texture *> textures;
    textures.push_back(textureManager->getRandomTexture("moisture"));
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
