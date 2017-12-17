//
// Created by Lou Landry on 02/12/2017.
//

#include "glcustom/GPUProgram.hpp"

glcustom::GPUProgram::GPUProgram(glimac::FilePath app_path, std::string m_vertex_shader, std::string m_fragment_shader)
        : m_app_path(app_path), m_vertex_shader(m_vertex_shader), m_fragment_shader(m_fragment_shader), m_u_variables() {
    m_vertex_shader += ".vs.glsl";
    m_fragment_shader += ".fs.glsl";
    m_program = glimac::loadProgram(m_app_path.dirPath() + "shaders/" + m_vertex_shader,
                                    m_app_path.dirPath() + "shaders/" + m_fragment_shader);
}

void glcustom::GPUProgram::addUniform(std::string name) {
    GLint id = glGetUniformLocation(m_program.getGLId(), name.c_str());
    m_u_variables.insert(std::pair<std::string, GLint>(name, id));
}

void glcustom::GPUProgram::sendUniform1f(std::string name, float value) {
    GLint id = m_u_variables[name];
    glUniform1f(id, value);
}

void glcustom::GPUProgram::sendUniformMat4(std::string name, glm::mat4 value) {
    GLint id = m_u_variables[name];
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void glcustom::GPUProgram::sendUniformMat3(std::string name, glm::mat3 value) {
    GLint id = m_u_variables[name];
    glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(value));
}

void glcustom::GPUProgram::use() {
    m_program.use();
}

void glcustom::GPUProgram::sendUniformVec3(std::string name, glm::vec3 value) {
    GLint id = m_u_variables[name];
    glUniform3fv(id, 1, glm::value_ptr(value));
}

