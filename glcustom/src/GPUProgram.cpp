//
// Created by Lou Landry on 02/12/2017.
//

#include "GPUProgram.hpp"

glcustom::GPUProgram::GPUProgram(glimac::FilePath app_path, std::string m_vertex_shader, std::string m_fragment_shader)
        : m_app_path(app_path), m_vertex_shader(m_vertex_shader), m_fragment_shader(m_fragment_shader)/*, m_u_variables()*/ {
    //m_app_path = glimac::FilePath(app_path);
    m_vertex_shader += ".vs.glsl";
    m_fragment_shader += ".fs.glsl";
    m_program = glimac::loadProgram(m_app_path.dirPath() + "shaders/" + m_vertex_shader,
                                    m_app_path.dirPath() + "shaders/" + m_fragment_shader);
}

void glcustom::GPUProgram::createUniformVariables(std::vector<std::string> u_variable_names) {
    for(int i = 0 ; i< u_variable_names.size(); i++) {
       // m_u_variables.push(UniformVariable(m_program.getGLId(), u_variable_names[i]));
    }
}
