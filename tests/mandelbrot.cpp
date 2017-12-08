#define GLEW_STATIC
#include <glimac/SDL2WindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <vector>

using namespace glimac;

typedef struct Vertex2D{
  glm::vec2 position;
  Vertex2D(){}
  Vertex2D(glm::vec2 p){
    position = p;
  }
} Vertex2D;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(600, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/mandelbrot.vs.glsl",
                                    applicationPath.dirPath() + "shaders/mandelbrot.fs.glsl");
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
     GLuint vbo, vao, ibo;
     glGenBuffers(1,&vbo);
     glGenVertexArrays(1,&vao);
     glGenBuffers(1,&ibo);

     std::vector<Vertex2D> vertices = {
        Vertex2D(glm::vec2(-1.f, 1.f)),
        Vertex2D(glm::vec2(1.f, 1.f)),
        Vertex2D(glm::vec2(1.f, -1.f)),
        Vertex2D(glm::vec2(-1.f, -1.f))
      };


    std::vector<uint32_t> indices = {0,3,1,1,3,2};


     glBindBuffer(GL_ARRAY_BUFFER, vbo);
     glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

     glBindVertexArray(vao);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
     const GLuint VERTEX_ATTR_POSITION = 0;
     glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
     //const GLuint VERTEX_ATTR_COLOR = 1;
     //glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

     glBindBuffer(GL_ARRAY_BUFFER, vbo);

     glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);

     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        //while(windowManager.pollEvent(e)) {
        //
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

         glClear(GL_COLOR_BUFFER_BIT);
         glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
         glBindVertexArray(vao);
         glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT, 0);
         glBindVertexArray(0);

        windowManager.swapBuffers();
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
