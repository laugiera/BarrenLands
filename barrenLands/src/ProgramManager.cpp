//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/ProgramManager.hpp"

ProgramManager::ProgramManager(const std::string &appPath) : testProgram(nullptr), lightProgram(nullptr), appPath(appPath) {
    createPrograms();
}

ProgramManager::~ProgramManager() {
    delete testProgram;
    delete lightProgram;
}

void ProgramManager::createPrograms() {
    //test Program
    glimac::FilePath fp(appPath);
    testProgram = new glcustom::GPUProgram(fp, "testShader",  "testShader");
    std::vector<std::string> uniform_variables = {"uMV", "uMVP","uNormal","uColor", "uTexture"};
    testProgram->addUniforms(uniform_variables);

    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture","uNormal", "uColor"};
    lightProgram = new glcustom::GPUProgram(fp,"lightTest","lightTest");
    lightProgram->addUniforms(uniform_variables);
}

glcustom::GPUProgram *ProgramManager::getTestProgram() const {
    return testProgram;
}

glcustom::GPUProgram *ProgramManager::getLightProgram() const {
    return lightProgram;
}


