//
// Created by Lou Landry on 17/01/2018.
//

#include "Color.hpp"

/**
 * Random constructor
 */
Color::Color() {
    //remplacer par des nb générés par la classe noise
    r = trunk01(NoiseManager::getInstance().getRandomFloat());
    g = trunk01(NoiseManager::getInstance().getRandomFloat());
    b = trunk01(NoiseManager::getInstance().getRandomFloat());
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
    float step = 1;
    r -= step*intensity;
    g -= step*intensity;
    b -= step*intensity;
}

/**
 * Lightens the color
 * @param intensity of lightening
 */
void Color::lighten(float intensity) {
    float step = 1;
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

void Color::red(float intensity) {
    float step = 1;
    r += step*intensity;
}

void Color::green(float intensity) {
    float step = 1;
    g += step*intensity;
}

void Color::blue(float intensity) {
    float step = 1;
    b += step*intensity;
}

void Color::randomSimilarColor(float intensity) {
    int component = int((NoiseManager::getInstance().getRandomFloat() + 1) * 10 ) % 3;
    float random = NoiseManager::getInstance().getRandomFloat(); //number beetween -1 and 1
    float step = 10 * intensity * random;
    switch(component){
        case 0 :
            r+=step;
            break;
        case 1:
            g += step;
            break;
        case 2 :
            b += step;
            break;
        default:
            break;
    }
    /*
    r += random * step *intensity;
    random = NoiseManager::getInstance().getRandomFloat();
    g += random * step *intensity;
    random = NoiseManager::getInstance().getRandomFloat();
    b += random * step *intensity;
     */
}

void Color::complementaryColor() {
    /*
    int component = int((NoiseManager::getInstance().getRandomFloat() + 1) * 10 ) % 3;
    switch(component) {
        case 0 :
            r = 1 - r;
            g = 1 - g;;
            break;
        case 1:
            g = 1 - g;
            b = 1 - b;
            break;
        case 2 :
            r = 1 - r;
            b = 1 - b;
            break;
        default:
            break;
    }
     */

    r = 1 - r;
    g = 1 - g;
    b = 1 - b;



}

void Color::saturate(float intensity) {
    float average = (r + g + b) / 3.f;
    r += (r-average) * intensity;
    g += (g-average) * intensity;
    b += (b-average) * intensity;
}




