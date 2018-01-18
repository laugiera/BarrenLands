//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_ROCK_H
#define BARRENLANDS_ROCK_H

#include <ProceduralObject.hpp>
#include <Color.hpp>

class ProceduralRock : public ProceduralObject {

public:
    ProceduralRock();
    ProceduralRock(glm::vec3 &_position, const Color &_color);
    virtual ~ProceduralRock();

    //à redéfinir pour chaque élement
    virtual void generateVertices() =0;
    virtual void generateIndices() =0;
    virtual void generateNormals() =0;

    //commun à tous les rocks
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);
    void draw(const glm::mat4 &viewMatrix);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    //static
    static void setPositions(std::vector<ProceduralObject *> objects);




};


#endif //BARRENLANDS_ROCK_H
