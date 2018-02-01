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

    try {
        glimac::FilePath f = argv[0];
        Tools::appPath = f.dirPath();
        Application::play(f);


       // Application app = Application(f);
       // app.appLoop();
        //app.testInterface();

    }catch (std::runtime_error e) {
        std::cerr << e.what() <<std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
