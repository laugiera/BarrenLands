#ifndef BARRENLANDS_PROCEDURALGRASS_HPP
#define BARRENLANDS_PROCEDURALGRASS_HPP

#include "ProceduralObject.hpp"

class ProceduralGrass : public ProceduralObject{
public:
    ProceduralGrass(glm::vec3 pos);
    virtual ~ProceduralGrass();

    //à redéfinir pour chaque élement
    void generateVertices(){};
    void generateIndices(){};
    void addGrass(float theta1, float theta2, float theta3, float x, float z, float y = 0);

    //commun à tous les grass
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);


    void draw(const glm::mat4 &viewMatrix);



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
