//
// Created by Lou Landry on 04/11/2017.
//

#define GLEW_STATIC
#include <iostream>
#include <glimac/Sphere.hpp>
#include "Application.hpp"

using namespace glimac;

int main(int argc, char** argv) {

    Application app(argv[0]);
    app.appLoop();

    return EXIT_SUCCESS;
}