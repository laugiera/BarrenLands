#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include "glm.hpp"
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace glimac {

class SDLWindowManager {
public:
    SDLWindowManager(uint32_t width, uint32_t height, const char* title);

    ~SDLWindowManager();

    bool pollEvent(SDL_Event& e);

    bool isKeyPressed(SDL_Scancode key) const;

    // button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
    bool isMouseButtonPressed(uint32_t button) const;

    glm::ivec2 getMousePosition() const;

    void swapBuffers();

    // Return the time in seconds
    float getTime() const;

    SDL_Window *getWindow() const;

    void setWindow(SDL_Window *window);

private:
    SDL_Window* window;
    SDL_GLContext context;
};

}
