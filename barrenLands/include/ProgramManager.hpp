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

    glcustom::GPUProgram * getLightProgram() const;

private:
    std::string appPath;
    glcustom::GPUProgram * testProgram;
    glcustom::GPUProgram * lightProgram;

};


#endif //BARRENLANDS_PROGRAMMANAGER_HPP
