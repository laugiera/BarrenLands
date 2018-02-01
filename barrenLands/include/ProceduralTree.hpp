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

    virtual void addInstance(const glm::vec3 &position, const Color &biomeColor);

    //à redéfinir pour chaque élement
    virtual void generateVertices();

    virtual void generateIndices(){};

    //commun à toutes les Tree
    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);

    virtual void scatter();


private:
    ProceduralBranche * tronc;
    ProceduralFeuillage * feuillage;
};

#endif //BARRENLANDS_PROCEDURALTREE_HPP
