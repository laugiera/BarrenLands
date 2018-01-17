//
// Created by Lou Landry on 04/11/2017.
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
#include <VAO.hpp>
#include <GPUProgram.hpp>
#include <Texture.hpp>
#include <vector>
#include "Application.hpp"
#include "TextureManager.hpp"

int main(int argc, char** argv) {

    Application app(argv[0]);
    app.appLoop();
    //app.testInterface();

    return EXIT_SUCCESS;
}


//
// Created by Etienne on 19/12/2017.
//

//
// Created by Lou on 16/12/2017.
//



/***
 * La map fait un carré de 100 par 100
 *
 *
 */


using namespace glimac;


int dismain(int argc, char** argv) {

    /***** SDL THINGY *****/
    // Initialize SDL and open a window
    //SDLWindowManager windowManager(800, 600, "GLImac");
    // Initialize glew for OpenGL3+ support
    /*
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
    */

    Application app(argv[0]);
    SDLWindowManager windowManager = app.getWindowManager();
    FilePath applicationPath(argv[0]);

    /***BARREN LAND ON GERE LE Nombre de Sub***/
    int nbrSub = 100;
    float width = 1;
    float elevationMax = 7;
    float freq = 0.08;
    float seed = 1200;
    NoiseManager noise(seed);

    /*****TEXTURES*****/
    TextureManager textures(applicationPath);
    textures.createTextures();
    glcustom::Texture * test_texture1 = textures.getTextures()[0];
    glcustom::Texture * test_texture2 = textures.getTextures()[1];
    /*
    glcustom::Texture test_texture1 = glcustom::Texture(
            applicationPath.dirPath() + "textures/" + "HatchPattern-final.png");
    glcustom::Texture test_texture2 = glcustom::Texture(applicationPath.dirPath() + "textures/" + "653306852.jpg");
    */

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

    //glcustom::GPUProgram program(applicationPath, "light",  "light");
    glcustom::GPUProgram program(applicationPath, "testShader",  "testShader");
    std::vector<std::string> uniform_variables = {"uMV", "uMVP", "uNormal", "uTexture"
                                                  /*"Light_cameraspace",
                                                  "uTexture", "uTexture2",
                                                  "uMoistureTexture", "uSubDiv"*/};

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

    /***TEST PROCEDURAL OBJECT***/
    ProceduralObject testObject;
    //testObject.vertices = vertices;
    //testObject.indices = indices;
    testObject.generateVertices();
    testObject.generateIndices();
    testObject.createRenderObject(&program);
    testObject.renderObject->fillData(testObject.vertices, testObject.indices);

    /***** BUFFERS *****/
    glcustom::VBO vbo = glcustom::VBO();
    glcustom::IBO ibo = glcustom::IBO();
    glcustom::VAO vao = glcustom::VAO();
    /*
    vbo.fillBuffer(testObject.vertices);
    ibo.fillBuffer(testObject.indices);
    vao.fillBuffer(testObject.vertices, &vbo, &ibo);
     */
    //vbo = testObject.renderObject->vbo;
    //ibo = testObject.renderObject->ibo;
    vao = testObject.renderObject->vao;



    /***CAMERA***/
    CameraManager camera;



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
                    camera.moveLeft(1.0);
                } else if (e.key.keysym.sym == SDLK_RIGHT) {
                    camera.moveLeft(-1.0);
                } else if (e.key.keysym.sym == SDLK_UP) {
                    camera.moveFront(1.0);
                } else if (e.key.keysym.sym == SDLK_DOWN) {
                    camera.moveFront(-1.0);
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

        app.clearGl();

        program.sendUniformTextureUnit("uTexture", 0);
        /*
        program.sendUniformTextureUnit("uTexture2", 1);
        program.sendUniformTextureUnit("uMoistureTexture", 2);
        program.sendUniform1i("uSubDiv", nbrSub);
        */
        test_texture1->bind();
         /*
        test_texture2.bind(GL_TEXTURE1);
        moisture.bind(GL_TEXTURE2);
         */
/*
        glm::vec4 lightPos = glm::vec4(-0.5,-0.5,-0.5,1);
        glm::mat4 rotation = glm::rotate(glm::mat4(1),windowManager.getTime(),glm::vec3(1,0,0));
        lightPos = rotation * ViewMatrix * lightPos;
    */
        testObject.draw(camera.getViewMatrix());
/*
        ProjMat = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        glm::mat4 MobelMatrix = glm::translate(glm::mat4(1.0f) , glm::vec3(0.f,-5.f,-10.f));
        glm::mat4 ViewMatrix = camera.getViewMatrix();
        glm::mat4 MV = ViewMatrix * MobelMatrix;
        glm::mat4 MVP = ProjMat * MV;

        //send uniform variables
        program.sendUniformMat4("uMV", MV);
        program.sendUniformMat4("uMVP", MVP);
        program.sendUniformMat4("uNormal", MVP);
        //program.sendUniformVec4("Light_cameraspace", lightPos);
        //draw
        vao.bind();
        //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glDrawElements(GL_TRIANGLES, testObject.indices.size(), GL_UNSIGNED_INT, 0);
        vao.debind();
        */
        test_texture1->debind();
        /*
        test_texture2.debind();
        moisture.debind();
         */

        // Update the display
        windowManager.swapBuffers();
    }

    //everything is deleted automatically

    return EXIT_SUCCESS;
}

