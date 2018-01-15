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
    Light(const glm::vec3 &_intensity, const std::string &_name);
    void transform(const glm::vec3 &translation, const float angle, const glm::vec3 &axesRotation, const glm::vec3 &scale);
    void addLightUniforms(glcustom::GPUProgram &program);
    void sendLightUniforms(glcustom::GPUProgram &program);

    void setDirection(glm::vec4 dir = glm::vec4(1,1,10,0));

    const glm::vec4 &getDirection() const;

private:
    glm::vec4 direction;
    glm::vec3 intensity;
    std::string name;

};


#endif //IMACMAN_LIGHT_H
