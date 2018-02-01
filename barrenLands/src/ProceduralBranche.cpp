#include "ProceduralBranche.hpp"
#include "NoiseManager.hpp"
/** Constructor and destructor**/

ProceduralBranche::ProceduralBranche(): ProceduralObject(){
    vertices.clear();
    indices.clear();

    //Initialisation
    height = 3*NoiseManager::getInstance().getRandomFloat() +3;
    radius1 = 0.2*NoiseManager::getInstance().getRandomFloat()+0.1;
    radius2 = 0.1*NoiseManager::getInstance().getRandomFloat()+0.05;
    nbrSub = 6*NoiseManager::getInstance().getRandomFloat()+4;
    generateVertices();
    generateNormals();
}

ProceduralBranche::~ProceduralBranche() {}

void ProceduralBranche::generateVertices(){
    int i;
    //Triangles de la face du bas
    for(i=0; i<nbrSub; ++i){
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x, position.y, position.z),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*i*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
    }

    //Triangles de la face du haut
    for(i=0; i<nbrSub; ++i){
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x, position.y+height, position.z),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*i*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
    }

    //Triangle du cylindre, par 2
    for(i=0; i<nbrSub; ++i){
        //Triangle du Haut
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*i*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*i*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        //Triangle du Bas
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*i*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*i*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius2*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y+height,position.z + radius2*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,1,0),
                                               glm::vec2(0,0)));
        vertices.push_back(glimac::ShapeVertex(glm::vec3(position.x + radius1*cos(2*(i+1)*glm::pi<float>()/nbrSub),position.y,position.z + radius1*sin(2*(i+1)*glm::pi<float>()/nbrSub)),
                                               glm::vec3(0,-1,0),
                                               glm::vec2(0,0)));

    }

}

void ProceduralBranche::generateNormals() {
    for(int i = 0; i< vertices.size(); i += 3){
        glm::vec3 dir1 = vertices[i+1].position - vertices[i].position;
        glm::vec3 dir2 = vertices[i+2].position - vertices[i+1].position;
        glm::vec3 norm = glm::normalize(glm::cross(dir1, dir2));
        vertices[i].normal = norm;
        vertices[i+1].normal = norm;
        vertices[i+2].normal = norm;
    }
}

glm::mat4 ProceduralBranche::getRandomRotation() {
    return glm::rotate(glm::mat4(1.f), glm::radians(180*NoiseManager::getInstance().getRandomFloat()), glm::vec3(0,1,0));
}

glm::mat4 ProceduralBranche::getRandomScale() {
    return glm::scale(glm::mat4(1.f), glm::vec3(0.3 + 0.1*NoiseManager::getInstance().getRandomFloat(),0.3 + 0.3*abs(NoiseManager::getInstance().getRandomFloat()),0.3+ 0.1*NoiseManager::getInstance().getRandomFloat()));
}

/**
 * Adds a instance of an object
 * Adds its position and color to the positions and colors attributs after having modified them
 * @param position
 * @param biomeColor
 */
void ProceduralBranche::addInstance(const glm::vec3 &position, const Color &biomeColor, glm::mat4 scale) {
    Color trueColor = chooseColor(biomeColor);
    glm::mat4 transfo(1.f);
    transfo =  scale * getRandomRotation() * transfo;
    instances.push_back(new Instance(transfo, position,trueColor));
}
