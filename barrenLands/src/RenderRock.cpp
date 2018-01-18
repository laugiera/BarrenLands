//
// Created by natshez on 18/01/2018.
//

#include "RenderRock.h"

RenderRock::RenderRock(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> _textures, Color *_color): RenderObject(program,
        _textures, color){

}
void RenderRock::sendUniforms(const glm::mat4 &viewMatrix){

}