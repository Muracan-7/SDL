#include "player.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <ostream>
#define TEXT_SIZE 80
#define TEXT_COLOR (SDL_Color){255,255,255,255}

static SDL_Texture* player_tex;
TTF_Font* font;
SDL_Texture* font_tex;
SDL_Surface* surf;

typedef struct 
{
    float x,y;

}Position;
Position position = {0,0};


static void texter(SDL_Renderer* renderer,float posx,float posy)
{
       SDL_FRect font_rect{posx,posy,120,64};
       SDL_RenderTexture(renderer,font_tex,NULL,&font_rect);
}

static void quit()
{
    TTF_CloseFont(font);
}
static void handle_events(SDL_Event* e)
{

}
static void update(float delta_time)
{   
    const bool *keyboard_state = SDL_GetKeyboardState(NULL);
   if(keyboard_state[SDL_SCANCODE_W])
   {
    position.y-=120*delta_time;
   }
   if(keyboard_state[SDL_SCANCODE_S])
   {
    position.y+=120*delta_time;
   }
     if(keyboard_state[SDL_SCANCODE_A])
   {
    position.x-=120*delta_time;
   }
     if(keyboard_state[SDL_SCANCODE_D])
   {
    position.x+=120*delta_time;
   }

}
static void render(SDL_Renderer* renderer,float delta_time)
{
    SDL_FRect player_pos{position.x,position.y,64,64};
     std::string delta_text = std::to_string(position.x);
     surf= TTF_RenderText_Blended(font,delta_text.c_str(),0,TEXT_COLOR);
    font_tex= SDL_CreateTextureFromSurface(renderer,surf);
    texter(renderer,position.x,position.y+40);
     SDL_DestroySurface(surf);
     SDL_DestroyTexture(font_tex);
    surf=NULL;

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
    TTF_Init();
    font=TTF_OpenFont("./font.ttf",TEXT_SIZE);
   
    player_tex=IMG_LoadTexture(renderer,"./dude.bmp");
    Entity player={.quit=quit,.handle_events=handle_events,.update=update,.render=render};
    return player;
}
