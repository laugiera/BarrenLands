//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_FLATROCK_H
#define BARRENLANDS_FLATROCK_H

#include <ProceduralRock.hpp>

class CrystalRock : public ProceduralRock {
public:
     CrystalRock();
     ~CrystalRock();
     void generateVertices();
     void generateIndices();
     void generateNormals();
     void subdivideFace( std::vector<glimac::ShapeVertex> & face, int nbRecurse);
private :
    glm::vec3 center;
};


#endif //BARRENLANDS_FLATROCK_H
