//
// Created by natshez on 17/01/2018.
//

#ifndef BARRENLANDS_SKYBOXOBJECT_CPP_H
#define BARRENLANDS_SKYBOXOBJECT_CPP_H

#include <ProceduralObject.hpp>
#include <RenderSkybox.hpp>
/**
 * Class SkyboxObject
 */
class SkyboxObject : public ProceduralObject {
public:
    SkyboxObject();
    ~SkyboxObject();

    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);
    void draw(const glm::mat4 &viewMatrix, const glm::vec4 &sunDirMatrix);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

private:
    RenderSkybox* renderObject;

};

#endif //BARRENLANDS_SKYBOXOBJECT_CPP_H
