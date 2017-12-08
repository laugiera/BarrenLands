
#define GLEW_STATIC
#include <glimac/SDL2WindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <vector>
#include <GPUProgram.hpp>

using namespace glimac;

typedef struct Vertex2DUV{
    glm::vec2 position;
    glm::vec2 texture;
    Vertex2DUV(){}
    Vertex2DUV(glm::vec2 p, glm::vec2 t){
        position = p;
        texture = t;
    }
} Vertex2D;

glm::mat3 rotate(float theta){
    theta = theta*3.14/180.0;
    glm::mat3 M = glm::mat3(
            glm::vec3(cos(theta), -sin(theta), 0.0),
            glm::vec3(sin(theta), cos(theta), 0.0),
            glm::vec3(0.0, 0.0, 1.0)
    );
    return M;
}

glm::mat3 translate(float tx, float ty){
    glm::mat3 M = glm::mat3(
            glm::vec3(1.0, 0.0, 0.0),
            glm::vec3(0.0, 1.0, 0.0),
            glm::vec3(tx, ty, 1.0)
    );
    return M;
}

glm::mat3 scale(float sx, float sy){
    glm::mat3 M = glm::mat3(
            glm::vec3(sx, 0.0, 0.0),
            glm::vec3(0.0, sy, 0.0),
            glm::vec3(0.0, 0.0, 1.0)
    );
    return M;
}

/*********************************
 * MAIN
 *********************************/

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

    glcustom::GPUProgram test_prog(applicationPath, "uniMatrix", "uniMatrix");
    test_prog.addUniform("uColor");
    test_prog.addUniform("uModelMatrice");
    test_prog.use();



    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //uniform variables and global variables
    //matrice (uniform)
    /*
    GLint uModelMatriceLocation = glGetUniformLocation(program.getGLId(), "uModelMatrice");
    glm::mat3 uModelMatriceValue;
    glUniformMatrix3fv(uModelMatriceLocation, 1, GL_FALSE, glm::value_ptr(uModelMatriceValue) );
    //color (uniform)
    GLint uColorLocation = glGetUniformLocation(program.getGLId(), "uColor");
    glm::vec3 uColorValue = glm::vec3(0,0,0);
    glUniform3fv(uColorLocation, 1, glm::value_ptr(uColorValue));
     */
    //time counter
    float time = 0;

    //buffers
    GLuint vbo, vao;
    glGenBuffers(1,&vbo);
    glGenVertexArrays(1,&vao);

    std::vector<Vertex2DUV> vertices = {
            Vertex2DUV(glm::vec2(-1.f, -1.f), glm::vec2(0.f,0.f)),
            Vertex2DUV(glm::vec2(1.f, -1.f), glm::vec2(0.f,0.f)),
            Vertex2DUV(glm::vec2(0.f, 1.f), glm::vec2(0.f,0.f))
    };

    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex2DUV), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); //debind vbo


    //bind vao
    glBindVertexArray(vao);
    const GLuint VERTEX_ATTR_POSITION = 0;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    const GLuint VERTEX_ATTR_TEXTURE = 1;
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    //bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, position));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*)offsetof(Vertex2DUV, texture));
    //debind vbo then va
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float left = 0;
    float right = 0;
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
            if(e.type == SDL_KEYDOWN) {
                left += (e.key.keysym.sym == SDLK_LEFT)?1 : 0;
                right += (e.key.keysym.sym == SDLK_RIGHT)?1 : 0;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glBindVertexArray(vao); //bind vao
        //triangle1
        glm::mat3 modelMatrix = rotate(time)* translate(-0.5+right/10.0-left/10.0, 0.5) * scale(0.75, 0.75)*rotate(time);
        test_prog.sendUniformMat3("uModelMatrice", modelMatrix);
        test_prog.sendUniformVec3("uColor", glm::vec3(1,1,1));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //triangle2
        test_prog.sendUniformMat3("uModelMatrice", rotate(time)* translate(-0.5, -0.5) * scale(0.25, 0.25)*rotate(-time));
        test_prog.sendUniformVec3("uColor", glm::vec3(0.7,0.7,0.2));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //triangle3
        test_prog.sendUniformMat3("uModelMatrice", rotate(time)* translate(0.5, -0.5) * scale(0.75, 0.75)*rotate(time));
        test_prog.sendUniformVec3("uColor", glm::vec3(01,0.2,0));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //triangle4
        test_prog.sendUniformMat3("uModelMatrice", rotate(time)* translate(0.5, 0.5) * scale(0.25, 0.25)*rotate(-time));
        test_prog.sendUniformVec3("uColor", glm::vec3(0.5,0.2,0.6));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0); //debind vao
        windowManager.swapBuffers();
        time++;
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}

