//
// Created by natshez on 17/01/2018.
//

#include "RenderSkybox.hpp"


RenderSkybox::~RenderSkybox() {
    for(glcustom::Texture * texture : textures){
        delete texture;
    }
}

RenderSkybox::RenderSkybox(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> textures)
        : RenderObject(program, textures){}



void RenderSkybox::bindTextures() {
    int textureUnit = GL_TEXTURE0;
    textures[0]->bind(GL_TEXTURE_CUBE_MAP, textureUnit);
    program->sendUniformTextureUnit("uTexture" + std::to_string(0), 0);

}

void RenderSkybox::debindTextures() {
    textures[0]->debind(GL_TEXTURE_CUBE_MAP);
}

void RenderSkybox::sendUniforms(const glm::mat4 &viewMatrix) {
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), Tools::windowWidth/Tools::windowHeight, 0.1f, 1500.f);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));
    program->sendUniformMat4("uMVP", modelViewProjMatrix);
    program->sendUniformMat4("uMV", modelViewMatrix);
}


