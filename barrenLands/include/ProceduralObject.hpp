//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROCEDURALOBJECT_HPP
#define BARRENLANDS_PROCEDURALOBJECT_HPP

#include "glimac/common.hpp"
#include <vector>
#include "RenderObject.hpp"
#include "glimac/Sphere.hpp"
#include "ProgramManager.hpp"
#include "TextureManager.hpp"
/**
 * Class ProceduralObject
 * By default, it's a cube
 */
class ProceduralObject {
public:
    ProceduralObject();
    //ProceduralObject(glm::vec3 &_position);

    virtual ~ProceduralObject();

    virtual void generateVertices();

    virtual void generateIndices();

    virtual void generateNormals();

    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager,Color *color = nullptr);

    virtual void draw(const glm::mat4 &viewMatrix);

    virtual std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);

    virtual void subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse = 1);

    virtual void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse = 1);

    /**Getter and setter for postion**/
    glm::vec3 & getPosition(){
        return position;
    }

    void setPosition(glm::vec3 &_position){
        position = _position;
    }

    float getHauteur();
    glm::vec3 getNormale();

    int inTriangle(glm::vec3 O, glm::vec3 A, glm::vec3 B);
    float determinerY(glm::vec3 O, glm::vec3 A, glm::vec3 B);

protected:
    std::vector<glimac::ShapeVertex> vertices;
    std::vector<uint32_t> indices;
    RenderObject * renderObject;
    glm::vec3 position;
};


#endif //BARRENLANDS_PROCEDURALOBJECT_HPP
