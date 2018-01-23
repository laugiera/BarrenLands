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
    //common vertices
    glm::vec3 highRightFront = glm::vec3(1,1,1);
    glm::vec3 highLeftFront = glm::vec3(-1,1,1);
    glm::vec3 bottomLeftFront = glm::vec3(-1,-1,1);
    glm::vec3 bottomRightFront = glm::vec3(1,-1,1);

    glm::vec3 highRightBack = glm::vec3(1,1,-1);
    glm::vec3 highLeftBack = glm::vec3(-1,1,-1);
    glm::vec3 bottomLeftBack = glm::vec3(-1,-1,-1);
    glm::vec3 bottomRightBack = glm::vec3(1,-1,-1);

    //FACE AVANT
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(0,0,1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftFront, glm::vec3(0,0,1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftFront, glm::vec3(0,0,1), glm::vec2(1,0)));

    vertices.push_back(glimac::ShapeVertex(bottomRightFront, glm::vec3(0,0,1), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftFront, glm::vec3(0,0,1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(0,0,1), glm::vec2(0,0)));

    //Face ARRIERE
    vertices.push_back(glimac::ShapeVertex(highRightBack, glm::vec3(0,0,-1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftBack, glm::vec3(0,0,-1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(0,0,-1), glm::vec2(1,0)));

    vertices.push_back(glimac::ShapeVertex(bottomRightBack, glm::vec3(0,0,-1), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(0,0,-1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highRightBack, glm::vec3(0,0,-1), glm::vec2(0,0)));

    //FACE GAUCHE
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highRightBack, glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightBack, glm::vec3(-1,0,0), glm::vec2(0,1)));

    vertices.push_back(glimac::ShapeVertex(bottomRightFront, glm::vec3(-1,0,0), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightBack, glm::vec3(-1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(-1,0,0), glm::vec2(0,0)));

    //FACE DROITE
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftFront, glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftFront, glm::vec3(1,0,0), glm::vec2(0,1)));

    vertices.push_back(glimac::ShapeVertex(highLeftBack, glm::vec3(1,0,0), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftFront, glm::vec3(1,0,0), glm::vec2(0,1)));

    //FACE HAUT
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftFront, glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftBack, glm::vec3(0,1,0), glm::vec2(0,1)));

    vertices.push_back(glimac::ShapeVertex(highRightBack, glm::vec3(0,1,0), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(highRightFront, glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(highLeftBack, glm::vec3(0,1,0), glm::vec2(0,1)));

    //FACE BAS
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightBack, glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightFront, glm::vec3(0,-1,0), glm::vec2(0,1)));

    vertices.push_back(glimac::ShapeVertex(bottomLeftFront, glm::vec3(0,-1,0), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(bottomLeftBack, glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(bottomRightFront, glm::vec3(0,-1,0), glm::vec2(0,1)));

    //subdivision
    std::vector<glimac::ShapeVertex> _vertices;
    std::vector<glimac::ShapeVertex>::iterator it = vertices.begin();

    ProceduralObject::subdivideObject(vertices);

    //procedural transformation
    for (int k = 0; k < vertices.size(); ++k) {
        float disturb = NoiseManager::getInstance().getVerticesDisturbation(vertices[k].position.x,vertices[k].position.y,vertices[k].position.z);
        vertices[k].position.x += disturb;
        std::cout << disturb << std::endl;
    }

}
void SharpRock::generateIndices(){
    indices.clear();
}
void SharpRock::generateNormals(){}

