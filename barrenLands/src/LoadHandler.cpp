//
// Created by natshez on 28/02/2018.
//

#include "LoadHandler.hpp"

LoadHandler::LoadHandler(SDL_Window * gWindow) : gRenderer(NULL), gFont(NULL) {
    init(gWindow);
    //Load media
    if( !loadMedia() )
    {
        printf( "Failed to load media!\n" );
        return;
    }
}




LoadHandler::~LoadHandler() {
    //Free loaded images
    for (int i = 0; i < gPromptTextTextures.size(); ++i)
        gPromptTextTextures[i].free();
    gForwardTexture.free();
    gReturnTexture.free();
    gTitleTextTexture.free();
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;
}

bool LoadHandler::init(SDL_Window * gWindow)
{

    saveNames = FileHelper::getAllLineFirstWord(Tools::savePath);
    saveNumber = saveNames.size();
    for (int i = 0; i < saveNumber; ++i){
        gPromptTextTextures.push_back(TextTexture());
    }
    gTitleTextTexture = TextTexture();
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


bool LoadHandler::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont( "font/Orator.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load  font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 222,95,50,255 };

        //Title
        std::string text = "UP / DOWN arrows to choose a load :";
        if( !gTitleTextTexture.loadFromRenderedText(gRenderer, gFont, text.c_str(), textColor ))
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
        //Go back
        text = "Press ECHAP to go back";
        if( !gReturnTexture.loadFromRenderedText(gRenderer, gFont, text.c_str(), textColor ))
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }

        //Go forward
        text = "Press ENTER to play";
        if( !gForwardTexture.loadFromRenderedText(gRenderer, gFont,text.c_str(), textColor ))
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }

        //loads
        textColor = { 255,255,255,255 };
        for (int i = 0; i < gPromptTextTextures.size(); ++i){
            if( !gPromptTextTextures[i].loadFromRenderedText(gRenderer, gFont, saveNames[i].c_str(), textColor ) )
            {
                printf( "Failed to render prompt text!\n" );
                success = false;
            }
        }
    }

    return success;
}


int LoadHandler::handle(std::string * loadName){
    //Main loop flag
    int quit = CREATE;
    int borderSize = 15;
    int x =0,y =0;
    //Event handler
    SDL_Event e;

    SDL_Rect renderQuadLoad = {0,0,0,0};
    int choosenSave = 0;

    *loadName = "default";

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
                    *loadName = saveNames[choosenSave];
                    quit = LOAD;
                }
                else if(e.key.keysym.sym == SDLK_UP){
                    choosenSave = (saveNumber + choosenSave - 1) % saveNumber;
                }
                else if(e.key.keysym.sym == SDLK_DOWN){
                    choosenSave = (choosenSave + 1) % saveNumber;
                }
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 18,16,11,0 );
        SDL_RenderClear( gRenderer );

        /**TITLE TEX **/
        x = (Tools::windowWidth - gTitleTextTexture.getWidth() ) / 2;
        y = 50 + (gTitleTextTexture.getHeight()) / 2;
        gTitleTextTexture.render(gRenderer, x, y);

        /**LOAD BUTTONS**/
        renderQuadLoad = { (Tools::windowWidth - gPromptTextTextures[0].getWidth() ) / 2,
                           y+(100 + (gPromptTextTextures[0].getHeight()/2))*(choosenSave+1),
                           gPromptTextTextures[0].getWidth(),
                           gPromptTextTextures[0].getHeight()  };
        renderQuadLoad.x-=borderSize; //whatever size you want
        renderQuadLoad.w+=(borderSize)*2;
        renderQuadLoad.y-=borderSize;
        renderQuadLoad.h+=(borderSize)*2;
        // Color from within the rectangle
        SDL_SetRenderDrawColor( gRenderer, 222,95,50,255  );
        // Fill in the rectangle
        SDL_RenderDrawRect (gRenderer, &renderQuadLoad);

        for (int i = 0; i < gPromptTextTextures.size(); ++i) {
            x = (Tools::windowWidth - gPromptTextTextures[i].getWidth() ) / 2;
            y += 100 + (gPromptTextTextures[i].getHeight()/2);
            gPromptTextTextures[i].render(gRenderer,x,y);
        }

        /**RETURN BUTTON**/
        x =  50;
        y = Tools::windowHeight - 50 - gReturnTexture.getHeight();
        gReturnTexture.render(gRenderer,x,y);

        SDL_Rect renderQuad = { x, y,  gReturnTexture.getWidth(),  gReturnTexture.getHeight()  };
        renderQuad.x-=borderSize;
        renderQuad.y-=borderSize;
        renderQuad.h+=(borderSize)*2;
        renderQuad.w+=(borderSize)*2;
        SDL_RenderDrawRect (gRenderer, &renderQuad);

        /**PLAY BUTTON**/
        x =  Tools::windowWidth - gForwardTexture.getWidth() - 50;
        gForwardTexture.render(gRenderer,x,y);

        renderQuad = { x, y,  gForwardTexture.getWidth(),  gForwardTexture.getHeight()  };
        renderQuad.x-=borderSize;
        renderQuad.y-=borderSize;
        renderQuad.h+=(borderSize)*2;
        renderQuad.w+=(borderSize)*2;
        SDL_RenderDrawRect (gRenderer, &renderQuad);

        //Update screen
        SDL_RenderPresent( gRenderer );
    }

    //Disable text input
    SDL_StopTextInput();
    return quit;

}
