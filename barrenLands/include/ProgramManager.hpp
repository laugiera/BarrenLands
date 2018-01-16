//
// Created by Lou Landry on 15/01/2018.
//

#ifndef BARRENLANDS_PROGRAMMANAGER_HPP
#define BARRENLANDS_PROGRAMMANAGER_HPP


#include <GPUProgram.hpp>

class ProgramManager {
public:
    ProgramManager(const std::string &appPath);

    virtual ~ProgramManager();

    glcustom::GPUProgram *getTestProgram() const;

    void createPrograms();
    void configureLight(glcustom::GPUProgram *program, std::string name);
    void reloadPrograms();
private:
    glimac::FilePath appPath;
    glcustom::GPUProgram * testProgram;

};


#endif //BARRENLANDS_PROGRAMMANAGER_HPP
