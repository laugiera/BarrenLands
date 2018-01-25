//
// Created by Lou Landry on 17/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALBIOME_HPP
#define BARRENLANDS_PROCEDURALBIOME_HPP

#include "ProceduralObject.hpp"
#include <Color.hpp>
#include <ElementManager.hpp>
/**
 * Class ProceduralBiome
 * Derived from Procedural Object
 * Manage biome, his color, vertices, elements
 */
class ProceduralBiome : public ProceduralObject{
public:
    ProceduralBiome( Color *_color = new Color(), const std::string &_name = "");

    ~ProceduralBiome();

    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);

    void createElements();

    void createElement(glm::vec3 position, const std::string &type);

    void setVertices(const std::vector<glimac::ShapeVertex *> &vertices);

    void addVertex(glimac::ShapeVertex *vertex);

    void setName(const std::string &name);

    const std::string &getName() const;

    /**
     * setPosition()
     *
     */


    Color *getColor() const;

    void setColor(Color *color);

private:
    std::vector<glimac::ShapeVertex *> vertices;
    std::string name;
    Color * color;
    std::vector<ProceduralObject *> rocks;
    std::vector<ProceduralObject *> grass;
    std::vector<ProceduralObject *> trees;

};


#endif //BARRENLANDS_PROCEDURALBIOME_HPP
