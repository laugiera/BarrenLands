#ifndef BARRENLANDS_PROCEDURALFEUILLAGE_HPP
#define BARRENLANDS_PROCEDURALFEUILLAGE_HPP

#include "ProceduralObject.hpp"

class ProceduralFeuillage : public ProceduralObject{
public:
    ProceduralFeuillage();
    virtual ~ProceduralFeuillage();

    //à redéfinir pour chaque élement
    void generateVertices();
    void generateIndices(){};
    //void generateNormals();

    //commun à toutes les branches
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);


    void draw(const glm::mat4 &viewMatrix);
    //static
    static void setPositions(std::vector<ProceduralObject *> objects);
    void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse);

private:
    glm::vec3 center;
};

#endif //BARRENLANDS_PROCEDURALFEUILLAGE_HPP
