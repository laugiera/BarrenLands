//
// Created by natshez on 18/01/2018.
//

#include "SharpRock.hpp"

SharpRock::SharpRock() : ProceduralRock(){
    generateIndices();
    generateVertices();
}
SharpRock::~SharpRock(){
}
void SharpRock::generateVertices(){
    vertices.clear();
    float* disturb = NoiseManager::getInstance().getVerticesDisturbation(8);
    //common vertices
    glm::vec3 highRightFront = glm::vec3(1,1,1)+ disturb[1];
    glm::vec3 highLeftFront = glm::vec3(-1,1,1)+ disturb[2];
    glm::vec3 bottomLeftFront = glm::vec3(-1,-1,1)+ disturb[3];
    glm::vec3 bottomRightFront = glm::vec3(1,-1,1)+ disturb[4];

    glm::vec3 highRightBack = glm::vec3(1,1,-1)+ disturb[5];
    glm::vec3 highLeftBack = glm::vec3(-1,1,-1)+ disturb[6];
    glm::vec3 bottomLeftBack = glm::vec3(-1,-1,-1)+ disturb[7];
    glm::vec3 bottomRightBack = glm::vec3(1,-1,-1)+ disturb[0];

    //FACE AVANT
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(0,0,1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftFront, glm::vec3(0,0,1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftFront, glm::vec3(0,0,1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightFront, glm::vec3(0,0,1), glm::vec2(1,1)));
    //Face ARRIERE
    vertices.push_back(glimac::ShapeVertex(highRightBack, glm::vec3(0,0,-1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftBack, glm::vec3(0,0,-1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(0,0,-1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightBack, glm::vec3(0,0,-1), glm::vec2(1,1)));
    //FACE GAUCHE
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highRightBack, glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightBack, glm::vec3(-1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(bottomRightFront, glm::vec3(-1,0,0), glm::vec2(1,0)));
    //FACE DROITE
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftFront, glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftFront, glm::vec3(1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(highLeftBack, glm::vec3(1,0,0), glm::vec2(1,0)));
    //FACE HAUT
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftFront, glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftBack, glm::vec3(0,1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(highRightBack, glm::vec3(0,1,0), glm::vec2(1,0)));
    //FACE BAS
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightBack, glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightFront, glm::vec3(0,-1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftFront, glm::vec3(0,-1,0), glm::vec2(1,0)));

}
void SharpRock::generateIndices(){
    ProceduralObject::generateIndices();
}
void SharpRock::generateNormals(){}

