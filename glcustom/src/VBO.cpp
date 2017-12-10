//
// Created by Lou Landry on 22/11/2017.
//
#include <glimac/common.hpp>
#include "VBO.hpp"
#include <vector>


glcustom::VBO::VBO() : m_id(){
    glGenBuffers(1, &m_id);
}

glcustom::VBO::~VBO() {
 glDeleteBuffers(1,&m_id);
}

void glcustom::VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void glcustom::VBO::debind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint glcustom::VBO::getM_id() const {
    return m_id;
}
/*
void glcustom::VBO::fillBuffer(const std::vector<glimac::ShapeVertex> &vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
*/