#ifndef BARRENLANDS_ROUNDFLATROCK_HPP
#define BARRENLANDS_ROUNDFLATROCK_HPP

#include <ProceduralRock.hpp>
#include "NoiseManager.hpp"

class RoundFlatRock : public ProceduralRock {
public:
    RoundFlatRock();
    ~RoundFlatRock();
    void generateVertices();
    void generateIndices();
    void generateNormals();
    //void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse =1);
    void subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse = 1);
    Color * chooseColor(Color * _color);
    int find(std::vector<glm::vec3> &tab, glm::vec3 object);
    void smooth(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);

    glm::mat4 getRandomRotation();
    glm::mat4 getRandomScale();

private:
    glm::vec3 center;
};

#endif //BARRENLANDS_ROUNDFLATROCK_HPP
