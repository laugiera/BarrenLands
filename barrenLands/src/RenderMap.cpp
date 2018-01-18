//
// Created by Lou Landry on 16/01/2018.
//

#include "RenderMap.hpp"

RenderMap::RenderMap(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> _textures) : RenderObject(program,
                                                                                                              _textures) {
}

void RenderMap::render(const glm::mat4 &viewMatrix) {
    RenderObject::render(viewMatrix);
}