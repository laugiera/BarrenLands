//
// Created by Lou Landry on 15/01/2018.
//

#include "../include/ProgramManager.hpp"
/**
 * Constructor
 * @param appPath
 */
ProgramManager::ProgramManager() : testProgram(nullptr), elementProgram(nullptr), skyboxProgram(
        nullptr), mapProgram(nullptr), DOFProgram(nullptr), texture2DProgram(nullptr), BlurProgram(nullptr),
                                                             GammaProgram(nullptr) {
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
    delete DOFProgram;
    delete texture2DProgram;
    delete BlurProgram;
    delete GammaProgram;
    std::cout << "delete program manager ok" << std::endl;
}
/**
 * createPrograms()
 */
void ProgramManager::createPrograms() {
    //test Program
    testProgram = new glcustom::GPUProgram(Tools::appPath, "testShader",  "testShader");
    std::vector<std::string> uniform_variables = {"uMV", "uMVP","uNormal","uColor", "uTexture0"};
    testProgram->addUniforms(uniform_variables);

    //to draw elements
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0", "uTexture1" ,"uNormal", "uColor","uDepthMVP"};
    elementProgram = new glcustom::GPUProgram(Tools::appPath,"element","element");
    elementProgram->addUniforms(uniform_variables);

    //to draw skybox
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0", "uResolution", "uTime", "uSunDir"};
    skyboxProgram = new glcustom::GPUProgram(Tools::appPath,"skybox","skybox");
    skyboxProgram->addUniforms(uniform_variables);

    //to draw the map
    uniform_variables.clear();
    uniform_variables = {"uMV", "uMVP","uTexture0", "uTexture1", "uTexture2" , "uTexture3", "uNormal", "uSubDiv", "uColors", "uDepthMVP"};
    mapProgram = new glcustom::GPUProgram(Tools::appPath,"light","light");
    mapProgram->addUniforms(uniform_variables);

    //to draw a 2D texture on the screen
    uniform_variables.clear();
    uniform_variables = {"uTexture0", "uZNear", "uZFar"};
    texture2DProgram = new glcustom::GPUProgram(Tools::appPath,"printTexture2D","printTexture2D");
    texture2DProgram->addUniforms(uniform_variables);

    //add the DOF effect
    uniform_variables.clear();
    uniform_variables = {"uTexture0", "uTexture1", "uTexture2", "uZNear", "uZFar"};
    DOFProgram = new glcustom::GPUProgram(Tools::appPath,"printTexture2D","DOF");
    DOFProgram->addUniforms(uniform_variables);

    //blur
    uniform_variables.clear();
    uniform_variables = {"uTexture0", "uSampleCount", "uDirection", "uZNear", "uZFar"};
    BlurProgram = new glcustom::GPUProgram(Tools::appPath,"printTexture2D","Blur");
    BlurProgram->addUniforms(uniform_variables);

    //gamma
    uniform_variables.clear();
    uniform_variables = {"uTexture0", "uTexture1", "uZNear", "uZFar", "uLightColor", "uLightDir" /*, "uP", "uV"*/};
    GammaProgram = new glcustom::GPUProgram(Tools::appPath,"printTexture2D","Gamma");
    GammaProgram->addUniforms(uniform_variables);

}
/**
 * reloadPrograms()
 * reload the modifications maded in shadders, for debuging
 * \!/ TO MAJ with the programs from the above functions
 */
void ProgramManager::reloadPrograms() {
    std::vector<std::string> uniform_variables = testProgram->getUniformList();
    testProgram->setProgram(Tools::appPath, "testShader",  "testShader");
    testProgram->addUniforms(uniform_variables);

    uniform_variables = elementProgram->getUniformList();
    elementProgram->setProgram(Tools::appPath, "element",  "element");
    elementProgram->addUniforms(uniform_variables);

    uniform_variables = skyboxProgram->getUniformList();
    skyboxProgram->setProgram(Tools::appPath, "skybox",  "skybox");
    skyboxProgram->addUniforms(uniform_variables);

    uniform_variables = mapProgram->getUniformList();
    mapProgram->setProgram(Tools::appPath, "light",  "light");
    mapProgram->addUniforms(uniform_variables);

    texture2DProgram->setProgram(Tools::appPath,"printTexture2D","printTexture2D");
    texture2DProgram->addUniform("uTexture0");

    uniform_variables = DOFProgram->getUniformList();
    DOFProgram->setProgram(Tools::appPath, "printTexture2D",  "DOF");
    DOFProgram->addUniforms(uniform_variables);

    uniform_variables = BlurProgram->getUniformList();
    BlurProgram->setProgram(Tools::appPath, "printTexture2D",  "Blur");
    BlurProgram->addUniforms(uniform_variables);

    uniform_variables = GammaProgram->getUniformList();
    GammaProgram->setProgram(Tools::appPath, "printTexture2D",  "Gamma");
    GammaProgram->addUniforms(uniform_variables);


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

glcustom::GPUProgram *ProgramManager::getBlurProgram() const {
    return BlurProgram;
}

glcustom::GPUProgram *ProgramManager::getGammaProgram() const {
    return GammaProgram;
}


