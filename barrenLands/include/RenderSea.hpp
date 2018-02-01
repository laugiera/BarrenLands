//
// Created by natshez on 01/02/2018.
//

#ifndef BARRENLANDS_RENDERSEA_H
#define BARRENLANDS_RENDERSEA_H
#include "RenderObject.hpp"

class RenderSea  : public RenderObject{
public:
    RenderSea(glcustom::GPUProgram *program, const std::vector<glcustom::Texture *> &texture, Color *_color);

private:
    void render(const glm::mat4 &viewMatrix, const  std::vector<Instance*> &instances);

};


#endif //BARRENLANDS_RENDERSEA_H
