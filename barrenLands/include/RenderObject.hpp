//
// Created by Lou Landry on 15/01/2018.
//
#define GLEW_STATIC
#ifndef BARRENLANDS_RENDEROBJECT_HPP
#define BARRENLANDS_RENDEROBJECT_HPP

#include <vector>
#include <glimac/common.hpp>
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include "Tools.hpp"
#include <Texture.hpp>
#include <Color.hpp>
#include <Instance.hpp>
/**
 * Class RenderObject
 * Corresponding to ProceduralObject Class
 */
class RenderObject {
public:
    RenderObject() = default;

    RenderObject(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> texture, Color *_color = nullptr);

    virtual ~RenderObject();
    void fillData(std::vector<glimac::ShapeVertex> vertices, std::vector<uint32_t> indices);
    virtual void transform(const glm::vec3 &translate, const float angle, const glm::vec3 &axesRotation,
                   const glm::vec3 &scale);
    virtual void alterModelMatrix(const glm::mat4 &transfos);
    virtual void render(const glm::mat4 & viewMatrix, const  std::vector<Instance*> &instances = std::vector<Instance*>());
    virtual void sendUniforms(const glm::mat4 &viewMatrix);
    virtual void bindTextures();
    virtual void debindTextures();
    /**
     * Getter and setter for color
     */
    virtual void setColor(Color *_color){
        color = _color;
    }

    Color * getColor(){
        return color;
    }


protected:
    glcustom::VAO vao;
    glcustom::GPUProgram * program;
    glm::mat4 modelMatrix;
    std::vector<uint32_t> indices;
    std::vector<glcustom::Texture *> textures;
    Color *color;
    int verticesCount;
};


#endif //BARRENLANDS_RENDEROBJECT_HPP
