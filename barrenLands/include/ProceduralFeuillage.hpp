#ifndef BARRENLANDS_PROCEDURALFEUILLAGE_HPP
#define BARRENLANDS_PROCEDURALFEUILLAGE_HPP

#include "ProceduralObject.hpp"

class ProceduralFeuillage : public ProceduralObject{
public:
    ProceduralFeuillage();
    virtual ~ProceduralFeuillage();

    glm::vec3 getRandomPosition(const glm::vec3 & position);
    glm::mat4 getRandomRotation();
    glm::mat4 getRandomScale();

    //à redéfinir pour chaque élement
    virtual void generateVertices();

    void generateIndices();

    void generateNormals();

    void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);
    void subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);
    virtual void addInstance(const glm::vec3 &position, const Color &biomeColor);
    int find(std::vector<glm::vec3> &tab, glm::vec3 object);
    void smooth(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);

private:
    glm::vec3 center;
};

#endif //BARRENLANDS_PROCEDURALFEUILLAGE_HPP
