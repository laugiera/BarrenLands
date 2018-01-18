//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_FLATROCK_H
#define BARRENLANDS_FLATROCK_H

#include <ProceduralRock.hpp>

class FlatRock : public ProceduralRock {
public:
     FlatRock();
     ~FlatRock();
     void generateVertices();
     void generateIndices();
     void generateNormals();

};


#endif //BARRENLANDS_FLATROCK_H
