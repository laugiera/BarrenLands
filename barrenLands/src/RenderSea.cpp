//
// Created by natshez on 01/02/2018.
//

#include "RenderSea.hpp"

/**
* render()
* render the object by using it's own GPU Program, sending it's own uniforms and binding it's own textures
* @param viewMatrix
*/
void RenderSea::render(const glm::mat4 &viewMatrix, const  std::vector<Instance*> &instances) {
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

RenderSea::RenderSea(glcustom::GPUProgram *program, const std::vector<glcustom::Texture *> &texture, Color *_color)
        : RenderObject(program, texture, _color) {}
