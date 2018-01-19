//
// Created by natshez on 18/01/2018.
//

#include "RenderRock.hpp"
/**
 * Constructor
 * @param program
 * @param _textures
 * @param _color
 */
RenderRock::RenderRock(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> _textures, Color *_color): RenderObject(program,
        _textures, color){

}
/**
 * sendUniforms()
 * @param viewMatrix
 */
void RenderRock::sendUniforms(const glm::mat4 &viewMatrix){

}