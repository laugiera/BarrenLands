//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALOBJECT_HPP
#define BARRENLANDS_PROCEDURALOBJECT_HPP

#include "glimac/common.hpp"
#include <vector>
#include "RenderObject.hpp"


class ProceduralObject {
public:
    ProceduralObject();

    virtual ~ProceduralObject();

    virtual void generateVertices();
    virtual void generateIndices();
    void generateNormals();
    void createRenderObject();
    void draw();
private:
    std::vector<glimac::ShapeVertex> vertices;
    std::vector<int> indices;
    RenderObject * renderObject;
};


#endif //BARRENLANDS_PROCEDURALOBJECT_HPP
