//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALOBJECT_HPP
#define BARRENLANDS_PROCEDURALOBJECT_HPP

#include "glimac/common.hpp"
#include <vector>
#include "RenderObject.hpp"
#include "glimac/Sphere.hpp"


class ProceduralObject {
public:
    ProceduralObject();

    virtual ~ProceduralObject();

    virtual void generateVertices();
    virtual void generateIndices();
    void generateNormals();
    virtual void createRenderObject(glcustom::GPUProgram *program);
    void draw(const glm::mat4 &viewMatrix);

    void setTextures(const std::vector<glcustom::Texture *> &textures);

//private:
    std::vector<glimac::ShapeVertex> vertices;
    std::vector<uint32_t> indices;
    RenderObject * renderObject;
    std::vector<glcustom::Texture *> textures;
};


#endif //BARRENLANDS_PROCEDURALOBJECT_HPP
