//
// Created by Lou Landry on 16/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALMAP_HPP
#define BARRENLANDS_PROCEDURALMAP_HPP

#include "ProceduralObject.hpp"
#include "NoiseManager.hpp"
#include "RenderMap.hpp"
#include "ProceduralBiome.hpp"
#include "ProgramManager.hpp"
#include "TextureManager.hpp"

class ProceduralMap : public ProceduralObject{
public:
    ProceduralMap(NoiseManager *noise);
    void generateVertices(NoiseManager *noise);
    void generateIndices();
    void generateNormals();
    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);
    void createBiomes();
    virtual std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);


    glimac::ShapeVertex getVertices(int i, int j);
    std::vector<glimac::ShapeVertex> getVerticesTab();

    void setTextures(const std::vector<glcustom::Texture *> &textures);

private:
    std::vector<glcustom::Texture*> textures;
    std::vector<ProceduralBiome *> biomes;

};


#endif //BARRENLANDS_PROCEDURALMAP_HPP
