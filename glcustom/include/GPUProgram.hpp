//
// Created by Lou Landry on 02/12/2017.
//

#ifndef BARRENLANDSMASTER_PROGRAM_HPP
#define BARRENLANDSMASTER_PROGRAM_HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <vector>
#include "UniformVariable.hpp"

namespace glcustom {

    class GPUProgram{
    private:
        glimac::FilePath m_app_path;
        glimac::Program m_program;
        std::string m_vertex_shader; //just the name
        std::string m_fragment_shader; //just the name
        std::vector<UniformVariable> m_u_variables;
    public:
        GPUProgram(glimac::FilePath app_path, std::string m_vertex_shader, std::string m_fragment_shader);
        void createUniformVariables(std::vector<std::string> u_variable_names);
    };

}



#endif //BARRENLANDSMASTER_PROGRAM_HPP
