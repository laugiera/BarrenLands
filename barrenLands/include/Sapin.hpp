#ifndef BARRENLANDS_SAPIN_HPP
#define BARRENLANDS_SAPIN_HPP

#include "ProceduralObject.hpp"
#include "ProceduralFeuillage.hpp"

class Sapin : public ProceduralFeuillage{
public:
    Sapin();
    virtual ~Sapin();

    //à redéfinir pour chaque élement
    void generateVertices() override;
    void addInstance(const glm::vec3 &position, const Color &biomeColor) override;

private:
    glm::vec3 center;
};

#endif //BARRENLANDS_SAPIN_HPP
