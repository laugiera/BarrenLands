//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_SHARPROCK_H
#define BARRENLANDS_SHARPROCK_H

#include <ProceduralRock.h>

class SharpRock : public ProceduralRock {
public:
    SharpRock();
    ~SharpRock();
    void generateVertices();
    void generateIndices();
    void generateNormals();
};


#endif //BARRENLANDS_SHARPROCK_H
