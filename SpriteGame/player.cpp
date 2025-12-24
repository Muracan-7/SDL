#include <ostream>
#include <math.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "sdl/common.h"
#include "entity.h"
#include <vector>
#define FONT_SIZE 24
#define TEXT_COLOR (SDL_Color){255,255,255,255}
#define BACKGROUND_TEXT_COLOR (SDL_Color){140,140,255,55}
#define ANIMATION_FPS 12.0f
#define ANIMATION_FRAME_DURATION (1.0f / ANIMATION_FPS)
#define PLAYER_SPEED 140


static SDL_Texture* player_tex;

TTF_Font* font_large;
TTF_Font* font_medium;
TTF_Font* font_small;

SDL_FRect player_Src;
SDL_FRect player_pos;

int frames{0};
int fps{0};
std::string fps_string;

Uint64 last_input_time = 0;
static int last_fps_time = 0;
static float time_accumulator = 0.0f;


SDL_Scancode last_key_pressed{SDL_SCANCODE_UNKNOWN};
SDL_Scancode current_key_pressed{SDL_SCANCODE_UNKNOWN};

typedef struct 
{
    float x,y;

}Position;
Position position = {0,0};

struct Frame
{
SDL_FRect player_src;
    Frame(float x,float y,float w,float h)
    {
        player_src.x=x;
        player_src.y=y;
        player_src.h=h;
        player_src.w=w;
    }
};

struct Animation 
{
    std::vector<Frame> mFrames;
    std::size_t srcCurrentFrame{0};
    std::size_t srcMaxFrames{0};

    Animation(){
    }
    void LoadFrames(float startingX,float startingY,float w,float h,int numberOfFrames)
    {
        srcMaxFrames= numberOfFrames;
        for(std::size_t i=0;i<numberOfFrames;i++)
        {
            mFrames.push_back(Frame(startingX+(w*i),startingY,w,h));
        }
    }
    SDL_FRect GetFrameAsSDL_FRect(int index)
    {
        return mFrames.at(index).player_src;
    }
    SDL_FRect GetFrameAsSDL_FRect()
    {
        return mFrames.at(srcCurrentFrame).player_src;
    }

    void playAnimation()
    {
        srcCurrentFrame++;
        if(srcCurrentFrame>=srcMaxFrames)
        {
            srcCurrentFrame=0;
        }
    }
};

Animation mAnimation;
Animation walkDown;
Animation walkUp;
Animation walkLeft;
Animation walkRight;
Animation attackRight;
Animation idleDown;

static void quit()
{
    TTF_CloseFont(font_large);
    TTF_CloseFont(font_medium);
    TTF_CloseFont(font_small);
    SDL_DestroyTexture(player_tex);


    TTF_Quit();
}

static void handle_events(SDL_Event* e)
{
    if(SDL_PollEvent(e))
    {
        switch (e->type)
        {
        case SDL_EVENT_KEY_DOWN:
            last_key_pressed == current_key_pressed;
            current_key_pressed = e->key.scancode;
            break;
        
        default:
            break;
        }
        

    }
}

void animate(Animation anim,float time_accumulator)
{
    while (time_accumulator >= ANIMATION_FRAME_DURATION)
    {
        anim.playAnimation();
        time_accumulator -= ANIMATION_FRAME_DURATION;
    }
       player_Src= anim.GetFrameAsSDL_FRect();
    
}



static void update(float delta_time)
{   
    const bool* keyboard_state = SDL_GetKeyboardState(NULL);
    bool idle=false;
    time_accumulator += delta_time;
  
    
    if(keyboard_state[SDL_SCANCODE_W])
    { 
    position.y-=PLAYER_SPEED*delta_time;
    animate(walkUp,time_accumulator);
    }
   
   if(keyboard_state[SDL_SCANCODE_S])
   {
    position.y+=PLAYER_SPEED*delta_time;
    animate(walkDown,time_accumulator);
   }

     if(keyboard_state[SDL_SCANCODE_A])
   {
    position.x-=PLAYER_SPEED*delta_time;
    animate(walkLeft,time_accumulator);
   }
     if(keyboard_state[SDL_SCANCODE_D])
   {
    position.x+=PLAYER_SPEED*delta_time;
    animate(walkRight,time_accumulator);
   }

    }
  




static void render(SDL_Renderer* renderer,float delta_time,TTF_TextEngine* text_engine)
{
     int current_time = SDL_GetTicks();
    if (current_time - last_fps_time >= 1000)
    {
        fps = frames; 
        frames = 0;
        last_fps_time = current_time; 
    }
   fps_string =std::to_string(fps);
   fps_string.append(" :FPS");

    TTF_Text* dude_text=TTF_CreateText(text_engine,font_medium,"Lil Nga",0);
    TTF_DrawRendererText(dude_text,position.x,position.y-20);
    
    TTF_Text* fps_text = TTF_CreateText(text_engine,font_large,fps_string.c_str(),0);
    TTF_DrawRendererText(fps_text,0,0);


    TTF_DestroyText(dude_text);
    TTF_DestroyText(fps_text);

     player_pos.x=position.x;
     player_pos.y=position.y;
     player_pos.h=128;
     player_pos.w=64;
     

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
    SDL_RenderTexture(renderer,player_tex,&player_Src,&player_pos);
    frames++;
}

Entity init_player(SDL_Renderer* renderer)
{
    
    font_large=TTF_OpenFont("assets/fonts/font.ttf",FONT_SIZE);
    font_medium=TTF_OpenFont("assets/fonts/font.ttf",FONT_SIZE-6);
    font_small=TTF_OpenFont("assets/fonts/font.ttf",FONT_SIZE-10);

    walkDown.LoadFrames(16,16,16,16,6);
    walkLeft.LoadFrames(16,32,16,16,6);
    walkRight.LoadFrames(16,48,16,16,6);
    walkUp.LoadFrames(16,64,16,16,6);
    attackRight.LoadFrames(18,329,22,20,6);
    idleDown.LoadFrames(130,16,16,16,6);

    player_tex=IMG_LoadTexture(renderer,"assets/Char_Sprites/char_spritesheet.png");
    SDL_SetTextureScaleMode(player_tex,SDL_SCALEMODE_NEAREST);
    Entity player={.quit=quit,.handle_events=handle_events,.update=update,.render=render};
    return player;

}