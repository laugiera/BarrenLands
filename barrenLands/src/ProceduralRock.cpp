//
// Created by natshez on 18/01/2018.
//

#include "ProceduralRock.hpp"
ProceduralRock::ProceduralRock(): ProceduralObject(){}
ProceduralRock::~ProceduralRock() {}

void ProceduralRock::createRenderObject(ProgramManager *programManager, TextureManager *textureManager,  Color * color){
    std::vector<glcustom::Texture *> textures = chooseTextures(textureManager);
    renderObject = new RenderObject(programManager->getLightProgram(), textures); // to change if program is different
    renderObject->fillData(vertices, indices);
    renderObject->setColor(color);
}


std::vector<glcustom::Texture *> ProceduralRock::chooseTextures(TextureManager *textureManager) {
    return std::vector<glcustom::Texture *>(1, textureManager->getRandomTexture("rock"));
}

//static
void ProceduralRock::setPositions(std::vector<ProceduralObject *> objects){

}