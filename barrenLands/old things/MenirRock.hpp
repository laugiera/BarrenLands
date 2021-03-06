//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_FLATROCK_H
#define BARRENLANDS_FLATROCK_H

#include <ProceduralRock.hpp>

class MenirRock : public ProceduralRock {
public:
     MenirRock();
     ~MenirRock();
     void generateVertices();
     void generateIndices();
     void generateNormals();
     void subdivideFace( std::vector<glimac::ShapeVertex> & face, int nbRecurse);
     glm::mat4 getRandomScale();
private :
    glm::vec3 center;
};


#endif //BARRENLANDS_FLATROCK_H
