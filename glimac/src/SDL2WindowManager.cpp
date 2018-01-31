#include "glimac/SDL2WindowManager.hpp"
#include <iostream>

namespace glimac {

SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title) {

    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }
    //attributes context open gl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    window = SDL_CreateWindow(title, 100, 100, width, height, SDL_WINDOW_OPENGL);
    if(!window){
      std::cerr << SDL_GetError() << std::endl;
      return;
    }
    context = SDL_GL_CreateContext(window);
    //can use
    //SDL_WINDOWPOS_UNDEFINED
    //SDL_WINDOWPOS_CENTERED

}

SDLWindowManager::~SDLWindowManager() {
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}

bool SDLWindowManager::pollEvent(SDL_Event& e) {
    return SDL_PollEvent(&e);
}

bool SDLWindowManager::isKeyPressed(SDL_Scancode key) const {
    return SDL_GetKeyboardState(NULL)[key];
}

// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

glm::ivec2 SDLWindowManager::getMousePosition() const {
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}

void SDLWindowManager::swapBuffers() {
    //std::cout << "test 3" << std::endl;
    SDL_GL_SwapWindow(window);
}

float SDLWindowManager::getTime() const {
    return 0.001f * SDL_GetTicks();
}

}
