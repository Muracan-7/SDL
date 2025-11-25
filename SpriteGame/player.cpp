#include "player.h"

static SDL_Texture* player_tex;

typedef struct 
{
    float x,y;

}Position;
Position position = {0,0};

static void quit()
{

}
static void handle_events(SDL_Event* e)
{

}
static void update()
{   
    const bool *keyboard_state = SDL_GetKeyboardState(NULL);
   if(keyboard_state[SDL_SCANCODE_W])
   {
    position.y-=0.01;
   }
   if(keyboard_state[SDL_SCANCODE_S])
   {
    position.y+=0.01;
   }
     if(keyboard_state[SDL_SCANCODE_A])
   {
    position.x-=0.01;
   }
     if(keyboard_state[SDL_SCANCODE_D])
   {
    position.x+=0.01;
   }

}
static void render(SDL_Renderer* renderer)
{   
    SDL_FRect player_pos{position.x,position.y,64,64};
    if(position.x>840)
    {
        position.x=static_cast<int>(position.x)%840;
    }
      if(position.x<0)
    {
        position.x=840;
    }
     if(position.y>320)
    {
        position.y=static_cast<int>(position.y)%320;
    }
     if(position.y<0)
    {
        position.y=320;
    }
    SDL_SetTextureScaleMode(player_tex,SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(renderer,player_tex,NULL,&player_pos);
    
    SDL_RenderPresent(renderer); 
}

Entity init_player(SDL_Renderer* renderer)
{
   
    player_tex=IMG_LoadTexture(renderer,"./dude.bmp");
    Entity player={.quit=quit,.handle_events=handle_events,.update=update,.render=render};
    return player;
}
