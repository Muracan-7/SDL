#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>
#include "entity.h"
#include "player.h"




#define RENDER_ENTITIES(entities,entities_count,ren,delta_time)\
for(int i=0;i<entities_count;i++){\
        entities[i].render(ren,delta_time);\
    }
#define UPDATE_ENTITIES(entities,entities_count,delta_time)\
for(int i=0;i<entities_count;i++){\
        entities[i].update(delta_time);\
    }
#define QUIT_ENTITIES(entities,entities_count)\
for(int i=0;i<entities_count;i++){\
        entities[i].quit();\
    }
#define HANDLE_ENTITIE_EVENTS(entities,entities_count,event)\
for(int i=0;i<entities_count;i++){\
        entities[i].handle_events(event);\
    }



Entity entities[MAX_ENTITIES];
int entities_count=0;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* player_tex;
Uint64 last_tick=0;
Uint64 current_tick=0;
float delta_time;




SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
 {  
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
    window=SDL_CreateWindow("Sprite Game",840,320,0);
    if(!window)
    {
        SDL_Log("The window init failed. %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }
    renderer = SDL_CreateRenderer(window,NULL);
     if(!renderer)
    {
        SDL_Log("The renderer init failed. %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

     

    entities[entities_count++]=  init_player(renderer);
    return SDL_APP_CONTINUE;
 }



void render()
{
    SDL_RenderClear(renderer);
 
    RENDER_ENTITIES(entities, entities_count, renderer,delta_time);
    SDL_RenderPresent(renderer);
}
void update()
{
    last_tick = current_tick;
    current_tick=SDL_GetTicks();
    delta_time = (current_tick-last_tick)/1000.0f;

    UPDATE_ENTITIES(entities,entities_count,delta_time);
}



void SDL_AppQuit(void *appstate, SDL_AppResult result)
    {
        QUIT_ENTITIES(entities,entities_count);
        SDL_DestroyRenderer(renderer);
        renderer=NULL;
        SDL_DestroyWindow(window);
        window = NULL;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);        
        TTF_Quit();
        
    }
    SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
 {
    if(event->type==SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
 }
SDL_AppResult SDL_AppIterate(void *appstate)
{
    update();
    render();

    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}


 
