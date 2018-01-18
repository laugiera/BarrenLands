//
// Created by Lou Landry on 17/01/2018.
//

#include "Color.hpp"

Color::Color() {
    //remplacer par des nb générés par la classe noise
    r = 0.5;
    g = 0.5;
    b = 0.5;
    a = 1;
}

Color::Color(float r) {
    r = g = b = sanitize255(r);
    a = 1;
}

Color::Color(float r, float g, float b) : a(sanitize255(r)), g(sanitize255(g)), b(sanitize255(b)), a(1)  {}

Color::Color(float r, float g, float b, float a) : r(sanitize255(r)), g(sanitize255(g)), b(sanitize255(b)), a(sanitize255(a)) {}

void Color::darken(float intensity) {
    float step = 0.01;
    r -= step*intensity;
    g -= step*intensity;
    b -= step*intensity;
}

void Color::lighten(float intensity) {
    float step = 0.01;
    r += step*intensity;
    g += step*intensity;
    b += step*intensity;
}
