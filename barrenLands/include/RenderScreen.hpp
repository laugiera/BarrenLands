//
// Created by Lou Landry on 29/01/2018.
//

#ifndef BARRENLANDS_RENDERSCREEN_HPP
#define BARRENLANDS_RENDERSCREEN_HPP

#include <VAO.hpp>
#include <GPUProgram.hpp>
#include <Texture.hpp>
#include <FBO.hpp>
#include "Tools.hpp"

class RenderScreen {
public:
    RenderScreen(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> textures);

    void createScreenVAO();
    void render(glcustom::FBO * fbo = nullptr);
    void render(GLuint fbo);
    void bindTextures();
    void debindTextures();
    void sendUniforms();
    void setTexture(glcustom::Texture * t);

private:
    glcustom::VAO vao;
    glcustom::GPUProgram * program;
    std::vector<glcustom::Texture *> textures;

};


#endif //BARRENLANDS_RENDERSCREEN_HPP
