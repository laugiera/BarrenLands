//
// Created by natshez on 18/01/2018.
//

#include "ProceduralRock.h"
ProceduralRock::ProceduralRock(): ProceduralObject(){
    color = Color();
}
ProceduralRock::~ProceduralRock() {
}

void ProceduralRock::createRenderObject(ProgramManager *programManager, TextureManager *textureManager){

}

void ProceduralRock::draw(const glm::mat4 &viewMatrix){

}

std::vector<glcustom::Texture *> ProceduralRock::chooseTextures(TextureManager *textureManager){

}