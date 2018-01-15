//
// Created by Lou Landry on 04/11/2017.
//

#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/SDL2WindowManager.hpp>
#include "include/BL_transform.hpp"
#include "NoiseManager.hpp"
#include "Application.hpp"

using namespace glimac;

int main(int argc, char** argv) {

    Application app;
    app.appLoop();
    
    return EXIT_SUCCESS;
}