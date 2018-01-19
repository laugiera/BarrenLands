//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_RENDERROCK_H
#define BARRENLANDS_RENDERROCK_H

#include "RenderObject.hpp"
/**
 * Class RenderRock
 * Corresponding to Procedural Rock Class
 * common to all rocks
 */
class RenderRock : public RenderObject{
public:
    RenderRock(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> _textures, Color *_color);
    void sendUniforms(const glm::mat4 &viewMatrix);

    void setColor(Color *_color){
        color->darken(10);
    }

};


#endif //BARRENLANDS_RENDERROCK_H
