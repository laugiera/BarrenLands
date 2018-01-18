#include <GPUProgram.hpp>

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
}

void SkyboxObject::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    renderObject = new RenderSkybox(programManager->getSkyboxProgram(), chooseTextures(textureManager));
    renderObject->fillData(vertices, indices);
}

std::vector<glcustom::Texture *> SkyboxObject::chooseTextures(TextureManager *textureManager) {
    std::vector<glcustom::Texture *> textures;
    textures.push_back(textureManager->getRandomTexture("skybox"));
    return textures;
}

void SkyboxObject::draw(const glm::mat4 &viewMatrix) {
    //transformer selon la position, rotation, scale de l'objet
    renderObject->transform(glm::vec3(0,0,-5), 0, glm::vec3(0,1,0), glm::vec3(100,100,100));
    renderObject->render(viewMatrix);
}


