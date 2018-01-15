//
// Created by Lou on 16/12/2017.
//

#define GLEW_STATIC
#include <glimac/SDL2WindowManager.hpp>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <memory>
#include <glimac/Sphere.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include "../barrenLands/include/NoiseManager.hpp"
#include "../barrenLands/src/NoiseManager.cpp"
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include <Texture.hpp>
#include <vector>

/***
 * La map fait un carré de 100 par 100
 *
 *
 */


using namespace glimac;


int main(int argc, char** argv) {
    /***** SDL THINGY *****/
    SDLWindowManager windowManager(800, 600, "GLImac");
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    FilePath applicationPath(argv[0]);

    /*****BARREN LAND ON GERE LE Nombre de Sub*****/
    int nbrSub = 100;
    float width = 1;
    float elevationMax = 7;
    float freq = 0.08;
    NoiseManager noiseManager(1200);

    /*****TEXTURES*****/
    glcustom::Texture test_texture1 = glcustom::Texture(
            applicationPath.dirPath() + "textures/" + "HatchPattern-final.png");
    glcustom::Texture test_texture2 = glcustom::Texture(applicationPath.dirPath() + "textures/" + "653306852.jpg");

    /***TEXTURE MOISTURE***/
    float** humidite = noiseManager.getElevationMap(nbrSub+1, nbrSub+1, freq-0.03, elevationMax);
    std::vector<float> moistureVector;
    for(int i = 0; i < nbrSub+1; i++){
        for(int j = 0 ; j < nbrSub+1; j++){
            moistureVector.push_back(humidite[i][j]);
            std::cout << humidite[i][j] << std::endl;
        }
    }
    glcustom::Texture moisture = glcustom::Texture(nbrSub+1, nbrSub+1, moistureVector.data(), GL_RED);

    /***** GPU PROGRAM *****/
    glcustom::GPUProgram program(applicationPath, "testBiomeTexture",  "testBiomeTexture");
    std::vector<std::string> uniform_variables = {"uMVMatrix", "uMVPMatrix", "uNormalMatrix", "uTexture", "uTexture2", "uMoistureTexture", "uSubDiv"};
    program.addUniforms(uniform_variables);
    program.use();

    //variables globales
    glm::mat4 ProjMat, MVMatrix, NormalMatrix;



    /***On fait le tableau***/
    int i, j;
    float** terrain = noiseManager.getElevationMap(nbrSub+1, nbrSub+1, freq, elevationMax);
    glimac::ShapeVertex vertices[(nbrSub+1)*(nbrSub+1)];
    for(i=0; i<nbrSub+1; ++i){
        for(j=0; j<nbrSub+1; j++){
            vertices[i*(nbrSub+1)+j] = glimac::ShapeVertex(glm::vec3(-width*nbrSub/2.0+j*width, terrain[i][j], -width*nbrSub/2.0+i*width), glm::vec3(0, 0, 1), glm::vec2(i, j));
        }
    }
    std::vector<glimac::ShapeVertex> vertices_vector(vertices, vertices + (nbrSub+1)*(nbrSub+1));
    uint32_t indices[nbrSub*nbrSub*6];
    for(i=0; i<nbrSub; ++i){
        for(j=0; j<nbrSub; ++j){
            indices[6*i*nbrSub + j*6 ] = i*nbrSub + j + i;
            indices[6*i*nbrSub + j*6 + 1] = i*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 2] = (i+1)*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 3] = i*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 4] = (i+1)*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 5] = (i+1)*nbrSub + j + 2 + i;
        }
    }
    std::vector<uint32_t> indices_vector(indices, indices + nbrSub*nbrSub*6);


    /***** BUFFERS *****/
    glcustom::VBO vbo = glcustom::VBO();
    glcustom::IBO ibo = glcustom::IBO();
    glcustom::VAO vao = glcustom::VAO();
    vbo.fillBuffer(vertices_vector);
    ibo.fillBuffer(indices_vector);
    vao.fillBuffer(vertices_vector, &vbo, &ibo);

    /***CAMERA***/
    TrackballCamera Camera;



    /*****INPUT*****/
    int rightPressed = 0;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_LEFT){
                    Camera.rotateLeft(5.0);
                }
                else if(e.key.keysym.sym == SDLK_RIGHT){
                    Camera.rotateLeft(-5.0);
                }
                else if(e.key.keysym.sym == SDLK_UP){
                    Camera.rotateUp(5.0);
                }
                else if(e.key.keysym.sym == SDLK_DOWN){
                    Camera.rotateUp(-5.0);
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN) {
                if(e.button.button == SDL_BUTTON_RIGHT){
                    rightPressed = 1;
                }
            }
            else if(e.wheel.y == 1 )
                Camera.moveFront(-1);
            else if(e.wheel.y == -1)
                Camera.moveFront(1);
            else if(e.type == SDL_MOUSEBUTTONUP) {
                if(e.button.button == SDL_BUTTON_RIGHT){
                    rightPressed = 0;
                }
            }
            else if (e.type == SDL_MOUSEMOTION && rightPressed == 1){
                Camera.rotateLeft(e.motion.xrel);
                Camera.rotateUp(e.motion.yrel);
            }

            else if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }


        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(99.f/255.f,25.f/255.f,9.f/255.f,1);
        program.sendUniformTextureUnit("uTexture", 0);
        program.sendUniformTextureUnit("uTexture2", 1);
        program.sendUniformTextureUnit("uMoistureTexture", 2);
        test_texture1.bind();
        test_texture2.bind(GL_TEXTURE1);
        moisture.bind(GL_TEXTURE2);
        ProjMat = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        glm::mat4 MVMatrix = glm::translate(glm::mat4(1.0f) , glm::vec3(0.f,-5.f,-10.f));
        glm::mat4 globalMVMatrix = Camera.getViewMatrix()*MVMatrix;
        //send uniform variables
        program.sendUniform1i("uSubDiv", nbrSub);
        program.sendUniformMat4("uMVMatrix", globalMVMatrix);
        program.sendUniformMat4("uMVPMatrix", ProjMat * globalMVMatrix);
        program.sendUniformMat4("uNormalMatrix", glm::transpose(glm::inverse(globalMVMatrix)));

        //draw
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices_vector.size(), GL_UNSIGNED_INT, 0);
        vao.debind();
        test_texture1.debind();
        test_texture2.debind();
        moisture.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //everything is deleted automatically

    return EXIT_SUCCESS;
}
