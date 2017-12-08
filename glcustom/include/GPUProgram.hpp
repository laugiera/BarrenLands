//
// Created by Lou Landry on 02/12/2017.
//

#ifndef BARRENLANDSMASTER_PROGRAM_HPP
#define BARRENLANDSMASTER_PROGRAM_HPP

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <map>
#include <glm/detail/type_mat.hpp>

namespace glcustom {

    class GPUProgram{
    private:
        glimac::FilePath m_app_path;
        glimac::Program m_program;
        std::string m_vertex_shader; //just the name
        std::string m_fragment_shader; //just the name
        std::map<std::string, GLint> m_u_variables;
    public:
        GPUProgram(glimac::FilePath app_path, std::string m_vertex_shader, std::string m_fragment_shader);
        void addUniform(std::string name);
        void sendUniform1f(std::string name, float value);
        void sendUniformMat4(std::string name, glm::mat4 value);
        void sendUniformMat3(std::string name, glm::mat3 value);
        void sendUniformVec3(std::string name, glm::vec3 value);
        void use();
    };

}



#endif //BARRENLANDSMASTER_PROGRAM_HPP
