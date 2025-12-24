#include "render.h"
#include "../entity.h"
#include "../player.h"

void app_render(void *appstate)
{
    AppState* state = (AppState*)appstate;

 
  SDL_RenderClear(state->renderer);
  SDL_SetRenderDrawColor(state->renderer, 0, 255, 0, 255);
  
  for (int i = 0; i < entities_count; i++) {
    if (!entities[i].render) continue;
        entities[i].render(state->renderer, state->delta_time, state->text_engine);
  }

  SDL_RenderPresent(state->renderer);

}

