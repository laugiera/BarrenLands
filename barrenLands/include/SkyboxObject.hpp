//
// Created by natshez on 17/01/2018.
//

#ifndef BARRENLANDS_SKYBOXOBJECT_CPP_H
#define BARRENLANDS_SKYBOXOBJECT_CPP_H

#include <ProceduralObject.hpp>
#include <RenderSkybox.h>

class SkyboxObject : public ProceduralObject {
public:
    SkyboxObject();
    ~SkyboxObject();

  /*  void generateVertices();
    void generateIndices();*/
    void createRenderObject(glcustom::GPUProgram *program);
    void draw(const glm::mat4 &viewMatrix);

    void setTextures(glcustom::Texture * textures);
};

#endif //BARRENLANDS_SKYBOXOBJECT_CPP_H
