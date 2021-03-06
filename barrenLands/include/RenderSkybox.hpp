//
// Created by natshez on 17/01/2018.
//

#ifndef BARRENLANDS_RENDERSKYBOX_H
#define BARRENLANDS_RENDERSKYBOX_H

#include "RenderObject.hpp"
/**
 * Class RenderSkybox
 * Corresponding to SkyboxObject
 */
class RenderSkybox : public RenderObject{
public :

    RenderSkybox() = default;

    RenderSkybox(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> texture);
    ~RenderSkybox();
    void bindTextures();
    void debindTextures();
    virtual void sendUniforms(const glm::mat4 &viewMatrix, const glm::vec4 &sunDirMatrix);
    void render(const glm::mat4 &viewMatrix, const glm::vec4 &sunDirMatrix);
};


#endif //BARRENLANDS_RENDERSKYBOX_H

