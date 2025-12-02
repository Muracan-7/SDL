#include "render.h"

void app_render(void *appstate)
{
    AppState* state= (AppState*)appstate;
    SDL_RenderClear(state->renderer);



for(int i=0;i<entities_count;i++){\
        entities[i].render(state->renderer,state->delta_time);\
    }


    SDL_RenderPresent(state->renderer);
}