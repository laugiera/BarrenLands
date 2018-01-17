//
// Created by Lou Landry on 17/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALBIOME_HPP
#define BARRENLANDS_PROCEDURALBIOME_HPP

#include "ProceduralObject.hpp"

class ProceduralBiome : public ProceduralObject{
public:
    ProceduralBiome();

    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);
    void createElements();

private:
    std::vector<ProceduralObject *> elements;

};


#endif //BARRENLANDS_PROCEDURALBIOME_HPP
