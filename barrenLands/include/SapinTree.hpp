//
// Created by Etienne on 01/02/2018.
//

#ifndef BARRENLANDS_SAPINTREE_HPP
#define BARRENLANDS_SAPINTREE_HPP

#include "ProceduralObject.hpp"
#include "ElementManager.hpp"

class SapinTree : public ProceduralObject{
public:
    SapinTree();
    virtual ~SapinTree();

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

#endif //BARRENLANDS_SAPINTREE_HPP
