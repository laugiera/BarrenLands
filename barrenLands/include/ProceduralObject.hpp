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
#include "Instance.hpp"
/**
 * Class ProceduralObject
 * By default, it's a cube
 */
class ProceduralObject {
public:

    ProceduralObject();

    virtual ~ProceduralObject();



    /**** CREATING AND RENDERING OBJECTS *****/

    virtual void addInstance(const glm::vec3 &position, const Color &biomeColor);

    virtual void createRenderObject(ProgramManager *programManager, TextureManager *textureManager,Color *color = nullptr);

    virtual void draw(const glm::mat4 &viewMatrix);



    /***** SETTING RANDOM PARAMETERS OF THE OBJECT *****/

    virtual glm::vec3 getRandomPosition(const glm::vec3 &position);

    virtual glm::mat4 getRandomRotation();

    virtual glm::mat4 getRandomScale();

    virtual void scatter();

    virtual Color * chooseColor(Color * _color = nullptr);

    virtual Color chooseColor(const Color & c);

    virtual std::vector<glcustom::Texture *> chooseTextures(TextureManager *textureManager);



    /***** FINDING THE HEIGHT AND ORIENTATION OF THE GROUND BENEATH AN OBJECT *****/

    float getHauteur(const glm::vec3 &_position);

    glm::vec3 getNormale();

    int inTriangle(glm::vec3 O, glm::vec3 A, glm::vec3 B, const glm::vec3 &_position);

    float determinerY(glm::vec3 O, glm::vec3 A, glm::vec3 B, const glm::vec3 &_position);



    /***** HANDLING OBJECT GEOMETRY *****/

    virtual void generateVertices();

    virtual void generateIndices();

    virtual void generateNormals();

    virtual void subdivideObject(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse = 1);

    virtual void subdivideFace(std::vector<glimac::ShapeVertex> &_vertices, int nbRecurse = 1);

    const std::vector<glimac::ShapeVertex> &getVertices() const;

    const std::vector<uint32_t> &getIndices() const;

    std::vector<Instance*> instances;
protected:
    std::vector<glimac::ShapeVertex> vertices;
    std::vector<uint32_t> indices;
    RenderObject * renderObject;
    glm::vec3 position;
    //std::vector<glm::vec3> positions;
    //std::vector<Color> colors;
};


#endif //BARRENLANDS_PROCEDURALOBJECT_HPP
