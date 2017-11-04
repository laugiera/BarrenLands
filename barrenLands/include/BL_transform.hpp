//
// Created by Lou Landry on 04/11/2017.
//

#ifndef BARRENLANDSMASTER_TRANSFORM_H
#define BARRENLANDSMASTER_TRANSFORM_H

#include <glimac/glm.hpp>

namespace BarrenLands {

    glm::mat3 rotate(float theta);

    glm::mat3 translate(float tx, float ty);

    glm::mat3 scale(float sx, float sy);

}

#endif //BARRENLANDSMASTER_TRANSFORM_H
