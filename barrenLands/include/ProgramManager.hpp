//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROGRAMMANAGER_HPP
#define BARRENLANDS_PROGRAMMANAGER_HPP


#include <GPUProgram.hpp>
#include <Light.hpp>
#include "Tools.hpp"
/**
 * Class ProgramManager
 * Initialise and manage all GPU Program of the app with their uniforms variables
 */
class ProgramManager {
public:
    ProgramManager();

    virtual ~ProgramManager();

    glcustom::GPUProgram *getTestProgram() const;

    void createPrograms();

    glcustom::GPUProgram * getElementProgram() const;

    glcustom::GPUProgram *getSkyboxProgram() const;

    glcustom::GPUProgram *getMapProgram() const;

    glcustom::GPUProgram *getTexture2DProgram() const;

    glcustom::GPUProgram *getDOFProgram() const;

    glcustom::GPUProgram *getBlurProgram() const;

    glcustom::GPUProgram *getGammaProgram() const;


    void reloadPrograms();
private:
    glcustom::GPUProgram * testProgram;
    glcustom::GPUProgram * elementProgram;
    glcustom::GPUProgram * skyboxProgram;
    glcustom::GPUProgram * mapProgram;
    glcustom::GPUProgram * texture2DProgram;
    glcustom::GPUProgram * DOFProgram;
    glcustom::GPUProgram * BlurProgram;
    glcustom::GPUProgram * GammaProgram;

};


#endif //BARRENLANDS_PROGRAMMANAGER_HPP
