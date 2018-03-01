//
// Created by natshez on 28/02/2018.
//

#ifndef BARRENLANDS_TEXTTEXTURE_H
#define BARRENLANDS_TEXTTEXTURE_H

//Using SDL, SDL_image, SDL_ttf, standard IO, strings, and string streams
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>

class TextTexture {
public:
    //Initializes variables
    TextTexture();

    //Deallocates memory
    ~TextTexture();

    //Loads image at specified path
    bool loadFromFile(SDL_Renderer* gRenderer, std::string path );

#ifdef _SDL_TTF_H
    //Creates image from font string
		bool loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font *gFont, std::string textureText, SDL_Color textColor );
#endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render(SDL_Renderer* gRenderer,  int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth();
    int getHeight();

    SDL_Texture *getMTexture() const;

    void setMTexture(SDL_Texture *mTexture);


private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;

};


#endif //BARRENLANDS_TEXTTEXTURE_H
