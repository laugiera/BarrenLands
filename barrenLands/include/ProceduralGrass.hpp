#ifndef BARRENLANDS_PROCEDURALGRASS_HPP
#define BARRENLANDS_PROCEDURALGRASS_HPP

#include "ProceduralObject.hpp"

class ProceduralGrass : public ProceduralObject{
public:
    ProceduralGrass(glm::vec3 pos);
    ProceduralGrass(glm::vec3 pos, std::vector<glimac::ShapeVertex> tab);
    virtual ~ProceduralGrass();

    //à redéfinir pour chaque élement
    void generateVertices(){};
    void generateIndices(){};
    void addGrass(float theta1, float theta2, float theta3, float x, float z, float y = 0);
    //void generateNormals();

    //commun à tous les grass
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);


    void draw(const glm::mat4 &viewMatrix);
    //static
    static void setPositions(std::vector<ProceduralObject *> objects);

    //Methode pour le placement
    int inTriangle(glm::vec3 O, glm::vec3 A, glm::vec3 B, glm::vec3 _position);
    float determinerHauteur(glm::vec3 O, glm::vec3 A, glm::vec3 B, glm::vec3 _position);

private:
    /*float theta1;
    float theta2;
    float theta3;*/
    float width;
    float height;
};

#endif //BARRENLANDS_PROCEDURALGRASS_HPP
