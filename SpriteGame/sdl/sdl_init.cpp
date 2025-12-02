#include "init.h"
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
 {  
    AppState* state = static_cast<AppState*>(SDL_malloc(sizeof(AppState)));
     *appstate = state;
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("The init for Video failed. %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if(!TTF_Init())
    {
        SDL_Log("The init for TTF failed. %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }
    state->window=SDL_CreateWindow("Sprite Game",WINDOW_WIDTH,WINDOW_HEIGHT,0);
    if(!state->window)
    {
        SDL_Log("The window init failed. %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }
    state->renderer = SDL_CreateRenderer(state->window,NULL);
     if(!state->renderer)
    {
        SDL_Log("The renderer init failed. %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

     

    entities[entities_count++]=  init_player(state->renderer);
    return SDL_APP_CONTINUE;
 }
