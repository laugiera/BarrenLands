//
// Created by Lou Landry on 04/11/2017.
//

#define GLEW_STATIC
#include <glimac/SDL2WindowManager.hpp>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glimac/TrackballCamera.hpp>
#include "../barrenLands/include/NoiseManager.hpp"
#include "../barrenLands/include/CameraManager.hpp"
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include <Texture.hpp>
#include <vector>
#include "Application.hpp"
#include "TextureManager.hpp"

int main(int argc, char** argv) {

    Application app(argv[0]);
    //app.appLoop();
    app.testInterface();

    return EXIT_SUCCESS;
}


