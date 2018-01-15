//
// Created by Etienne on 10/12/2017.
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
#include <glimac/FreeflyCamera.hpp>
#include "../barrenLands/include/NoiseManager.hpp"

/***
 * La map fait un carré de 100 par 100
 *
 *
 */


using namespace glimac;

int main(int argc, char** argv) {
    /***BARREN LAND ON GERE LE Nombre de Sub***/

    int nbrSub;
    std::cout << "Indiquez le nombre de carre par cote : " << std::endl;
    std::cin >> nbrSub;
    std::cout << "Nombre de subdivisions = " << nbrSub << std::endl;

    float width;
    std::cout << "Indiquez la largeur des carres : " << std::endl;
    std::cin >> width;
    std::cout << "Largeur = " << width << std::endl;

    float elevationMax;
    std::cout << "Indiquez l'elevation maximale de la map : " << std::endl;
    std::cin >> elevationMax;
    std::cout << "Hauteur max = " << elevationMax << std::endl;

    float freq;
    std::cout << "Indiquez la freq de la map : " << std::endl;
    std::cin >> freq;
    std::cout << "Freq = " << freq << std::endl;

    /******/

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
    Program program = loadProgram(applicationPath.dirPath() + "shaders/testShader.vs.glsl",
                                  applicationPath.dirPath() + "shaders/testShader.fs.glsl");
    program.use();

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
    glm::mat4 ProjMat;
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;

    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    /***On fait le tableau***/
    int i, j;
    //test génération bruit
    float** terrain = NoiseManager::getElevationMap(nbrSub+1, nbrSub+1, elevationMax, freq);

    // => Tableau de sommets : un seul exemplaire de chaque sommet
    //ShapeVertex vertices[(nbrSub+1)*(nbrSub+1)];
    std::vector<ShapeVertex> vertices;

    /*Dans la boucle qu'il suit :
     * les -10 correspondent au premier point, il sera en (-10,-10)
     * les 20 correspondent à l'indice max qui sera : (-10+20,-10+20) = (10,10)
     * Les deux peuvent être modifiés pour avoir des résultats différents !
     */


    for(i=0; i<nbrSub+1; ++i){
        for(j=0; j<nbrSub+1; j++){
            vertices.push_back(ShapeVertex(glm::vec3(-width*nbrSub/2.0+j*width, terrain[i][j], -width*nbrSub/2.0+i*width), glm::vec3(0, 0, 0), glm::vec2(i,j)));
        }
    }

    /***BARREN LAND : INDICES DES TRIANGLES***/

    //uint32_t indices[nbrSub*nbrSub*6]

    std::vector<uint32_t> indices; //C'est mon nombre de points
    /*for(i=0; i<nbrSub; ++i){
        for(j=0; j<nbrSub; ++j){
            indices[6*i*nbrSub + j*6 ] = i*nbrSub + j + i;
            indices[6*i*nbrSub + j*6 + 1] = i*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 2] = (i+1)*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 3] = i*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 4] = (i+1)*nbrSub + j + 1 + i;
            indices[6*i*nbrSub + j*6 + 5] = (i+1)*nbrSub + j + 2 + i;
        }
    }*/

    for(i=0; i<nbrSub; ++i){
        for(j=0; j<nbrSub; ++j){
            indices.push_back(i*nbrSub + j + i);
            indices.push_back(i*nbrSub + j + 1 + i);
            indices.push_back((i+1)*nbrSub + j + 1 + i);
            indices.push_back(i*nbrSub + j + 1 + i);
            indices.push_back((i+1)*nbrSub + j + 1 + i);
            indices.push_back((i+1)*nbrSub + j + 2 + i);
        }
    }

    /******/


    /*** BARREN LAND : CALCUL DES NORMALES */
    glm::vec3 dir1;
    glm::vec3 dir2;
    glm::vec3 norm;

    for(i=0; i < nbrSub*nbrSub*2; ++i){
        dir1 = vertices[indices[3*i]].position - vertices[indices[3*i+1]].position;
        dir2 = vertices[indices[3*i]].position - vertices[indices[3*i+2]].position;
        norm = glm::cross(dir1, dir2);
        vertices[indices[3*i]].normal += norm;
        vertices[indices[3*i+1]].normal += norm;
        vertices[indices[3*i+2]].normal += norm;
    }

    for(i=0; i < vertices.size(); ++i){
        vertices[indices[i]].normal = glm::normalize(vertices[indices[i]].normal);
    }



    /******/

    // => Penser à bien changer le nombre de sommet ((nbrSub+1)*(nbrSub+1) au lieu de 6):
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ShapeVertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // => Creation du IBO
    GLuint ibo;
    glGenBuffers(1, &ibo);

    // => On bind sur GL_ELEMENT_ARRAY_BUFFER, cible reservée pour les IBOs
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // => Tableau d'indices: ce sont les indices des sommets à dessiner
    // On en a 6 afin de former deux triangles
    // Chaque indice correspond au sommet correspondant dans le VBO



    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    // => Comme d'habitude on debind avant de passer à autre chose
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXTURE = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
                          sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,
                          sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE,
                          sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


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

        ProjMat = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
        glm::mat4 globalMVMatrix = Camera.getViewMatrix();
        //MVMatrix = glm::translate(glm::mat4(1.0f) , glm::vec3(0.f,-5.f,0.f));
        //MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1.0, 0));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE,
                           glm::value_ptr(globalMVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE,
                           glm::value_ptr(glm::transpose(glm::inverse(globalMVMatrix))));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE,
                           glm::value_ptr(ProjMat * globalMVMatrix));

        glBindVertexArray(vao);

        // => On utilise glDrawElements à la place de glDrawArrays
        // Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
        glDrawElements(GL_TRIANGLES, nbrSub*nbrSub*6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
