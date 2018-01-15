//
// Created by natshez on 29/12/2017.
//

#include "Light.hpp"

Light::Light(const glm::vec3 &_intensity, const std::string & _name) : intensity(_intensity), name(_name)
{
    setDirection();
}

void Light::setDirection(glm::vec4 dir) {
    direction = dir;
}

void Light::transform(const glm::vec3 &translation, const float angle, const glm::vec3 &axesRotation, const glm::vec3 &scale){
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::scale(transformation,scale);
    transformation = glm::rotate(transformation,angle,axesRotation);
    transformation = glm::translate(transformation, translation);
    direction = transformation * direction;
}

void Light::addLightUniforms(glcustom::GPUProgram &program){
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uLightDir_vs_"+name);
    uniformVariables.push_back("uLightIntensity_"+name);

    program.addUniforms(uniformVariables);
}

void Light::sendLightUniforms(glcustom::GPUProgram &program){

    program.sendUniformVec4("uLightDir_vs_"+name,direction);
    program.sendUniformVec3("uLightIntensity_"+name,intensity);

}

const glm::vec4 &Light::getDirection() const {
    return direction;
}
