//
// Created by natshez on 18/01/2018.
//

#include "RenderRock.h"

RenderRock::RenderRock(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> _textures): RenderObject(program,
        _textures){

}
void RenderRock::sendUniforms(const glm::mat4 &viewMatrix){

}