//
// Created by natshez on 18/01/2018.
//

#ifndef BARRENLANDS_ROCK_H
#define BARRENLANDS_ROCK_H

#include <ProceduralObject.hpp>
#include <RenderRock.hpp>
/**
 * Class ProceduralRock
 * Derived from ProceduralObject
 * Abstract class for the Rock Object concept
 * Will be derived in concret rock classes
 */
class ProceduralRock : public ProceduralObject {

public:
    ProceduralRock();
    virtual ~ProceduralRock();

    //à redéfinir pour chaque élement
    virtual void generateVertices() =0;
    virtual void generateIndices() =0;
    virtual void generateNormals() =0;

    //commun à tous les rocks
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager, Color * _color);
    std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    //static
    static void setPositions(std::vector<ProceduralObject *> objects);

};


#endif //BARRENLANDS_ROCK_H
