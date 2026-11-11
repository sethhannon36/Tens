#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "Tens.h"

/* Game Pieces */
SDL_Texture* cardsheet;
int cardsheet_rows = 4;
int cardsheet_cols = 15;
float cardsheet_w = 0.0f;
float cardsheet_h = 0.0f;

/* SDL */
SDL_Window* window;
SDL_Renderer* renderer;
bool waiting_for_input = true;

// TODO finish rendering process, add clicking support

/* Game Loop */
// Initialize Application
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {

    /* Init SDL */
    SDL_SetAppMetadata("Chiken Quest", "0.1", "NULL");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Chiken Quest", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Set Vertical Sync (CURRENTLY DISABLED FOR TESTING)
    if (!SDL_SetRenderVSync(renderer, SDL_RENDERER_VSYNC_DISABLED)) {
        SDL_Log("VSync not supported: %s", SDL_GetError());
    }

    // Enforce Strict Aspect Ratio
    SDL_SetWindowAspectRatio(window, 16.0f / 9.0f, 16.0f / 9.0f);

    TensInit(2);

    // load card images
    SDL_Surface* s = SDL_LoadPNG("../resource/cards.png");
    if ( !s ) 
    {
    printf(" Image not found!\n ");
    return SDL_APP_FAILURE;
    }

    cardsheet = SDL_CreateTextureFromSurface( renderer, s );
    if ( !cardsheet ) 
    {
    printf(" Texture failed to create!\n ");
    return SDL_APP_FAILURE;
    }

    SDL_GetTextureSize( cardsheet, &cardsheet_w, &cardsheet_h);
    cardsheet_h /= cardsheet_rows;
    cardsheet_w /= cardsheet_cols;

    SDL_DestroySurface( s );

    return SDL_APP_CONTINUE;

}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    /* render game */
    // get cards
    int player = 0;
    int hand_size = Tens_CountCardsInSet( Tens_GetPlayerSetId(player) );
    int cards[hand_size];
    Tens_GetCardsFromSet( Tens_GetPlayerSetId(player), cards);

    // render SDL
    SDL_SetRenderDrawColor( renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
    SDL_RenderClear( renderer );
    SDL_FRect source;
    source.w = cardsheet_w;
    source.h = cardsheet_h;
    source.x = 0;
    source.y = 0;

    SDL_FRect target;
    target.w = 100;
    target.h = 200;
    target.x = 0;
    target.y = 0;

    SDL_RenderTexture( renderer, cardsheet, &source, &target );
    SDL_RenderPresent( renderer );
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_DestroyTexture(cardsheet);
    TensDestroy();
}
