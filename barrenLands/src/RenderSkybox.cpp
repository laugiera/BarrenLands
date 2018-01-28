//
// Created by natshez on 17/01/2018.
//

#include "RenderSkybox.hpp"

/**
 * Destructor
 */
RenderSkybox::~RenderSkybox() {
    for(glcustom::Texture * texture : textures){
        delete texture;
    }
}
/**
 * Constructor
 * @param program
 * @param textures
 */
RenderSkybox::RenderSkybox(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> textures)
        : RenderObject(program, textures){}
/**
 * bindTextures()
 * bind a GL_TEXTURE_CUBE_MAP texture
 */
void RenderSkybox::bindTextures() {
    int textureUnit = GL_TEXTURE0;
    textures[0]->bind(GL_TEXTURE_CUBE_MAP, textureUnit);
    program->sendUniformTextureUnit("uTexture" + std::to_string(0), 0);

}
/**
 * debindTextures()
 */
void RenderSkybox::debindTextures() {
    textures[0]->debind(GL_TEXTURE_CUBE_MAP);
}
/**
 * sendUniforms()
 * @param viewMatrix
 */
void RenderSkybox::sendUniforms(const glm::mat4 &viewMatrix) {
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    glm::mat4 modelViewProjMatrix = Tools::projMatrix * modelViewMatrix;
    glm::mat4 normals = glm::transpose(glm::inverse(modelViewMatrix));
    program->sendUniformMat4("uMVP", modelViewProjMatrix);
    program->sendUniformMat4("uMV", modelViewMatrix);
}




