//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_CRYSTALROCK_H
#define BARRENLANDS_CRYSTALROCK_H

#include <ProceduralRock.hpp>

class CrystalRock : public ProceduralRock {
public:
     CrystalRock();
     ~CrystalRock();
     void generateVertices();
     void generateIndices();
     void generateNormals();
     void subdivideFace( std::vector<glimac::ShapeVertex> & face, int nbRecurse);
    Color * chooseColor(Color * _color);
    glm::mat4 getRandomScale();
private :
    glm::vec3 center;
};


#endif //BARRENLANDS_CRYSTALROCK_H
