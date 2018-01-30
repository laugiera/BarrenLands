//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROGRAMMANAGER_HPP
#define BARRENLANDS_PROGRAMMANAGER_HPP


#include <GPUProgram.hpp>
#include <Light.hpp>
/**
 * Class ProgramManager
 * Initialise and manage all GPU Program of the app with their uniforms variables
 */
class ProgramManager {
public:
    ProgramManager(const std::string &appPath);

    virtual ~ProgramManager();

    glcustom::GPUProgram *getTestProgram() const;

    void createPrograms();

    glcustom::GPUProgram * getElementProgram() const;

    glcustom::GPUProgram *getSkyboxProgram() const;

    glcustom::GPUProgram *getMapProgram() const;

    glcustom::GPUProgram *getTexture2DProgram() const;

    glcustom::GPUProgram *getDOFProgram() const;

    glcustom::GPUProgram *getShadowProgram() const;

    void reloadPrograms();
private:
    glimac::FilePath appPath;
    glcustom::GPUProgram * testProgram;
    glcustom::GPUProgram * elementProgram;
    glcustom::GPUProgram * skyboxProgram;
    glcustom::GPUProgram * mapProgram;
    glcustom::GPUProgram * texture2DProgram;
    glcustom::GPUProgram * DOFProgram;
    glcustom::GPUProgram * shadowProgram;

};


#endif //BARRENLANDS_PROGRAMMANAGER_HPP
