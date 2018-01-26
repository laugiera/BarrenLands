#ifndef BARRENLANDS_PROCEDURALBRANCHE_HPP
#define BARRENLANDS_PROCEDURALBRANCHE_HPP

#include "ProceduralObject.hpp"

class ProceduralBranche : public ProceduralObject{
public:
    ProceduralBranche();
    virtual ~ProceduralBranche();

    glm::mat4 getRandomScale();

    //à redéfinir pour chaque élement
    void generateVertices();
    void generateIndices(){};
    void generateNormals();

    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    float getHeight(){
        return height;
    }
/*
    void draw(const glm::mat4 &viewMatrix);
    */
    //static
    static void setPositions(std::vector<ProceduralObject *> objects);

private:
    int nbrSub;
    float height;
    float radius1;
    float radius2;
};

#endif //BARRENLANDS_PROCEDURALBRANCHE_HPP
