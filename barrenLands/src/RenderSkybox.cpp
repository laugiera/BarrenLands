//
// Created by natshez on 17/01/2018.
//

#include "RenderSkybox.h"


RenderSkybox::~RenderSkybox() {
    for(glcustom::Texture * texture : textures){
        delete texture;
    }
}

void RenderSkybox::render(const glm::mat4 &viewMatrix) {
    program->use();
    //proj matrix à externaliser
    glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), Tools::windowWidth/Tools::windowHeight, 0.1f, 1500.f);
    modelMatrix = glm::mat4(1.0);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;

    glm::mat4 modelViewProjMatrix = projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));


    program->sendUniformMat4("uMVP", modelViewProjMatrix);
    program->sendUniformMat4("uMV", modelViewMatrix);

    bindTextures();

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.debind();

    debindTextures();

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
