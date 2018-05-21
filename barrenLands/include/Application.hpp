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
#include <FileHelper.hpp>
#include <RoundRock.hpp>/*
#include "ProceduralGrass.hpp"
#include "ProceduralBranche.hpp"
#include "ProceduralFeuillage.hpp"
#include "ProceduralTree.hpp"*/
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <MenuManager.hpp>
/**
 * Class Application
 * main class of the project
 */

class MenuManager;

class Application {
public:
    Application(const glimac::FilePath &appPath);
    virtual ~Application();

    void initOpenGl();
    void clearGl();
    int appLoop();
    void printErrors();
    void addDOF(glcustom::Texture *text, glcustom::Texture *depth, glcustom::FBO &fbo, glm::vec3 &lightColor,  glm::vec4 &lightDir);
    int start();
    void load(const std::string & fileName);
    void save(const int & choosenSave);
    static void play(glimac::FilePath f);
    void swapSDLBuffers(){
        this->windowManager.swapBuffers();
    }

    /**getters and setters**/
    const glimac::SDLWindowManager &getWindowManager() const;
    ProgramManager *getProgramManager() const;
    TextureManager *getTextureManager() const;

private:
    glimac::SDLWindowManager windowManager;
    ProgramManager * programManager;
    CameraManager * camera;
    TextureManager * textureManager;
    MenuManager * menuManager;
    float lightAngle;

    //void uniformLightDistribution(float diam, int x, int y, float * originalColor, float *newColor);
};


#endif //BARRENLANDS_APPLICATION_HPP
