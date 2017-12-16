//
// Created by Lou Landry on 16/12/2017.
//

#include "VAO.hpp"

glcustom::VAO::VAO() {
    glGenVertexArrays(1, &m_id);
}

glcustom::VAO::~VAO() {
    glDeleteVertexArrays(1, &m_id);
}

void glcustom::VAO::bind() {
    glBindVertexArray(m_id);
}

void glcustom::VAO::debind() {
    glBindVertexArray(0);
}

GLuint glcustom::VAO::getM_id() const {
    return m_id;
}

