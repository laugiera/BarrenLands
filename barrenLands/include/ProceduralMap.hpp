//
// Created by Lou Landry on 16/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALMAP_HPP
#define BARRENLANDS_PROCEDURALMAP_HPP

#include "ProceduralObject.hpp"
#include "ProceduralSea.hpp"
#include "NoiseManager.hpp"
#include "RenderMap.hpp"
#include "ProceduralBiome.hpp"
#include "ProgramManager.hpp"
#include "TextureManager.hpp"
#include <Color.hpp>
/**
 * Class ProceduralMap
 * Derived from ProceduralObject
 * Manage the game Map with its biomes, vertices, sea and noise maps
 */
class ProceduralMap : public ProceduralObject{
public:
    ProceduralMap();

    virtual ~ProceduralMap();

    void generateVertices();

    void generateIndices();

    void generateNormals();

    void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);

    void createBiomes();

    virtual std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    void createBiomeColors();

    glimac::ShapeVertex getVertex(int i, int j);

    std::vector<glimac::ShapeVertex> getVertices();

    void createSea();

    void draw(const glm::mat4 & viewMatrix);



private:
    std::vector<ProceduralBiome *> biomes;
    std::vector<float> moistureMap;
    ProceduralObject * sea;

};


#endif //BARRENLANDS_PROCEDURALMAP_HPP
