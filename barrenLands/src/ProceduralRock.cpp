//
// Created by natshez on 18/01/2018.
//

#include "ProceduralRock.h"
ProceduralRock::ProceduralRock(): ProceduralObject(), color(),position(glm::vec3(0.f)){}
ProceduralRock::ProceduralRock(glm::vec3 &_position): color(),position(_position){}
ProceduralRock::~ProceduralRock() {}

void ProceduralRock::createRenderObject(ProgramManager *programManager, TextureManager *textureManager){

}

void ProceduralRock::draw(const glm::mat4 &viewMatrix){

}

std::vector<glcustom::Texture *> ProceduralRock::chooseTextures(TextureManager *textureManager){

}

//static
void ProceduralRock::setPositions(std::vector<ProceduralObject *> objects){

}