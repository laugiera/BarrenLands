//
// Created by Lou Landry on 17/01/2018.
//

#include "Color.hpp"

/**
 * Random constructor
 */
Color::Color() {
    //remplacer par des nb générés par la classe noise
    r = 0.5;
    g = 0.5;
    b = 0.5;
    a = 1;
}

/**
 * Grey Level contructor
 * @param r
 */
Color::Color(float r) {
    r = g = b = sanitize255(r);
    a = 1;
}

/**
 * RGB Constructor
 * @param r
 * @param g
 * @param b
 */
Color::Color(float r, float g, float b) : r(sanitize255(r)), g(sanitize255(g)), b(sanitize255(b)), a(1)  {}

/**
 * RBGA Constructor
 * @param r
 * @param g
 * @param b
 * @param a
 */
Color::Color(float r, float g, float b, float a) : r(sanitize255(r)), g(sanitize255(g)), b(sanitize255(b)), a(sanitize255(a)) {}

/**
 * Copie Constructor
 * @param c
 */
Color::Color(Color *c) : r(c->r),
                         g(c->g),
                         b(c->b),
                         a(c->a) {}

/**
 * Darkens the color
 * @param intensity of darkening
 */
void Color::darken(float intensity) {
    float step = 0.01;
    r -= step*intensity;
    g -= step*intensity;
    b -= step*intensity;
}

/**
 * Lightens the color
 * @param intensity of lightening
 */
void Color::lighten(float intensity) {
    float step = 0.01;
    r += step*intensity;
    g += step*intensity;
    b += step*intensity;
}

/**
 * Returns normalized values of the color
 * @return vec3 containing R G and B values of color
 */
glm::vec3 Color::getVec3() {
    if(!this){
        return glm::vec3(0,0,0);
    }
    return glm::vec3( trunk01(r), trunk01(g), trunk01(b) );
}


