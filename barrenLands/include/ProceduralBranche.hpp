#ifndef BARRENLANDS_PROCEDURALBRANCHE_HPP
#define BARRENLANDS_PROCEDURALBRANCHE_HPP

#include "ProceduralObject.hpp"

class ProceduralBranche : public ProceduralObject{
public:
    ProceduralBranche();
    virtual ~ProceduralBranche();

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

private:
    int nbrSub;
    float height;
    float radius1;
    float radius2;
};

#endif //BARRENLANDS_PROCEDURALBRANCHE_HPP
