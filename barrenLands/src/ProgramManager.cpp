//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/ProgramManager.hpp"
/**
 * Constructor
 * @param appPath
 */
ProgramManager::ProgramManager(const std::string &appPath) : testProgram(nullptr), elementProgram(nullptr), skyboxProgram(
        nullptr), mapProgram(nullptr), shadowProgram(nullptr), appPath(appPath) {
    createPrograms();
}
/**
 * Destructor
 */
ProgramManager::~ProgramManager() {
    delete testProgram;
    delete elementProgram;
    delete skyboxProgram;
    delete mapProgram;
    delete shadowProgram;
    delete DOFProgram;
    delete texture2DProgram;
}
/**
 * createPrograms()
 */
void ProgramManager::createPrograms() {
    //test Program
    testProgram = new glcustom::GPUProgram(appPath, "testShader",  "testShader");
    std::vector<std::string> uniform_variables = {"uMV", "uMVP","uNormal","uColor", "uTexture0"};
    testProgram->addUniforms(uniform_variables);

    //to draw elements
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0", "uTexture1" ,"uNormal", "uColor","uDepthMVP"};
    elementProgram = new glcustom::GPUProgram(appPath,"element","element");
    elementProgram->addUniforms(uniform_variables);

    //to draw skybox
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0"};
    skyboxProgram = new glcustom::GPUProgram(appPath,"skybox","skybox");
    skyboxProgram->addUniforms(uniform_variables);

    //to draw the map
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0", "uTexture1", "uTexture2" , "uNormal", "uSubDiv", "uColors", "uDepthMVP"};
    mapProgram = new glcustom::GPUProgram(appPath,"light","light");
    mapProgram->addUniforms(uniform_variables);

    //to draw a 2D texture on the screen
    texture2DProgram = new glcustom::GPUProgram(appPath,"printTexture2D","printTexture2D");
    texture2DProgram->addUniform("uTexture0");

    //add the DOF effect
    uniform_variables.clear();
    uniform_variables = {"uTexture0", "uTexture1", "uZNear", "uZFar"};
    DOFProgram = new glcustom::GPUProgram(appPath,"printTexture2D","DOF");
    DOFProgram->addUniforms(uniform_variables);

    //shadow map
    uniform_variables.clear();
    uniform_variables = {"uTexture0", "uTexture1", "uTexture2"};
    shadowProgram = new glcustom::GPUProgram(appPath,"shadow","shadow");
    shadowProgram->addUniforms(uniform_variables);

}
/**
 * reloadPrograms()
 * reload the modifications maded in shadders, for debuging
 * \!/ TO MAJ with the programs from the above functions
 */
void ProgramManager::reloadPrograms() {
    std::vector<std::string> uniform_variables = testProgram->getUniformList();
    testProgram->setProgram(appPath, "testShader",  "testShader");
    testProgram->addUniforms(uniform_variables);

    uniform_variables = elementProgram->getUniformList();
    elementProgram->setProgram(appPath, "element",  "element");
    elementProgram->addUniforms(uniform_variables);

    uniform_variables = skyboxProgram->getUniformList();
    skyboxProgram->setProgram(appPath, "skybox",  "skybox");
    skyboxProgram->addUniforms(uniform_variables);

    uniform_variables = mapProgram->getUniformList();
    mapProgram->setProgram(appPath, "light",  "light");
    mapProgram->addUniforms(uniform_variables);

    texture2DProgram->setProgram(appPath,"printTexture2D","printTexture2D");
    texture2DProgram->addUniform("uTexture0");

    uniform_variables = DOFProgram->getUniformList();
    DOFProgram->setProgram(appPath, "printTexture2D",  "DOF");
    DOFProgram->addUniforms(uniform_variables);


}
/**Getters and setters for each program**/
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

glcustom::GPUProgram *ProgramManager::getTexture2DProgram() const {
    return texture2DProgram;
}

glcustom::GPUProgram *ProgramManager::getDOFProgram() const {
    return DOFProgram;
}

glcustom::GPUProgram *ProgramManager::getShadowProgram() const {
    return shadowProgram;
}


