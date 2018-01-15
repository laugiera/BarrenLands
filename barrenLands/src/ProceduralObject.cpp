//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/ProceduralObject.hpp"

ProceduralObject::ProceduralObject() : renderObject(nullptr) {
    generateVertices();
    generateIndices();
}

ProceduralObject::~ProceduralObject() {
 delete renderObject;
}

void ProceduralObject::generateVertices() {
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,1,-1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,1,-1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-1,-1,-1), glm::vec3(0,1,0), glm::vec2(1,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(1,-1,-1), glm::vec3(0,1,0), glm::vec2(1,1)));

}

void ProceduralObject::generateIndices() {
    int _indices[] =
            {
                    0,1,2,
                    0,2,3,
                    0,4,5,
                    5,2,0,
                    1,5,6,
                    1,6,2,
                    2,6,7,
                    2,7,3,
                    3,7,4,
                    3,4,0,
                    4,5,6,
                    4,6,7
            };

    indices = std::vector<int>(_indices, _indices + sizeof(_indices) / sizeof(int));

}

void ProceduralObject::generateNormals() {

}

void ProceduralObject::createRenderObject(glcustom::GPUProgram *program) {
    renderObject = new RenderObject(program);
    renderObject->fillData(vertices, indices);
}

void ProceduralObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    renderObject->transform(glm::vec3(0), 0, glm::vec3(0,1,0), glm::vec3(1));
    renderObject->render(viewMatrix);
}

