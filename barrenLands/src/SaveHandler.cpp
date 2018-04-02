//
// Created by natshez on 28/02/2018.
//

#include "SaveHandler.hpp"
/**
 * Constructor
 * loads media
 * @param gWindow SDL_Window *
 */
SaveHandler::SaveHandler(SDL_Window * gWindow) : gRenderer(NULL), gFont(NULL) {
    init(gWindow);
    loadMedia();
}
/**
 * Destructor
 */
SaveHandler::~SaveHandler() {
    //Free Saveed images
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
/**
 * init()
 * @param gWindow
 * @return void
 * \exception <std::runtime_error> { cannot open the given file }
 */
void SaveHandler::init(SDL_Window * gWindow)
{
    saveNames = FileHelper::getAllLineFirstWord(Tools::savePath); //get saves names
    for (int i = 0; i < Tools::saveMaxnumber; ++i){
        gPromptTextTextures.push_back(TextTexture());
    }
    gTitleTextTexture = TextTexture();
    gForwardTexture = TextTexture();
    gReturnTexture = TextTexture();
    //Create vsynced renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( gRenderer == NULL )
        throw std::runtime_error("save rendered could not be open !");

}
/**
 * loadMedia()
 * lodas the font and the textures
 * @return void
 * \exception <std::runtime_error> { cannot load font or textures files }
 */
void SaveHandler::loadMedia()
{

    //Open the font
    gFont = TTF_OpenFont( "font/Orator.ttf", 28 );
    if( gFont == NULL )
        throw std::runtime_error("save font could not be open !");
    else
    {
        //Render the prompt
        SDL_Color textColor = { 222,95,50,255 };

        //Title
        std::string text = "UP / DOWN arrows to choose a save (that will rewrite on existing) :";
        if( !gTitleTextTexture.loadFromRenderedText(gRenderer, gFont, text.c_str(), textColor ))
            throw std::runtime_error("TitleTextTexture rendered could not be open !");
        //Go back
        text = "Press ECHAP to go back";
        if( !gReturnTexture.loadFromRenderedText(gRenderer, gFont, text.c_str(), textColor ))
            throw std::runtime_error("ReturnTexture rendered could not be open !");

        //Go forward
        text = "Press ENTER to save";
        if( !gForwardTexture.loadFromRenderedText(gRenderer, gFont,text.c_str(), textColor ))
            throw std::runtime_error("ForwardTexture rendered could not be open !");

        //Saves
        textColor = { 255,255,255,255 };
        for (int i = 0; i < gPromptTextTextures.size(); ++i){
            if(i<saveNames.size())
                text = saveNames[i];
            else
                text = "free spot";
            if( !gPromptTextTextures[i].loadFromRenderedText(gRenderer, gFont, text.c_str(), textColor ) )
                throw std::runtime_error("PromptTexture rendered could not be open !");
        }
    }
}
/**
 * handle()
 * render the menu
 * @param the number of the choosenSave
 * @return int among the enum defined in Tool class, represents the button clicked in the menu (pause, save, quit)
 */
int SaveHandler::handle(int * choosenSave){
    //Main loop flag
    int quit = CREATE;
    int borderSize = 15;
    int x =0,y =0;
    //Event handler
    SDL_Event e;

    SDL_Rect renderQuadSave;
    *choosenSave = 0;

    //While application is running
    while( quit == CREATE )
    {
              //Handle events on queue
        while( SDL_PollEvent( &e ) != 0  && quit == CREATE)
        {
            //User requests quit
            if( e.type == SDL_QUIT )
                quit = QUIT;

            else if( e.type == SDL_KEYDOWN )
            {
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    quit = PAUSE;
                }
                else if(e.key.keysym.sym == SDLK_RETURN){
                    quit = SAVE;
                }
                else if(e.key.keysym.sym == SDLK_UP){
                    *choosenSave = (Tools::saveMaxnumber + *choosenSave - 1) % Tools::saveMaxnumber ;
                }
                else if(e.key.keysym.sym == SDLK_DOWN){
                    *choosenSave = (*choosenSave + 1) % Tools::saveMaxnumber ;
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

        /**Save BUTTONS**/
        renderQuadSave = { (Tools::windowWidth - gPromptTextTextures[0].getWidth() ) / 2,
                           y+(100 + (gPromptTextTextures[0].getHeight()/2))*((*choosenSave)+1),
                           gPromptTextTextures[0].getWidth(),
                           gPromptTextTextures[0].getHeight()  };
        renderQuadSave.x-=borderSize; //whatever size you want
        renderQuadSave.w+=(borderSize)*2;
        renderQuadSave.y-=borderSize;
        renderQuadSave.h+=(borderSize)*2;
        // Color from within the rectangle
        SDL_SetRenderDrawColor( gRenderer, 222,95,50,255  );
        // Fill in the rectangle
        SDL_RenderDrawRect (gRenderer, &renderQuadSave);

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
