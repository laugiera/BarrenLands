//
// Created by Lou Landry on 18/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALSEA_HPP
#define BARRENLANDS_PROCEDURALSEA_HPP

#include "ProceduralObject.hpp"

class ProceduralSea : public ProceduralObject {
public:
    ProceduralSea();

private:
    void generateVertices();
    void generateIndices();
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager,Color *color = nullptr);
    void draw(const glm::mat4 & viewMatrix);
};


#endif //BARRENLANDS_PROCEDURALSEA_HPP
