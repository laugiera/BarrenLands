//
// Created by natshez on 28/02/2018.
//

#include "TextHandler.hpp"

enum {
    BACK, FORWARD
};

TextHandler::TextHandler(SDL_Window * gWindow) : gRenderer(NULL), gFont(NULL) {
    init(gWindow);
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return;
    }
}

TextHandler::~TextHandler() {
    //Free loaded images
    gPromptTextTexture.free();
    gInputTextTexture.free();
    gForwardTexture.free();
    gReturnTexture.free();
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
}

bool TextHandler::init(SDL_Window * gWindow)
{
    gInputTextTexture = TextTexture();
    gPromptTextTexture = TextTexture();
    gForwardTexture = TextTexture();
    gReturnTexture = TextTexture();
    //Create vsynced renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    return true;
}


bool TextHandler::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont( "font/Orator.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 222,95,50,255 };
        if( !gPromptTextTexture.loadFromRenderedText(gRenderer, gFont, "Enter your name to create your world :", textColor ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }

    return success;
}

int TextHandler::handle(std::string * inputText){
    //Main loop flag
    int quit = CREATE;

    //Event handler
    SDL_Event e;

    SDL_Color textColor = { 255,255,255,255 };

    //The current input text.
    *inputText = "...";
    gInputTextTexture.loadFromRenderedText(gRenderer, gFont, (*inputText).c_str(), textColor );

    //Go back
    std::string goBackText = "Press ECHAP to go back";
    gReturnTexture.loadFromRenderedText(gRenderer, gFont, goBackText.c_str(), textColor );

    //Go forward
    //The current input text.
    std::string goForwardText = "Press ENTER to play";
    gForwardTexture.loadFromRenderedText(gRenderer, gFont, goForwardText.c_str(), textColor );

    //Enable text input
    SDL_StartTextInput();

    //While application is running
    while( quit == CREATE )
    {
        //The rerender text flag
        bool renderText = false;

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0  && quit == CREATE)
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = QUIT;
            }
                //Special key input
            else if( e.type == SDL_KEYDOWN )
            {
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    quit = MAINMENU;
                }
                else if(e.key.keysym.sym == SDLK_RETURN){
                    quit = PLAY;
                }
                else if( e.key.keysym.sym == SDLK_BACKSPACE && (*inputText).length() > 0 )
                {
                    //lop off character
                    (*inputText).pop_back();
                    renderText = true;
                }
            }
                //Special text input event
            else if( e.type == SDL_TEXTINPUT && (*inputText).length() < Tools::maxCharName)
            {
                    //Append character
                    *inputText += e.text.text;
                    renderText = true;
            }
        }

        //Rerender text if needed
        if( renderText )
        {
            //Text is not empty
            if( *inputText != "" )
            {
                //Render new text
                gInputTextTexture.loadFromRenderedText(gRenderer, gFont, (*inputText).c_str(), textColor );
            }
                //Text is empty
            else
            {
                //Render space texture
                gInputTextTexture.loadFromRenderedText(gRenderer, gFont, " ", textColor );
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 18,16,11,0 );
        SDL_RenderClear( gRenderer );

        //Render text textures
        int borderSize = 15;
        int x = (Tools::windowWidth - gPromptTextTexture.getWidth() ) / 2;
        int y = (Tools::windowHeight - gPromptTextTexture.getHeight() ) / 2;
        gPromptTextTexture.render(gRenderer, x, y);

        x =  ( Tools::windowWidth - gInputTextTexture.getWidth() ) / 2;
        y = (Tools::windowHeight - gPromptTextTexture.getHeight() ) / 2 +  gPromptTextTexture.getHeight();
        gInputTextTexture.render(gRenderer,x, y );

        x =  50;
        y = Tools::windowHeight - 50 - gReturnTexture.getHeight();
        gReturnTexture.render(gRenderer,x,y);

        SDL_Rect renderQuad = { x, y,  gReturnTexture.getWidth(),  gReturnTexture.getHeight()  };
        renderQuad.x-=borderSize; //whatever size you want
        renderQuad.y-=borderSize;
        renderQuad.h+=(borderSize)*2;
        renderQuad.w+=(borderSize)*2;
        // Color from within the rectangle
        SDL_SetRenderDrawColor( gRenderer, 222,95,50,255  );
        // Fill in the rectangle
        SDL_RenderDrawRect (gRenderer, &renderQuad);

        x =  Tools::windowWidth - gForwardTexture.getWidth() - 50;
        gForwardTexture.render(gRenderer,x,y);

        renderQuad = { x, y,  gForwardTexture.getWidth(),  gForwardTexture.getHeight()  };
        renderQuad.x-=borderSize; //whatever size you want
        renderQuad.y-=borderSize;
        renderQuad.h+=(borderSize)*2;
        renderQuad.w+=(borderSize)*2;
        // Color from within the rectangle
        SDL_SetRenderDrawColor( gRenderer, 222,95,50,255  );
        // Fill in the rectangle
        SDL_RenderDrawRect (gRenderer, &renderQuad);

        //Update screen
        SDL_RenderPresent( gRenderer );
    }

    //Disable text input
    SDL_StopTextInput();
    return quit;

}
