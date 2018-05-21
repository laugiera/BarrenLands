//
// Created by natshez on 28/02/2018.
//

#ifndef BARRENLANDS_TEXTTEXTURE_H
#define BARRENLANDS_TEXTTEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

/**
 * class TextTexture handles sdl textures and font
 */
class TextTexture {
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;

public:
    TextTexture();
    ~TextTexture();

#ifdef _SDL_TTF_H
    //Creates image from font string
		bool loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font *gFont, std::string textureText, SDL_Color textColor );
#endif

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(SDL_Renderer* gRenderer,  int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

};


#endif //BARRENLANDS_TEXTTEXTURE_H
