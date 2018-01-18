//
// Created by Lou Landry on 17/01/2018.
//

#ifndef BARRENLANDS_COLOR_HPP
#define BARRENLANDS_COLOR_HPP

#include "glm/vec3.hpp"

class Color {
public:
    Color();

    Color(float r);

    Color(float g, float b, float a);

    Color(float r, float g, float b, float a);

    inline float sanitize255(float f){
        return (f>1)? f/255.f : f;
    }

    void darken(float intensity);

    void lighten(float intensity);

    glm::vec3 getVec3();


private:
    float r;
    float g;
    float b;
    float a;

};


#endif //BARRENLANDS_COLOR_HPP
