//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_RENDEROBJECT_HPP
#define BARRENLANDS_RENDEROBJECT_HPP

#include <vector>
#include <glimac/common.hpp>
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include "Tools.hpp"

class RenderObject {
public:
    RenderObject() = default;

    RenderObject(glcustom::GPUProgram * program);

    virtual ~RenderObject();
    void fillData(std::vector<glimac::ShapeVertex> vertices, std::vector<uint32_t> indices);
    void transform(const glm::vec3 &translate, const float angle, const glm::vec3 &axesRotation,
                   const glm::vec3 &scale);
    void render(const glm::mat4 &viewMatrix);

//private:
    glcustom::VAO vao;
    glcustom::VBO vbo;
    glcustom::IBO ibo;
    glcustom::GPUProgram * program;
    glm::mat4 modelMatrix;
    std::vector<uint32_t> indices;
};


#endif //BARRENLANDS_RENDEROBJECT_HPP
