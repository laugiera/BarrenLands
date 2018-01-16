//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/ProgramManager.hpp"

ProgramManager::ProgramManager(const std::string &appPath) : testProgram(nullptr), appPath(appPath) {
    createPrograms();
}

ProgramManager::~ProgramManager() {
    delete testProgram;
}

void ProgramManager::configureLight(glcustom::GPUProgram * program, std::string name) {
    //add light variables to program
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uLightDir_vs_"+name);
    uniformVariables.push_back("uLightIntensity_"+name);
    program->addUniforms(uniformVariables);
    //send fixed light data to program
    program->sendUniformVec4("uLightDir_vs_"+name,glm::vec4(0,-1,0,0));
    program->sendUniformVec3("uLightIntensity_"+name,glm::vec3(1));
}

void ProgramManager::createPrograms() {
    //test Program
    glimac::FilePath fp(appPath);
    testProgram = new glcustom::GPUProgram(fp, "testShader",  "testShader");
    std::vector<std::string> uniform_variables = {"uMV", "uMVP","uNormal","uColor"};
    testProgram->addUniforms(uniform_variables);
    //configureLight(testProgram, "basicLight");

}

glcustom::GPUProgram *ProgramManager::getTestProgram() const {
    return testProgram;
}


