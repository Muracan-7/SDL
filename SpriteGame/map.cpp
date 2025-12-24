#include "map.h"
#define TILE_WIDTH (WINDOW_WIDTH/16)
#define TILE_HEIGHT (WINDOW_HEIGHT/16)+1

SDL_Texture* map_texture;
int tilemap[TILE_WIDTH][TILE_HEIGHT];

static void quit()
{
    SDL_DestroyTexture(map_texture);
}
static void handle_events(SDL_Event* e)
{

}
static void update(float delta_time)
{

}
static void render(SDL_Renderer* renderer,float delta_time,TTF_TextEngine* text_engine)
{
    
    map_texture=IMG_LoadTexture(renderer,"assets/Dungeon_Tileset.png");
    if(!map_texture)
    {
        SDL_Log("Texture didn't load %s",SDL_GetError());
    }
   
    for (int x=0;x<TILE_WIDTH;x++)
    {
        for(int y=0;y<TILE_HEIGHT;y++)
        {
            tilemap[x][y] = 1;
            tilemap[x+1][y] = 2;
            tilemap[x+1][y+1] = 3;
            tilemap[x][y+1] = 4;
        }
    }
    SDL_FRect tile[TILE_WIDTH][TILE_HEIGHT];
     for (int x=0;x<TILE_WIDTH;x++)
    {
        for(int y=0;y<TILE_HEIGHT;y++)
        {
            tile[x][y].y=y*16;
            tile[x][y].x=x*16;
            tile[x][y].h=16;
            tile[x][y].w=16;

        }
    }

    SDL_FRect tile_1={64,176,16,16};
    SDL_FRect tile_2={64,192,16,16};

    SDL_FRect tile_3={80,176,16,16};
    SDL_FRect tile_4={96,192,16,16};


    for (int x=0;x<TILE_WIDTH;x++)
    {
        for(int y=0;y<TILE_HEIGHT;y++)
        {
            switch (tilemap[x][y])
            {
            case 1:
                SDL_RenderTexture(renderer,map_texture,&tile_1,&tile[x][y]); 
                break;
            case 2:
                SDL_RenderTexture(renderer,map_texture,&tile_2,&tile[x][y]);
                break;
            case 3:
                SDL_RenderTexture(renderer,map_texture,&tile_3,&tile[x][y]);
                break;
            case 4:
                SDL_RenderTexture(renderer,map_texture,&tile_4,&tile[x][y]);
                break;
            }
        }
    }
        SDL_SetTextureScaleMode(map_texture,SDL_SCALEMODE_NEAREST);

}

Entity init_map(SDL_Renderer* renderer)
{
 

    Entity map = {
        .quit=quit,
        .handle_events=handle_events,
        .update=update,
        .render=render
    };
    return map;
}