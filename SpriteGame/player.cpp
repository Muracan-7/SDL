#include <ostream>
#include "draw_text.h"
#include <math.h>


#define TEXT_SIZE 80
#define TEXT_COLOR (SDL_Color){255,255,255,255}

static SDL_Texture* player_tex;

SDL_Surface* pos_surf;
SDL_Texture* pos_tex;

SDL_Texture* fps_tex;
SDL_Surface* fps_surf;
TTF_Font* font;

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


static void quit()
{
    TTF_CloseFont(font);
    TTF_Quit();
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
     

     texter(renderer,0,0,120,40,fps_tex,fps_text,TEXT_COLOR,font);
    

     SDL_DestroySurface(fps_surf);
     SDL_DestroyTexture(fps_tex);
     fps_surf=NULL;



     pos_text = std::to_string((int)round(position.x));
     pos_text.append(":x ");
     pos_text_y = std::to_string((int)round(position.y));
     pos_text.append(pos_text_y);
     pos_text.append(":y ");
     pos_surf =TTF_RenderText_Blended(font,pos_text.c_str(),0,TEXT_COLOR);
     pos_tex = SDL_CreateTextureFromSurface(renderer,pos_surf);
     
     texter(renderer,position.x,position.y+40,140,40,pos_tex,pos_text,TEXT_COLOR,font);

     SDL_DestroySurface(pos_surf);
     SDL_DestroyTexture(pos_tex);
     pos_surf=NULL;




     SDL_FRect player_pos{position.x,position.y,64,64};

    if(position.x>WINDOW_WIDTH)
    {
        position.x=static_cast<int>(position.x)%WINDOW_WIDTH;
    }
      if(position.x<0)
    {
        position.x=WINDOW_WIDTH;
    }
     if(position.y>WINDOW_HEIGHT)
    {
        position.y=static_cast<int>(position.y)%WINDOW_HEIGHT;
    }
     if(position.y<0)
    {
        position.y=WINDOW_HEIGHT;
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
    SDL_SetTextureScaleMode(fps_tex,SDL_SCALEMODE_LINEAR);
    player_tex=IMG_LoadTexture(renderer,"./dude.bmp");
    Entity player={.quit=quit,.handle_events=handle_events,.update=update,.render=render};
    return player;

}
