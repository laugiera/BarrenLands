//
// Created by natshez on 28/02/2018.
//

#ifndef BARRENLANDS_LoadHandler_H
#define BARRENLANDS_LoadHandler_H


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <TextTexture.hpp>
#include <Tools.hpp>
#include <FileHelper.hpp>

/**
 * class LoadHandler print load menu
 */
class LoadHandler {
public:
    LoadHandler(SDL_Window * gWindow);
    ~LoadHandler();
    void init(SDL_Window * gWindow);
    void loadMedia();
    int handle(std::string * loadName);

private:
    //Scene textures
    std::vector<TextTexture> gPromptTextTextures;
    TextTexture gTitleTextTexture;
    TextTexture gForwardTexture;
    TextTexture gReturnTexture;

    //The window renderer
    SDL_Renderer* gRenderer;

    //Globally used font
    TTF_Font *gFont;

    int saveNumber;
    std::vector<std::string> saveNames;

};


#endif //BARRENLANDS_LoadHandler_H
