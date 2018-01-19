//
// Created by Lou Landry on 17/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALBIOME_HPP
#define BARRENLANDS_PROCEDURALBIOME_HPP

#include "ProceduralObject.hpp"
#include <Color.hpp>
#include <ElementFactory.hpp>
/**
 * Class ProceduralBiome
 * Derived from Procedural Object
 * Manage biome, his color, vertices, elements
 */
class ProceduralBiome : public ProceduralObject{
public:
    ProceduralBiome( Color *_color = new Color());
    ~ProceduralBiome();

    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager);
    void createElements();
    void createElements(glm::vec3 position);

    void setVertices(const std::vector<glimac::ShapeVertex *> &vertices);

    void addVertex(glimac::ShapeVertex *vertex);
    /**
     * setPosition()
     *
     */
    void setPosition(){
        if(vertices.size() != 0){
            std::cout << vertices[20]->position << std::endl;
            elements[0]->setPosition(vertices[20]->position);
            std::cout << elements[0]->getPosition() << std::endl;
        }
        std::cout << elements.size() << std::endl;
        std::cout << vertices.size() << std::endl;
    }

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
