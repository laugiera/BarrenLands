//
// Created by natshez on 17/01/2018.
//

#include "RenderSkybox.hpp"

/**
 * Destructor
 */
RenderSkybox::~RenderSkybox() {
/*    for(glcustom::Texture * texture : textures){
        delete texture;
    }*/ //already done in super class !!!!!
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
    program->sendUniformVec3("uResolution",glm::vec3(Tools::windowWidth, Tools::windowHeight, 1.0));
    program->sendUniform1f("uTime", (float)Tools::time);
}

/**
* render()
* render the object by using it's own GPU Program, sending it's own uniforms and binding it's own textures
* @param viewMatrix
*/
void RenderSkybox::render(const glm::mat4 &viewMatrix, const  std::vector<Instance*> &instances) {
    program->use();
    bindTextures();
    vao.bind();
    sendUniforms(viewMatrix);
    if(indices.empty()){
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    } else {
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    vao.debind();
    debindTextures();

}




