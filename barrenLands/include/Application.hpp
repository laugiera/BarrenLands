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
#include "ElementManager.hpp"
#include "ProceduralSea.hpp"
#include <FBO.hpp>
#include "RenderScreen.hpp"

/**
 * Class Application
 * main class of the project
 */

class Application {
public:
    Application(const glimac::FilePath &appPath);

    virtual ~Application();

    void initOpenGl();
    void clearGl();
    void appLoop();
    void testInterface();
    void printErrors();
    void addDOF(glcustom::Texture *text, glcustom::Texture *depth);


    const glimac::SDLWindowManager &getWindowManager() const;

private:
    glimac::SDLWindowManager windowManager;
    std::vector<ProceduralObject*> objects;
    ProgramManager * programManager;
    CameraManager * camera;
    TextureManager * textureManager;
    NoiseManager * noiseManager;

    void uniformLightDistribution(float diam, int x, int y, float * originalColor, float *newColor);
};


#endif //BARRENLANDS_APPLICATION_HPP
