#ifndef BARRENLANDS_PROCEDURALGRASS_HPP
#define BARRENLANDS_PROCEDURALGRASS_HPP

#include "ProceduralObject.hpp"

class ProceduralGrass : public ProceduralObject{
public:
    ProceduralGrass();
    virtual ~ProceduralGrass();

    //à redéfinir pour chaque élement
    void generateVertices();
    void generateIndices();
    //void generateNormals();

    //commun à tous les grass
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    //static
    static void setPositions(std::vector<ProceduralObject *> objects);

private:
    float theta1;
    float theta2;
    float theta3;
    float width;
    float height;
};

#endif //BARRENLANDS_PROCEDURALGRASS_HPP
