//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/ProgramManager.hpp"

ProgramManager::ProgramManager(const std::string &appPath) : testProgram(nullptr), lightProgram(nullptr), skyboxProgram(
        nullptr), appPath(appPath) {
    createPrograms();
}

ProgramManager::~ProgramManager() {
    delete testProgram;
    delete lightProgram;
    delete skyboxProgram;
}

void ProgramManager::createPrograms() {
    //test Program
    testProgram = new glcustom::GPUProgram(appPath, "testShader",  "testShader");
    std::vector<std::string> uniform_variables = {"uMV", "uMVP","uNormal","uColor", "uTexture"};
    testProgram->addUniforms(uniform_variables);

    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0", "uTexture1", "uTexture2" ,"uNormal", "uColor", "uSubDiv"};
    lightProgram = new glcustom::GPUProgram(appPath,"lightTest","lightTest");
    lightProgram->addUniforms(uniform_variables);

    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0"};
    skyboxProgram = new glcustom::GPUProgram(appPath,"skybox","skybox");
    skyboxProgram->addUniforms(uniform_variables);


}

glcustom::GPUProgram *ProgramManager::getTestProgram() const {
    return testProgram;
}


glcustom::GPUProgram *ProgramManager::getLightProgram() const {
    return lightProgram;
}
void ProgramManager::reloadPrograms() {
    std::vector<std::string> uniform_variables = testProgram->getUniformList();
    testProgram->setProgram(appPath, "testShader",  "testShader");
    testProgram->addUniforms(uniform_variables);

    uniform_variables = lightProgram->getUniformList();
    lightProgram->setProgram(appPath, "LightTest",  "LightTest");
    lightProgram->addUniforms(uniform_variables);
}

glcustom::GPUProgram *ProgramManager::getSkyboxProgram() const {
    return skyboxProgram;
}


