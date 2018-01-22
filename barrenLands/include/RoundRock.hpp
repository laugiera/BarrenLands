//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_ROUNDROCK_H
#define BARRENLANDS_ROUNDROCK_H

#include <ProceduralRock.hpp>

class RoundRock : public ProceduralRock {
public:
    RoundRock();
    ~RoundRock();
    void generateVertices();
    void generateIndices();
    void generateNormals();
    void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices);
};


#endif //BARRENLANDS_ROUNDROCK_H
