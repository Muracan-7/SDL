#pragma once
#include "sdl/common.h"
#define MAX_ENTITIES 100

typedef struct{
    void (*quit)(void);
    void (*handle_events)(SDL_Event*);
    void (*update)(float);
    void (*render)(SDL_Renderer*,float,TTF_TextEngine*);
}Entity;

extern Entity entities[MAX_ENTITIES];
extern int entities_count;
