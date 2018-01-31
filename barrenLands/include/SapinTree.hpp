#ifndef BARRENLANDS_SAPINTREE_HPP
#define BARRENLANDS_SAPINTREE_HPP


#include "ProceduralBranche.hpp"
#include "Sapin.hpp"
#include "ProceduralTree.hpp"


class SapinTree : public ProceduralTree {
public:
    SapinTree();
    virtual ~SapinTree();

    void addInstance(const glm::vec3 &position, const Color &biomeColor);

    //à redéfinir pour chaque élement
    void generateVertices();

    void generateIndices(){};

    //commun à toutes les Tree
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);
    void scatter();


private:
    ProceduralBranche * tronc;
    ProceduralFeuillage * sapin;
};

#endif //BARRENLANDS_SAPINTREE_HPP
