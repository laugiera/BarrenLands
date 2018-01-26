//
// Created by natshez on 26/01/2018.
//

#include "Instance.hpp"

const glm::mat4 &Instance::getTransfo() const {
    return transfo;
}

void Instance::setTransfo(const glm::mat4 &transfo) {
    Instance::transfo = transfo;
}


 Color &Instance::getColor()  {
    return color;
}

void Instance::setColor(const Color &color) {
    Instance::color = color;
}

Instance::Instance(const glm::mat4 &transfo, const glm::vec3 &position, const Color &color) : transfo(transfo), position(position), color(color) {}

Instance::~Instance() {

}
