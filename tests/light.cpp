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
#include "../barrenLands/include/NoiseManager.h"
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
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);

    //textures
    glcustom::Texture test_texture1 = glcustom::Texture(
            applicationPath.dirPath() + "textures/" + "HatchPattern-final.png");
    glcustom::Texture test_texture2 = glcustom::Texture(applicationPath.dirPath() + "textures/" + "653306852.jpg");

    /***** GPU PROGRAM *****/

    glcustom::GPUProgram program(applicationPath, "light",  "directLight");
    std::vector<std::string> uniform_variables = {"MV", "MVP","V","M","LightPosition_worldspace",
                                                  "uTexture", "uTexture2","rotation"};
    program.addUniforms(uniform_variables);
    program.use();

    //variables globales
    glm::mat4 ProjMat, MVMatrix, NormalMatrix;

    /***BARREN LAND ON GERE LE Nombre de Sub***/
    int nbrSub = 100;
    float width = 1;
    float elevationMax = 5;
    float freq = 0.05;

    /***On fait le tableau***/
    int i, j;
    //test génération bruit
    float** terrain = NoiseManager::getElevationMap(nbrSub+1, nbrSub+1, elevationMax, freq);
    //génération bruit humidité
    float** humidite = NoiseManager::getElevationMap(nbrSub+1, nbrSub+1, elevationMax, freq+0.02);
    // => Tableau de sommets : un seul exemplaire de chaque sommet
    glimac::ShapeVertex vertices[(nbrSub+1)*(nbrSub+1)];
    /*Dans la boucle qu'il suit :
     * les -10 correspondent au premier point, il sera en (-10,-10)
     * les 20 correspondent à l'indice max qui sera : (-10+20,-10+20) = (10,10)
     * Les deux peuvent être modifiés pour avoir des résultats différents !
     */
    for(i=0; i<nbrSub+1; ++i){
        for(j=0; j<nbrSub+1; j++){

            vertices[i*(nbrSub+1)+j] = glimac::ShapeVertex(glm::vec3(-width*nbrSub/2.0+j*width, terrain[i][j], -width*nbrSub/2.0+i*width), glm::vec3(0, 0, 1), glm::vec2(humidite[i][j], terrain[i][j]));

        }
    }
    std::vector<glimac::ShapeVertex> vertices_vector(vertices, vertices + (nbrSub+1)*(nbrSub+1));
    // => Tableau d'indices: ce sont les indices des sommets à dessiner
    // On en a 6 afin de former deux triangles
    // Chaque indice correspond au sommet correspondant dans le VBO
    uint32_t indices[nbrSub*nbrSub*6]; //C'est mon nombre de points
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

    // Application loop:
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
        program.sendUniformTextureUnit("uTexture", 0);
        program.sendUniformTextureUnit("uTexture2", 1);
        test_texture1.bind();
        test_texture2.bind(GL_TEXTURE1);

        ProjMat = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        glm::mat4 MobelMatrix = glm::translate(glm::mat4(1.0f) , glm::vec3(0.f,-5.f,-10.f));
        glm::mat4 ViewMatrix = Camera.getViewMatrix();
        glm::mat4 MV = ViewMatrix * MobelMatrix;
        glm::mat4 MVP = ProjMat * MV;

        glm::vec4 lightPos = glm::vec4(20,200,50,1);
        glm::mat4 rotation = glm::rotate(glm::mat4(1),windowManager.getTime(),glm::vec3(0,1,0));
        //lightPos = lightPos * rotation;

        //send uniform variables
        program.sendUniformMat4("V", ViewMatrix);
        program.sendUniformMat4("M", MobelMatrix);
        program.sendUniformMat4("MV", MV);
        program.sendUniformMat4("MVP", MVP);
        program.sendUniformVec4("LightPosition_worldspace", lightPos);
        program.sendUniformMat4("rotation",rotation);

        //draw
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices_vector.size(), GL_UNSIGNED_INT, 0);
        vao.debind();
        test_texture1.debind();
        test_texture2.debind();

        // Update the display
        windowManager.swapBuffers();
    }

    //everything is deleted automatically

    return EXIT_SUCCESS;
}
