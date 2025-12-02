#include "sdl/common.h"
#include "draw_text.h"

SDL_Texture* font_tex;
SDL_Surface* font_surf;



void texter(SDL_Renderer* renderer,float posx,float posy,float scalex,float scaley,SDL_Texture* font_tex,std::string text,SDL_Color color,TTF_Font* font
)
{
       font_surf = TTF_RenderText_Blended(font,text.c_str(),0,color);
       SDL_FRect font_rect{posx,posy,scalex,scaley};
       font_tex= SDL_CreateTextureFromSurface(renderer,font_surf);
       SDL_RenderTexture(renderer,font_tex,NULL,&font_rect);
}