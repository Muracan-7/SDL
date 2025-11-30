#include "player.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <ostream>
#define TEXT_SIZE 80
#define TEXT_COLOR (SDL_Color){255,255,255,255}
#include <math.h>
static SDL_Texture* player_tex;
TTF_Font* font;
SDL_Texture* font_tex;
SDL_Surface* fps_surf;

SDL_Surface* pos_surf;
SDL_Texture* pos_tex;

int mseconds;
int seconds;
int frames{0};
int fps{0};
std::string fps_text;
static int last_fps_time = 0;
std::string pos_text;
std::string pos_text_y;
typedef struct 
{
    float x,y;

}Position;
Position position = {0,0};


static void texter(SDL_Renderer* renderer,float posx,float posy)
{
       SDL_FRect font_rect{posx,posy,140,32};
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
   int current_time = SDL_GetTicks();
    if (current_time - last_fps_time >= 1000)
    {
        fps = frames; 
        frames = 0;
        last_fps_time = current_time; 
    }

   
     fps_text = std::to_string(fps);
     fps_text.append(":FPS");
     fps_surf= TTF_RenderText_Blended(font,fps_text.c_str(),0,TEXT_COLOR);


    font_tex= SDL_CreateTextureFromSurface(renderer,fps_surf);
    SDL_SetTextureScaleMode(font_tex,SDL_SCALEMODE_LINEAR);
    texter(renderer,0,0);


     SDL_DestroySurface(fps_surf);
     SDL_DestroyTexture(font_tex);
     fps_surf=NULL;


     pos_text = std::to_string((int)round(position.x));
     pos_text.append(":x ");
     pos_text_y = std::to_string((int)round(position.y));
     pos_text.append(pos_text_y);
     pos_text.append(":y ");
     pos_surf =TTF_RenderText_Blended(font,pos_text.c_str(),0,TEXT_COLOR);
     pos_tex = SDL_CreateTextureFromSurface(renderer,pos_surf);
     texter(renderer,position.x,position.y-40);
     
     

     SDL_DestroySurface(pos_surf);
     SDL_DestroyTexture(pos_tex);
     pos_surf=NULL;




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
    frames++;
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
