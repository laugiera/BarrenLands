//
// Created by Lou Landry on 02/12/2017.
//

#include "GPUProgram.hpp"
#include <vector>

glcustom::GPUProgram::GPUProgram(glimac::FilePath app_path, std::string m_vertex_shader, std::string m_fragment_shader)
        : m_app_path(app_path), m_vertex_shader(m_vertex_shader), m_fragment_shader(m_fragment_shader), m_u_variables() {
    m_vertex_shader += ".vs.glsl";
    m_fragment_shader += ".fs.glsl";
    m_program = glimac::loadProgram(m_app_path + "shaders/" + m_vertex_shader,
                                    m_app_path + "shaders/" + m_fragment_shader);
}

void glcustom::GPUProgram::addUniform(std::string name) {
    GLint id = glGetUniformLocation(m_program.getGLId(), name.c_str());
    //m_u_variables.insert(std::pair<std::string, GLint>(name, id));
    m_u_variables[name] = id;
}


void glcustom::GPUProgram::setProgram(glimac::FilePath app_path, std::string m_vertex_shader, std::string m_fragment_shader){
    //keep uVariable list
    //std::vector<std::string> uVars = getUniformList();

    m_vertex_shader = m_vertex_shader + ".vs.glsl";
    m_fragment_shader = m_fragment_shader + ".fs.glsl";
    m_program = glimac::loadProgram(m_app_path + "shaders/" + m_vertex_shader,
                                    m_app_path + "shaders/" + m_fragment_shader);
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
/*
void glcustom::GPUProgram::sendUniformArrayVec3(std::string name, glm::vec3 * values, int size){
    GLint id = m_u_variables[name];
    glUniform3fv(id, size, glm::value_ptr(values[0]));
}
 */

void glcustom::GPUProgram::sendUniformArrayVec3(std::string name, glm::vec3 *values, int size) {
    GLint id = m_u_variables[name];
    glUniform3fv(id, size, glm::value_ptr(values[0]));
}


void glcustom::GPUProgram::sendUniformVec4(std::string name, glm::vec4 value) {
    GLint id = m_u_variables[name];
    //std::cout << glIsProgram(id) << std::endl;
    glUniform4fv(id, 1, glm::value_ptr(value));
}

GLint glcustom::GPUProgram::getUniformId(std::string name) {
    if(m_u_variables.find(name) != m_u_variables.end()){
        return m_u_variables[name];
    }
    return -1; //handle exception
}

void glcustom::GPUProgram::addUniforms(std::vector<std::string> names) {
    for(int i = 0; i<names.size(); i++){
        addUniform(names[i]);
    }
}

void glcustom::GPUProgram::sendUniform1i(std::string name, int value) {
    GLint id = m_u_variables[name];
    glUniform1i(id, value);
}

void glcustom::GPUProgram::sendUniformTextureUnit(std::string name, int value) {
    GLint id = m_u_variables[name];
    glUniform1i(id, value);
}

std::vector<std::string> glcustom::GPUProgram::getUniformList() {
    std::vector<std::string> uniformList;
    std::map<std::string, GLint>::iterator it;
    for(it = m_u_variables.begin(); it!=m_u_variables.end(); it++){
       uniformList.push_back(it->first);
    }
    return uniformList;
}

void glcustom::GPUProgram::changeFS(std::string fsFile) {
    m_fragment_shader = fsFile;
    fsFile += ".fs.glsl";
    fsFile = m_app_path + "shaders/" + fsFile;
    glimac::Shader fs = glimac::loadShader(GL_FRAGMENT_SHADER, fsFile);

    if(!fs.compile()) {
        throw std::runtime_error("Compilation error for fragment shader (from file " + fsFile + "): " + fs.getInfoLog());
    }
    m_program.attachShader(fs);

    if(!m_program.link()) {
        throw std::runtime_error("Link error (for file " + fsFile + "): " + m_program.getInfoLog());
    }
}

void glcustom::GPUProgram::changeVS(std::string vsFile) {
    m_vertex_shader = vsFile;
    vsFile += ".vs.glsl";
    vsFile = m_app_path + "shaders/" + vsFile ;
    glimac::Shader vs = glimac::loadShader(GL_FRAGMENT_SHADER, vsFile);

    if(!vs.compile()) {
        throw std::runtime_error("Compilation error for vertex shader (from file " + vsFile + "): " + vs.getInfoLog());
    }
    m_program.attachShader(vs);

    if(!m_program.link()) {
        throw std::runtime_error("Link error (for file " + vsFile + "): " + m_program.getInfoLog());
    }
}


/*
void glcustom::GPUProgram::addTexture(std::string name, const glcustom::Texture texture) {
    m_textures.insert(std::pair<std::string, Texture>(name, texture));
}

void glcustom::GPUProgram::addTextures(std::vector<std::string> names, std::vector<glcustom::Texture> textures) {
    for(int i = 0; i<names.size(); i++){
        addTexture(names[i], textures[i]);
    }
}


void glcustom::GPUProgram::sendTextures() {
    std::map<std::string, Texture>::iterator it = m_textures.begin();

    while(it != m_textures.end()){
        sendUniform1i(getUniformId(it->first), ) -> arg comment itérer sur GL_TEXTUREXXX ?????
    }
}
*/

