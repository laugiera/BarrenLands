//
// Created by natshez on 28/02/2018.
//

#ifndef BARRENLANDS_SaveHandler_H
#define BARRENLANDS_SaveHandler_H

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
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
 * class SaveHandler print the save menu
 */
class SaveHandler {
public:
    SaveHandler(SDL_Window * gWindow);
    ~SaveHandler();
    //Starts up SDL and creates window
    void init(SDL_Window * gWindow);
    void loadMedia();
    int handle(int * choosenSave);

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

    std::vector<std::string> saveNames;

};


#endif //BARRENLANDS_SaveHandler_H
