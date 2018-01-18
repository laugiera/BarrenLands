//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROGRAMMANAGER_HPP
#define BARRENLANDS_PROGRAMMANAGER_HPP


#include <GPUProgram.hpp>
#include <Light.hpp>

class ProgramManager {
public:
    ProgramManager(const std::string &appPath);

    virtual ~ProgramManager();

    glcustom::GPUProgram *getTestProgram() const;

    void createPrograms();

    glcustom::GPUProgram * getElementProgram() const;

    glcustom::GPUProgram *getSkyboxProgram() const;

    glcustom::GPUProgram *getMapProgram() const;

    void reloadPrograms();
private:
    glimac::FilePath appPath;
    glcustom::GPUProgram * testProgram;
    glcustom::GPUProgram * elementProgram;
    glcustom::GPUProgram * skyboxProgram;
    glcustom::GPUProgram * mapProgram;

};


#endif //BARRENLANDS_PROGRAMMANAGER_HPP
