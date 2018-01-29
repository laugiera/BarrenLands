//
// Created by natshez on 26/01/2018.
//

#ifndef BARRENLANDS_INSTANCE_H
#define BARRENLANDS_INSTANCE_H

#include <glimac/glm.hpp>
#include <Color.hpp>

class Instance {

public:
    Instance(const glm::mat4 &transfo, const glm::vec3 &position, const Color &color);

    virtual ~Instance();

    const glm::mat4 &getTransfo() const;

    void setTransfo(const glm::mat4 &transfo);

    void setColor(const Color &color);

     Color &getColor();

    glm::vec3 position;

private:
    glm::mat4 transfo;
    Color color;
};


#endif //BARRENLANDS_INSTANCE_H
