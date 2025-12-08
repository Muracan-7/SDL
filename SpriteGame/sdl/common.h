#pragma once
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640



#ifdef __cplusplus
extern "C" {
#endif

// Ensure all four callback declarations are present and *exactly* match the SDL3 signature (non-const SDL_Event*)
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv);
void SDL_AppQuit(void *appstate, SDL_AppResult result);
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
SDL_AppResult SDL_AppIterate(void *appstate);

#ifdef __cplusplus
}
#endif


typedef struct AppState{
    SDL_Window* window;
    SDL_Renderer* renderer;
    float last_tick;
    float current_tick;
    float delta_time;
    TTF_TextEngine* text_engine;
    uint64_t last_counter;
    uint64_t frequency;

}AppState;

