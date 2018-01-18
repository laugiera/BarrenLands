//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_ARCHEDROCK_H
#define BARRENLANDS_ARCHEDROCK_H

#include <ProceduralRock.hpp>

class ArchedRock : public ProceduralRock {
public:
    ArchedRock();
    ~ArchedRock();
    void generateVertices();
    void generateIndices();
    void generateNormals();
};


#endif //BARRENLANDS_ARCHEDROCK_H
