//
// Created by Lou Landry on 02/12/2017.
//
#define GLEW_STATIC
#ifndef BARRENLANDSMASTER_PROGRAM_HPP
#define BARRENLANDSMASTER_PROGRAM_HPP

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <map>
#include <glm/detail/type_mat.hpp>
#include <vector>
//#include <Texture.hpp>
#include <vector>
#include <iostream>

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
        void addUniforms(std::vector<std::string> names);
        std::vector<std::string> getUniformList();
        void changeFS(std::string fsFile);
        void changeVS(std::string vsFile);

        void setProgram(glimac::FilePath app_path, std::string m_vertex_shader, std::string m_fragment_shader);

        void sendUniform1i(std::string name, int value);
        void sendUniform1f(std::string name, float value);
        void sendUniformMat4(std::string name, glm::mat4 value);
        void sendUniformMat3(std::string name, glm::mat3 value);
        void sendUniformVec3(std::string name, glm::vec3 value);
        void sendUniformVec4(std::string name, glm::vec4 value);
        void sendUniformTextureUnit(std::string name, int value);
        void sendUniformArrayVec3(std::string name, glm::vec3 *values, int size);
        void use();
        GLint getUniformId(std::string name);
        /*
        void addTexture(std::string name, Texture texture);
        void addTextures(std::vector<std::string> names, std::vector<Texture> textures);
        void sendTextures();
         */
    };

}



#endif //BARRENLANDSMASTER_PROGRAM_HPP
