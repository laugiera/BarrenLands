//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALOBJECT_HPP
#define BARRENLANDS_PROCEDURALOBJECT_HPP

#include "glimac/common.hpp"
#include <vector>
#include "RenderObject.hpp"
#include "glimac/Sphere.hpp"
#include "ProgramManager.hpp"
#include "TextureManager.hpp"


class ProceduralObject {
public:
    ProceduralObject();

    virtual ~ProceduralObject();

    virtual void generateVertices();

    virtual void generateIndices();

    virtual void generateNormals();

    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);

    virtual void draw(const glm::mat4 &viewMatrix);

    virtual std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    //glm::vec3 position; //A enlever, là pour faire des tests.
protected:
    std::vector<glimac::ShapeVertex> vertices;
    std::vector<uint32_t> indices;
    RenderObject * renderObject;
};


#endif //BARRENLANDS_PROCEDURALOBJECT_HPP
