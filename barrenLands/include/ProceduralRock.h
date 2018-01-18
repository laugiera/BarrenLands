//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_ROCK_H
#define BARRENLANDS_ROCK_H

#include <ProceduralObject.hpp>
#include <Color.hpp>

class ProceduralRock : public ProceduralObject {

protected:
    Color color;
    glm::vec3 position;

public:
    ProceduralRock();
    ProceduralRock(glm::vec3 &_position);
    virtual ~ProceduralRock();

    //à redéfinir pour chaque élement
    virtual void generateVertices() =0;
    virtual void generateIndices() =0;
    virtual void generateNormals() =0;

    void setColor(Color &_color){
        color = color;
    }

    Color & getColor(){
        return color;
    }

    void setPosition(glm::vec3 &_position){
        position = position;
    }

    glm::vec3 & getPosition(){
        return position;
    }

    //commun à tous les rocks
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);
    void draw(const glm::mat4 &viewMatrix);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    //static
    static void setPositions(std::vector<ProceduralObject *> objects);




};


#endif //BARRENLANDS_ROCK_H
