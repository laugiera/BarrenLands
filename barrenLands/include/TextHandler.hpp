//
// Created by natshez on 28/02/2018.
//

#ifndef BARRENLANDS_TEXTHANDLER_H
#define BARRENLANDS_TEXTHANDLER_H

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <TextTexture.hpp>
#include <Tools.hpp>


class TextHandler {
public:
    TextHandler(SDL_Window * gWindow);
    ~TextHandler();
    //Starts up SDL and creates window
    bool init(SDL_Window * gWindow);
    //Loads media
    bool loadMedia();
    int handle(std::string * inputText);

private:


    //Scene textures
    TextTexture gPromptTextTexture;
    TextTexture gInputTextTexture;
    TextTexture gForwardTexture;
    TextTexture gReturnTexture;

    //The window renderer
    SDL_Renderer* gRenderer;

    //Globally used font
    TTF_Font *gFont;

};


#endif //BARRENLANDS_TEXTHANDLER_H
