//
// Created by Lou Landry on 22/11/2017.
//
#define GLEW_STATIC
#include "VBO.hpp"
#include <vector>


glcustom::VBO::VBO(){
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
