#ifndef BARRENLANDS_PROCEDURALFEUILLAGE_HPP
#define BARRENLANDS_PROCEDURALFEUILLAGE_HPP

#include "ProceduralObject.hpp"

class ProceduralFeuillage : public ProceduralObject{
public:
    ProceduralFeuillage();
    virtual ~ProceduralFeuillage();

    glm::vec3 getRandomPosition(const glm::vec3 & position);

    glm::mat4 getRandomScale();

    //à redéfinir pour chaque élement
    void generateVertices();

    void generateIndices();

    void generateNormals();

    void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);

    void addInstance(const glm::vec3 &position, const Color &biomeColor);


private:
    glm::vec3 center;
};

#endif //BARRENLANDS_PROCEDURALFEUILLAGE_HPP