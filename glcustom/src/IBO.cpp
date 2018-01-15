//
// Created by Lou Landry on 16/12/2017.
//

#include "IBO.hpp"

glcustom::IBO::IBO() {
    glGenBuffers(1, &m_id);
}

glcustom::IBO::~IBO() {
   // glDeleteBuffers(1, &m_id);
}

void glcustom::IBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void glcustom::IBO::debind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
