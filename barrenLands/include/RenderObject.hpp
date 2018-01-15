//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_RENDEROBJECT_HPP
#define BARRENLANDS_RENDEROBJECT_HPP

#include <vector>
#include <glimac/common.hpp>

class RenderObject {
public:
    RenderObject();

    virtual ~RenderObject();

    void fillData(std::vector<glimac::ShapeVertex> vertices, std::vector<int> indices);
    void render();
};


#endif //BARRENLANDS_RENDEROBJECT_HPP
