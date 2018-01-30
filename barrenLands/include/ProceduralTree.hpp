#ifndef BARRENLANDS_PROCEDURALTREE_HPP
#define BARRENLANDS_PROCEDURALTREE_HPP

#include "ProceduralObject.hpp"
#include "ProceduralBranche.hpp"
#include "ProceduralFeuillage.hpp"
#include "ElementManager.hpp"

class ProceduralTree : public ProceduralObject{
public:
    ProceduralTree();
    virtual ~ProceduralTree();

    void addInstance(const glm::vec3 &position, const Color &biomeColor);

    //à redéfinir pour chaque élement
    void generateVertices();

    void generateIndices(){};

    //commun à toutes les Tree
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);

    void scatter();


private:
    ProceduralBranche * tronc;
    ProceduralFeuillage * feuillage;
};

#endif //BARRENLANDS_PROCEDURALTREE_HPP