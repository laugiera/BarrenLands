//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_APPLICATION_HPP
#define BARRENLANDS_APPLICATION_HPP

#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "glimac/SDL2WindowManager.hpp"
#include "Tools.hpp"
#include "SkyboxObject.hpp"
#include "ProgramManager.hpp"
#include "CameraManager.hpp"
#include "TextureManager.hpp"
#include "NoiseManager.hpp"
#include "ProceduralMap.hpp"
#include "ElementFactory.hpp"

class Application {
public:
    Application(const glimac::FilePath &appPath);

    virtual ~Application();

    int initOpenGl();
    void clearGl();
    void appLoop();
    void testInterface();
    void printErrors();

    const glimac::SDLWindowManager &getWindowManager() const;

private:
    glimac::SDLWindowManager windowManager;
    std::vector<ProceduralObject*> objects;
    ProgramManager * programManager;
    CameraManager * camera;
    TextureManager * textureManager;
    NoiseManager * noiseManager;
};


#endif //BARRENLANDS_APPLICATION_HPP
