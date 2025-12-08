#include "render.h"
#include "../entity.h"
#include "../player.h"
void app_render(void *appstate)
{
    AppState* state= (AppState*)appstate;

        SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);

    for(int i=0;i<entities_count;i++){
        entities[i].render(state->renderer,state->delta_time,state->text_engine);
    }
    SDL_RenderClear(state->renderer);


    SDL_RenderPresent(state->renderer);
}