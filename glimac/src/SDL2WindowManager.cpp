#include "glimac/SDL2WindowManager.hpp"
#include <iostream>

namespace glimac {

SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title) {

    if(0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }
    //attributes context open gl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    window = SDL_CreateWindow(title, 0, 0, width, height, SDL_WINDOW_OPENGL ); //| SDL_WINDOW_FULLSCREEN_DESKTOP

    if(!window){
      std::cerr << SDL_GetError() << std::endl;
      return;
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return;
    }

    context = SDL_GL_CreateContext(window);

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    SDL_ShowCursor(SDL_DISABLE);


}

SDLWindowManager::~SDLWindowManager() {
    SDL_GL_DeleteContext(context);
    Mix_CloseAudio(); //Fermeture de l'API
    //Quit SDL subsystems
    delete window;
    IMG_Quit();
    TTF_Quit();
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

    SDL_Window *SDLWindowManager::getWindow() const {
        return window;
    }

    void SDLWindowManager::setWindow(SDL_Window *window) {
        SDLWindowManager::window = window;
    }

}
