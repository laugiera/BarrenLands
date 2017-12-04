//
// Created by Lou Landry on 02/12/2017.
//

#include "UniformVariable.hpp"

glcustom::UniformVariable::UniformVariable(GLuint program_location, const std::string &m_name) : m_location(),
                                                                                                 m_name(m_name) {
    m_location = glGetUniformLocation(program_location, m_name.c_str());
}


