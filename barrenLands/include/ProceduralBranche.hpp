#ifndef BARRENLANDS_PROCEDURALBRANCHE_HPP
#define BARRENLANDS_PROCEDURALBRANCHE_HPP

#include "ProceduralObject.hpp"

class ProceduralBranche : public ProceduralObject{
public:
    ProceduralBranche();
    virtual ~ProceduralBranche();

    glm::mat4 getRandomRotation();
    glm::mat4 getRandomScale();

    //à redéfinir pour chaque élement
    void generateVertices();
    void generateIndices(){};
    void generateNormals();


    float getHeight(){
        return height;
    }

    void addInstance(const glm::vec3 &position, const Color &biomeColor, glm::mat4 scale);

private:
    int nbrSub;
    float height;
    float radius1;
    float radius2;
};

#endif //BARRENLANDS_PROCEDURALBRANCHE_HPP
