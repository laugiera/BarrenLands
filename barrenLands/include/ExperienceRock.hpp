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
    void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);
private:
    glm::vec3 center;
};


#endif //BARRENLANDS_EXPERIENCEROCK_HPP
