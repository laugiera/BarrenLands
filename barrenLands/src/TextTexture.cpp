//
// Created by natshez on 28/02/2018.
//

#include <SDL_render.h>
#include <include/TextTexture.hpp>
#include "TextTexture.hpp"
/**
 * constructor
 */
TextTexture::TextTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}
/**
 * destructor
 */
TextTexture::~TextTexture()
{
    //Deallocate
    free();
}
/**
 * loadFromRenderedText()
 * load a textures printing a given text
 */
#ifdef _SDL_TTF_H
bool TextTexture::loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font *gFont, std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }


    //Return success
    return mTexture != NULL;
}
#endif
/**
 * free a texture
 */
void TextTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
/**
 * render a texture
 * @param gRenderer
 * @param x
 * @param y
 * @param clip
 * @param angle
 * @param center
 * @param flip
 */
void TextTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}
/** getters and setters**/
int TextTexture::getWidth()
{
    return mWidth;
}

int TextTexture::getHeight()
{
    return mHeight;
}
