//
// Created by natshez on 29/12/2017.
//

#include "../include/Light.hpp"
/**
 * Constructor
 * @param _intensity
 * @param _name
 * @param _color
 */
Light::Light(const float &_intensity, const std::string & _name,  const glm::vec3 &_color) : intensity(_intensity), name(_name), color(_color)
{
    resetDirection(1);
}
/**
 * setDirection()
 * @param glm::vec4 dir
 */
void Light::setDirection(glm::vec4 dir) {
    direction = dir;
}
/**
 * transform()
 * applies transformation to the light direction
 * @param glm::vec3 translation
 * @param float angle
 * @param glm::vec3 axesRotation
 * @param glm::vec3 scale
 */
void Light::transform(const glm::vec3 &translation, const float angle, const glm::vec3 &axesRotation, const glm::vec3 &scale){
    glm::mat4 transformation = glm::mat4(1.f);
    transformation = glm::scale(transformation,scale);
    transformation = glm::rotate(transformation,angle,axesRotation);
    transformation = glm::translate(transformation, translation);
    direction = transformation * direction;
}
/**
 * addLightUniforms()
 * add needed uniforms to the GPU Program list of uniforms names
 * @param glcustom::GPUProgram * program
 */
void Light::addLightUniforms(glcustom::GPUProgram *program){
    std::vector<std::string> uniformVariables;
    uniformVariables.push_back("uLightDir"+name);
    uniformVariables.push_back("uLightIntensity"+name);
    uniformVariables.push_back("uLightColor"+name);

    program->addUniforms(uniformVariables);
}
/**
 * sendLightUniforms()
 * send needed uniforms values
 * \!/program.use() HAS to be done BEFORE using this function
 * \!/HAS to be the exact same has the function above
 * @param glcustom::GPUProgram * program
 */
void Light::sendLightUniforms(glcustom::GPUProgram *program){

    program->sendUniformVec4("uLightDir"+name,direction);
    program->sendUniform1f("uLightIntensity"+name,intensity);
    program->sendUniformVec3("uLightColor"+name,color);

}
/**
 * rotate()
 * rotate the direction with a given view matrix and angle
 * @param angle
 * @param viewMatrix
 */
void Light::rotate(float angle, const glm::mat4  &viewMatrix){
    glm::mat4 rotation = glm::rotate(glm::mat4(1),angle,glm::vec3(1,0,0));
    direction = rotation * viewMatrix * direction;
}
/**
 * resetDirection()
 * with default value
 */
void Light::resetDirection(const float negative){
    direction = negative*glm::vec4(-0.5,-0.5,-0.5,0);
}
/**
 * getDirection()
 * @return glm::vec4
 */
const glm::vec4 &Light::getDirection() const {
    return direction;
}

const glm::vec3 &Light::getColor() const {
    return color;
}


