//
// Created by Lou Landry on 22/11/2017.
//
#include <glimac/common.hpp>
#include "../include/VBOBuffer.hpp"
#include <vector>


VBOBuffer::VBOBuffer() : m_id(){
    glGenBuffers(1, &m_id);
}

VBOBuffer::~VBOBuffer() {
 glDeleteBuffers(1,&m_id);
}

void VBOBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBOBuffer::debind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint VBOBuffer::getM_id() const {
    return m_id;
}

void VBOBuffer::fill(const std::vector<glimac::ShapeVertex> &vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glimac::ShapeVertex), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
