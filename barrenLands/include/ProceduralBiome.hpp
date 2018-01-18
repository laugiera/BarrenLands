//
// Created by Lou Landry on 17/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALBIOME_HPP
#define BARRENLANDS_PROCEDURALBIOME_HPP

#include "ProceduralObject.hpp"
#include <Color.hpp>
#include <ElementFactory.hpp>

class ProceduralBiome : public ProceduralObject{
public:
    ProceduralBiome( Color *_color = new Color());
    ~ProceduralBiome();

    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);
    void createElements();

    void setVertices(const std::vector<glimac::ShapeVertex *> &vertices);

    void addVertex(glimac::ShapeVertex *vertex);
    void draw(const glm::mat4 &viewMatrix);


    Color *getColor() const;

    void setColor(Color *color);

private:
    std::vector<ProceduralObject *> elements;
    std::vector<glimac::ShapeVertex *> vertices;
    std::string name;
    Color * color;

};


#endif //BARRENLANDS_PROCEDURALBIOME_HPP
