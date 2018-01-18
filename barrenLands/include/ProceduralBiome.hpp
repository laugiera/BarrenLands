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

    void setVertices(const std::vector<glimac::ShapeVertex *> &vertices);

    void addVertex(glimac::ShapeVertex *vertex);

private:
    std::vector<ProceduralObject *> elements;
    std::vector<glimac::ShapeVertex *> vertices;
    std::string name;

};


#endif //BARRENLANDS_PROCEDURALBIOME_HPP
