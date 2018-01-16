//
// Created by Etienne on 19/12/2017.
//

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
#include <glimac/FreeflyCamera.hpp>
#include <glimac/TrackballCamera.hpp>
#include "../barrenLands/include/NoiseManager.hpp"
#include "../barrenLands/include/CameraManager.hpp"
#include "../barrenLands/src/CameraManager.cpp"
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

void conversionIndice(float x, float z, int &i, int &j, float width, int nbrSub){
    i = x + width*nbrSub/2;
    j = z + width*nbrSub/2;
}


float hauteurMoyenne(std::vector<ShapeVertex> vect, int i, int j, int nbrSub){
    float hauteur = 0;
    hauteur += vect[i*(nbrSub+1)+j].position.y; //point du centre

    return hauteur;
}

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

    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    FilePath applicationPath(argv[0]);

    /***BARREN LAND ON GERE LE Nombre de Sub***/
    int nbrSub = 100;
    float width = 1;
    float elevationMax = 7;
    float freq = 0.08;
    float seed = 1200;
    NoiseManager noise(seed);

    /*****TEXTURES*****/
    glcustom::Texture test_texture1 = glcustom::Texture(
            applicationPath.dirPath() + "textures/" + "HatchPattern-final.png");
    glcustom::Texture test_texture2 = glcustom::Texture(applicationPath.dirPath() + "textures/" + "653306852.jpg");


    /***TEXTURE MOISTURE***/
    float** humidite = noise.getElevationMap(nbrSub+1, nbrSub+1, freq-0.03, elevationMax);
    std::vector<float> moistureVector;
    for(int i = 0; i < nbrSub+1; i++){
        for(int j = 0 ; j < nbrSub+1; j++){
            moistureVector.push_back(humidite[i][j]);
        }
    }
    glcustom::Texture moisture = glcustom::Texture(nbrSub+1, nbrSub+1, moistureVector.data(), GL_RED);

    /***** GPU PROGRAM *****/

    glcustom::GPUProgram program(applicationPath, "light",  "light");
    std::vector<std::string> uniform_variables = {"MV", "MVP","Light_cameraspace",
                                                  "uTexture", "uTexture2",
                                                  "uMoistureTexture", "uSubDiv"};

    program.addUniforms(uniform_variables);
    program.use();

    //variables globales
    glm::mat4 ProjMat, MVMatrix, NormalMatrix;

    /***On fait le tableau***/

    int i, j;
    //test génération bruit
    float** terrain = noise.getElevationMap(nbrSub+1, nbrSub+1);

    std::vector<ShapeVertex> vertices;

    for(i=0; i<nbrSub+1; ++i){
        for(j=0; j<nbrSub+1; j++){
            vertices.push_back(ShapeVertex(
                    glm::vec3(-width*nbrSub/2.0+j*width, terrain[i][j], -width*nbrSub/2.0+i*width),
                    glm::vec3(0, 0, 0),
                    glm::vec2(i, j)
            ));
        }
    }

    /***BARREN LAND : INDICES DES TRIANGLES***/


    std::vector<uint32_t> indices; //C'est mon nombre de points

    for(i=0; i<nbrSub; ++i){
        for(j=0; j<nbrSub; ++j){
            indices.push_back(i*nbrSub + j + i); //0
            indices.push_back(i*nbrSub + j + 1 + i); //1
            indices.push_back((i+1)*nbrSub + j + 1 + i);  //2
            indices.push_back(i*nbrSub + j + 1 + i); //1
            indices.push_back((i+1)*nbrSub + j + 1 + i); //2
            indices.push_back((i+1)*nbrSub + j + 2 + i); //3
        }
    }

    /******/


    /*** BARREN LAND : CALCUL DES NORMALES */
    glm::vec3 dir1;
    glm::vec3 dir2;
    glm::vec3 norm;

    for(i=0; i < nbrSub*nbrSub*2; ++i){
        if(i%2 == 0){
            dir1 = vertices[indices[3*i+1]].position - vertices[indices[3*i]].position;
            dir2 = vertices[indices[3*i+2]].position - vertices[indices[3*i]].position;
        }
        else{
            dir1 = vertices[indices[3*i]].position - vertices[indices[3*i+1]].position;
            dir2 = vertices[indices[3*i+2]].position - vertices[indices[3*i+1]].position;
        }
        norm = glm::normalize(glm::cross(dir2, dir1));
        vertices[indices[3*i]].normal += norm;
        vertices[indices[3*i+1]].normal += norm;
        vertices[indices[3*i+2]].normal += norm;


    }

    for(i=0; i < vertices.size(); ++i){
        vertices[indices[i]].normal = glm::normalize(vertices[indices[i]].normal);
    }

    /******/

    /***** BUFFERS *****/
    glcustom::VBO vbo = glcustom::VBO();
    glcustom::IBO ibo = glcustom::IBO();
    glcustom::VAO vao = glcustom::VAO();

    vbo.fillBuffer(vertices);
    ibo.fillBuffer(indices);
    vao.fillBuffer(vertices, &vbo, &ibo);

    /***CAMERA***/
    float scale = 100;
    //std::cout << vertices[int(vertices.size()/float(2))].position << std::endl;
    glm::vec3 pos = vertices[int(vertices.size()/float(2))].position;
    pos.y = pos.y*scale + 4; //Pour être un peu plus haut que le sol
    CameraManager camera(pos);

    //Pour récupérer la position de la caméra sur le tableau !

    int camx, camy;
    int &ref = camx;
    int &ref2 = camy;
    conversionIndice(camera.getPosition().x, camera.getPosition().z, ref, ref2, width, nbrSub);
    std::cout << ref*(nbrSub+1) + ref2 << std::endl;
    std::cout << int(vertices.size()/float(2)) << std::endl;
    //CameraManager camera;
    /*int camera = 0;
    TrackballCamera Camera1;
    FreeflyCamera Camera2;*/

    // Application loop:
    int rightPressed = 0;
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_LEFT) {
                    camera.moveLeft(4.0, nbrSub, width, scale, hauteurMoyenne(vertices, ref2, ref, nbrSub)+0.2);
                    conversionIndice(camera.getPosition().x/scale, camera.getPosition().z/scale, ref, ref2, width, nbrSub);
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    camera.moveLeft(-4.0, nbrSub, width, scale, hauteurMoyenne(vertices, ref2, ref, nbrSub)+0.2);
                    conversionIndice(camera.getPosition().x/scale, camera.getPosition().z/scale, ref, ref2, width, nbrSub);
                } else if (e.key.keysym.sym == SDLK_UP) {
                    camera.moveFront(4.0, nbrSub, width, scale, hauteurMoyenne(vertices, ref2, ref, nbrSub)+0.2);
                    conversionIndice(camera.getPosition().x/scale, camera.getPosition().z/scale, ref, ref2, width, nbrSub);
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    camera.moveFront(-4.0, nbrSub, width, scale, hauteurMoyenne(vertices, ref2, ref, nbrSub)+0.2);
                    conversionIndice(camera.getPosition().x/scale, camera.getPosition().z/scale, ref, ref2, width, nbrSub);
                }
                if (e.key.keysym.sym == SDLK_v) {
                    if(camera.getChoice() == 0){
                        camera.setChoice(1);
                    }
                    else{
                        camera.setChoice(0);
                    }
                }
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    rightPressed = 1;
                }
            } else if (e.wheel.y == 1)
                camera.zoom(-1);
            else if (e.wheel.y == -1)
                camera.zoom(1);
            else if (e.type == SDL_MOUSEBUTTONUP) {
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    rightPressed = 0;
                }
            } else if (e.type == SDL_MOUSEMOTION && rightPressed == 1) {
                camera.rotateLeft(e.motion.xrel);
                camera.rotateUp(e.motion.yrel);
            } else if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        program.sendUniformTextureUnit("uTexture", 0);
        program.sendUniformTextureUnit("uTexture2", 1);
        program.sendUniformTextureUnit("uMoistureTexture", 2);
        program.sendUniform1i("uSubDiv", nbrSub);
        test_texture1.bind();
        test_texture2.bind(GL_TEXTURE1);
        moisture.bind(GL_TEXTURE2);

        ProjMat = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 1500.f);
        glm::mat4 MobelMatrix = glm::translate(glm::mat4(1.0f) , glm::vec3(0.f,-5.f,-10.f));
        MobelMatrix = glm::scale(MobelMatrix , glm::vec3(scale,scale,scale));
        glm::mat4 ViewMatrix = camera.getViewMatrix();;
        glm::mat4 MV = ViewMatrix * MobelMatrix;
        glm::mat4 MVP = ProjMat * MV;

        glm::vec4 lightPos = glm::vec4(-0.5,-0.5,-0.5,1);
        glm::mat4 rotation = glm::rotate(glm::mat4(1),windowManager.getTime(),glm::vec3(1,0,0));
        lightPos = rotation * ViewMatrix * lightPos;

        //send uniform variables
        program.sendUniformMat4("MV", MV);
        program.sendUniformMat4("MVP", MVP);
        program.sendUniformVec4("Light_cameraspace", lightPos);
        //draw
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
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

