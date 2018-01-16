//
// Created by natshez on 29/12/2017.
//

#ifndef IMACMAN_LIGHT_H
#define IMACMAN_LIGHT_H


#include <glm/vector_relational.hpp>
#include <glm/matrix.hpp>
#include <GPUProgram.hpp>
#include <iostream>

class Light {
public:
    Light(const float &_intensity, const std::string &_name, const glm::vec3 &_color);
    void transform(const glm::vec3 &translation, const float angle, const glm::vec3 &axesRotation, const glm::vec3 &scale);
    void addLightUniforms(glcustom::GPUProgram *program);
    void sendLightUniforms(glcustom::GPUProgram *program);
    void rotate(float angle, const glm::mat4 &viewMatrix);

    void setDirection(glm::vec4 dir);
    void resetDirection();
    const glm::vec4 &getDirection() const;

private:
    glm::vec4 direction;
    float intensity;
    glm::vec3 color;
    std::string name;

};


#endif //IMACMAN_LIGHT_H
