//
// Created by Lou Landry on 17/01/2018.
//

#include "ProceduralBiome.hpp"

void ProceduralBiome::createRenderObject(ProgramManager *programManager, TextureManager *textureManager) {
    for(ProceduralObject * element : elements){
        element->createRenderObject(programManager, textureManager);
    }
}

ProceduralBiome::ProceduralBiome() : elements() {
    indices.clear();
    createElements();
}

void ProceduralBiome::createElements() {
    //Use factory to fill elements attribute
}
