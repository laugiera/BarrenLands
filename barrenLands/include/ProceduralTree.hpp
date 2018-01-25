#ifndef BARRENLANDS_PROCEDURALTREE_HPP
#define BARRENLANDS_PROCEDURALTREE_HPP

#include "ProceduralObject.hpp"
#include "ProceduralBranche.hpp"
#include "ProceduralFeuillage.hpp"

class ProceduralTree : public ProceduralObject{
public:
    ProceduralTree();
    virtual ~ProceduralTree();

    //à redéfinir pour chaque élement
    void generateVertices();
    void generateIndices(){};
    //void generateNormals();

    //commun à toutes les Tree
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);


    void draw(const glm::mat4 &viewMatrix);
    //static
    static void setPositions(std::vector<ProceduralObject *> objects);

private:
    ProceduralBranche tronc;
    ProceduralFeuillage feuillage;
};

#endif //BARRENLANDS_PROCEDURALTREE_HPP
