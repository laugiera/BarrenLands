//
// Created by Lou Landry on 04/11/2017.
//

#include "BL_transform.hpp"

namespace BarrenLands {

    glm::mat3 rotate(float theta) {
        theta = theta * 3.14 / 180.0;
        glm::mat3 M = glm::mat3(
                glm::vec3(cos(theta), -sin(theta), 0.0),
                glm::vec3(sin(theta), cos(theta), 0.0),
                glm::vec3(0.0, 0.0, 1.0)
        );
        return M;
    }

    glm::mat3 translate(float tx, float ty) {
        glm::mat3 M = glm::mat3(
                glm::vec3(1.0, 0.0, 0.0),
                glm::vec3(0.0, 1.0, 0.0),
                glm::vec3(tx, ty, 1.0)
        );
        return M;
    }

    glm::mat3 scale(float sx, float sy) {
        glm::mat3 M = glm::mat3(
                glm::vec3(sx, 0.0, 0.0),
                glm::vec3(0.0, sy, 0.0),
                glm::vec3(0.0, 0.0, 1.0)
        );
        return M;
    }

}