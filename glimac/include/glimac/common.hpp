#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
	float	moisture;

	ShapeVertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texpos, float _moisture = 0)
		: position(pos), normal(normal), texCoords(texpos), moisture(_moisture) {}
	ShapeVertex(){}
};

}
