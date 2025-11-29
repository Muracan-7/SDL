#pragma once
#include <SDL3/SDL.h>
#define MAX_ENTITIES 100

typedef struct{
    void (*texter)(SDL_Renderer*);
    void (*quit)(void);
    void (*handle_events)(SDL_Event*);
    void (*update)(float);
    void (*render)(SDL_Renderer*,float);

}Entity;