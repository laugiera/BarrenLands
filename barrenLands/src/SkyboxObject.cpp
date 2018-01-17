//
// Created by natshez on 17/01/2018.
//

//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/SkyboxObject.hpp"

SkyboxObject::SkyboxObject() : ProceduralObject() {
    generateVertices();
    generateIndices();
}

SkyboxObject::~SkyboxObject() {
    delete renderObject;
    for(glcustom::Texture* texture : textures){
        delete texture;
    }
}

/*void SkyboxObject::generateVertices() {
    vertices.clear();

    //FACE AVANT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,10,10), glm::vec3(0,0,1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,10,10), glm::vec3(0,0,1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,-10,10), glm::vec3(0,0,1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,-10,10), glm::vec3(0,0,1), glm::vec2(1,1)));
    //Face ARRIERE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,10,-10), glm::vec3(0,0,-1), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,10,-10), glm::vec3(0,0,-1), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,-10,-10), glm::vec3(0,0,-1), glm::vec2(1,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,-10,-10), glm::vec3(0,0,-1), glm::vec2(1,1)));
    //FACE GAUCHE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,10,10), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,10,-10), glm::vec3(-1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,-10,-10), glm::vec3(-1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,-10,10), glm::vec3(-1,0,0), glm::vec2(1,0)));
    //FACE DROITE
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,-10,-10), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,-10,10), glm::vec3(1,0,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,10,10), glm::vec3(1,0,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,10,-10), glm::vec3(1,0,0), glm::vec2(1,0)));
    //FACE HAUT
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,10,10), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,10,10), glm::vec3(0,1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,10,-10), glm::vec3(0,1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,10,-10), glm::vec3(0,1,0), glm::vec2(1,0)));
    //FACE BAS
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,-10,-10), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,-10,-10), glm::vec3(0,-1,0), glm::vec2(0,0)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(10,-10,10), glm::vec3(0,-1,0), glm::vec2(0,1)));
    vertices.push_back(glimac::ShapeVertex(glm::vec3(-10,-10,10), glm::vec3(0,-1,0), glm::vec2(1,0)));
}

void SkyboxObject::generateIndices() {
    indices.clear();
    uint32_t _indices[] =
            {
                    0,1,2,
                    0,2,3,
                    4,5,6,
                    4,6,7,
                    8,9,10,
                    8,10,11,
                    12,13,14,
                    12,14,15,
                    16,17,18,
                    16,18,19,
                    20,21,22,
                    20,22,23
            };

    indices = std::vector<uint32_t>(_indices, _indices + sizeof(_indices) / sizeof(uint32_t));
    //indices = std::vector<uint32_t>();

}*/

void SkyboxObject::createRenderObject(glcustom::GPUProgram *program) {
    renderObject = new RenderSkybox(program, textures);
    renderObject->fillData(vertices, indices);
}

void SkyboxObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    renderObject->transform(glm::vec3(0), 0, glm::vec3(0,1,0), glm::vec3(10,10,10));
    renderObject->render(viewMatrix);
}

void SkyboxObject::setTextures(glcustom::Texture * textures) {
    ProceduralObject::textures.push_back(textures);
}
