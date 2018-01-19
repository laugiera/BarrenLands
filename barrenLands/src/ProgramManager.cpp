//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/ProgramManager.hpp"

ProgramManager::ProgramManager(const std::string &appPath) : testProgram(nullptr), elementProgram(nullptr), skyboxProgram(
        nullptr), mapProgram(nullptr), appPath(appPath) {
    createPrograms();
}

ProgramManager::~ProgramManager() {
    delete testProgram;
    delete elementProgram;
    delete skyboxProgram;
    delete mapProgram;
}

/**
 * Creates the programs
 */
void ProgramManager::createPrograms() {
    //test Program
    testProgram = new glcustom::GPUProgram(appPath, "testShader",  "testShader");
    std::vector<std::string> uniform_variables = {"uMV", "uMVP","uNormal","uColor", "uTexture0"};
    testProgram->addUniforms(uniform_variables);

    //to draw elements
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0" ,"uNormal", "uColor"};
    elementProgram = new glcustom::GPUProgram(appPath,"element","element");
    elementProgram->addUniforms(uniform_variables);

    //to draw skybox
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0"};
    skyboxProgram = new glcustom::GPUProgram(appPath,"skybox","skybox");
    skyboxProgram->addUniforms(uniform_variables);

    //to draw the map
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0", "uTexture1", "uTexture2" ,"uNormal", "uSubDiv", "uColors"};
    mapProgram = new glcustom::GPUProgram(appPath,"light","light");
    mapProgram->addUniforms(uniform_variables);


}

/**
 * Reload the GPUprograms to be able to alter the shaders while running the app
 */
void ProgramManager::reloadPrograms() {
    std::vector<std::string> uniform_variables = testProgram->getUniformList();
    testProgram->setProgram(appPath, "testShader",  "testShader");
    testProgram->addUniforms(uniform_variables);

}

/***** GETTERS *****/

glcustom::GPUProgram *ProgramManager::getTestProgram() const {
    return testProgram;
}

glcustom::GPUProgram *ProgramManager::getElementProgram() const {
    return elementProgram;
}

glcustom::GPUProgram *ProgramManager::getSkyboxProgram() const {
    return skyboxProgram;
}

glcustom::GPUProgram *ProgramManager::getMapProgram() const {
    return mapProgram;
}


