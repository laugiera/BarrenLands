/*//
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
}

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
}*/
