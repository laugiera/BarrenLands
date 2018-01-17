//
// Created by Lou Landry on 16/01/2018.
//

#ifndef BARRENLANDS_RENDERMAP_HPP
#define BARRENLANDS_RENDERMAP_HPP

#include "RenderObject.hpp"

class RenderMap : public RenderObject{
public:
    RenderMap(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> textures);
    void render(const glm::mat4 & viewMatrix);
};


#endif //BARRENLANDS_RENDERMAP_HPP
