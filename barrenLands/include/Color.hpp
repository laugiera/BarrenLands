//
// Created by Lou Landry on 17/01/2018.
//

#ifndef BARRENLANDS_COLOR_HPP
#define BARRENLANDS_COLOR_HPP

#include "glm/vec3.hpp"
#include <string>
#include "NoiseManager.hpp"

enum {RANDOM, RED, GREEN, BLUE, ALPHA};


/**
 * Class Color
 * Manage a color and its rgb composantes
 */
class Color {
public:
    Color();

    Color(float r);

    Color(float g, float b, float a);

    Color(float r, float g, float b, float a);

    Color ( Color * c);

    /**
     * sanitize255()
     * @param float f value of rgb composante
     * @return normalised value of the composante between 0 and 1
     */
    inline float sanitize255(float f){
        f = (f > 255)? 255 : f;
        return (f>1)? f/255.f : f;
    }
    /**
     *  trunk01()
     * @param float f value of rgb composante
     * @return value trunked, between 0 and 1
     */
    inline float trunk01(float f){
        f = (f>1)? 1 : f;
        f = (f<0)? 0 : f;
        return f;
    }

    void darken(float intensity);

    void lighten(float intensity);

    void red(float intensity = 0.1);
    void green(float intensity = 0.1);
    void blue(float intensity = 0.1);

    void randomSimilarColor(float intensity = 0.1);
    void complementaryColor();

    glm::vec3 getVec3();


private:
    float r;
    float g;
    float b;
    float a;

};


#endif //BARRENLANDS_COLOR_HPP
