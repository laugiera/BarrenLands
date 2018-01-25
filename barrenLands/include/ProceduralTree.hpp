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

    glm::mat4 getRandomScale();

    //à redéfinir pour chaque élement
    void generateVertices();

    void generateIndices(){};

    //commun à toutes les Tree
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);

    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);


private:
    ProceduralBranche * tronc;
    ProceduralFeuillage * feuillage;
};

#endif //BARRENLANDS_PROCEDURALTREE_HPP
