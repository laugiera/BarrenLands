//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_ROUNDROCK_H
#define BARRENLANDS_ROUNDROCK_H

#include <ProceduralRock.h>

class RoundRock : public ProceduralRock {
public:
    RoundRock();
    ~RoundRock();
    void generateVertices();
    void generateIndices();
    void generateNormals();
};


#endif //BARRENLANDS_ROUNDROCK_H
