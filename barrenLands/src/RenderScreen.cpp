//
// Created by Lou Landry on 29/01/2018.
//

#include "RenderScreen.hpp"

RenderScreen::RenderScreen(glcustom::GPUProgram *program, std::vector<glcustom::Texture *> textures) : program(program),
                                                                                         textures(textures),
                                                                                         vao()
{
    createScreenVAO();
}

void RenderScreen::createScreenVAO() {
    std::vector<glimac::ShapeVertex> vertices = {
            glimac::ShapeVertex(glm::vec3(-1,1,0), glm::vec3(0), glm::vec2(0,1)),
            glimac::ShapeVertex(glm::vec3(1,1,0), glm::vec3(0), glm::vec2(1,1)),
            glimac::ShapeVertex(glm::vec3(-1,-1,0), glm::vec3(0), glm::vec2(0,0)),
            glimac::ShapeVertex(glm::vec3(1,1,0), glm::vec3(0), glm::vec2(1,1)),
            glimac::ShapeVertex(glm::vec3(-1,-1,0), glm::vec3(0), glm::vec2(0,0)),
            glimac::ShapeVertex(glm::vec3(1,-1,0), glm::vec3(0), glm::vec2(1,0))
    };
    glcustom::VBO vbo;
    vbo.fillBuffer(vertices);
    vao.fillBuffer(vertices, &vbo);
}

void RenderScreen::setTexture(glcustom::Texture * t){
    textures.clear();
    textures.push_back(t);
}

void RenderScreen::render(glcustom::FBO *fbo) {
    if(fbo){
        fbo->bind();
        //fbo->clear();
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    program->use();
    sendUniforms();
    bindTextures();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.debind();
    debindTextures();
}

void RenderScreen::bindTextures() {
    int textureUnit = GL_TEXTURE0;
    int i = 0;
    for(glcustom::Texture * texture : textures){
        texture->bind(GL_TEXTURE_2D, textureUnit+i);
        program->sendUniformTextureUnit("uTexture" + std::to_string(i), i);
        i++;
    }
}

void RenderScreen::debindTextures() {
    for(glcustom::Texture * texture : textures){
        texture->debind(GL_TEXTURE_2D);
    }
}

void RenderScreen::sendUniforms() {
    program->sendUniform1f("uZNear", Tools::zNear);
    program->sendUniform1f("uZFar", Tools::zFar);
}

void RenderScreen::render(GLuint fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    program->use();
    sendUniforms();
    bindTextures();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    vao.debind();
    debindTextures();
}
