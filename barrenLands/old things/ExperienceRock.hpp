#ifndef BARRENLANDS_EXPERIENCEROCK_HPP
#define BARRENLANDS_EXPERIENCEROCK_HPP

#include <ProceduralRock.hpp>
#include "NoiseManager.hpp"

class ExperienceRock : public ProceduralRock {
public:
    ExperienceRock();
    ~ExperienceRock();
    void generateVertices();
    void generateIndices();
    void generateNormals();
    //void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse =1);
    void subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse = 1);
    Color * chooseColor(Color * _color);
    int find(std::vector<glm::vec3> &tab, glm::vec3 object);
    void smooth(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);
private:
    glm::vec3 center;
};


#endif //BARRENLANDS_EXPERIENCEROCK_HPP
