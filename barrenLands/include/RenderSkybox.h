//
// Created by natshez on 17/01/2018.
//

#ifndef BARRENLANDS_RENDERSKYBOX_H
#define BARRENLANDS_RENDERSKYBOX_H

#include "RenderObject.hpp"

class RenderSkybox : public RenderObject{
public :

    RenderSkybox() = default;

    RenderSkybox(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> texture);
    ~RenderSkybox();
    void render(const glm::mat4 &viewMatrix);
    void bindTextures();
    void debindTextures();
};


#endif //BARRENLANDS_RENDERSKYBOX_H
