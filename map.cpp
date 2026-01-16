#include "map.h"
#define TILE_WIDTH (WINDOW_WIDTH/16)
#define TILE_HEIGHT (WINDOW_HEIGHT/16)



SDL_Texture* map_texture;
int tilemap[TILE_WIDTH*2][TILE_HEIGHT*2];
int max_tile_count=(TILE_WIDTH*2)*TILE_HEIGHT*2;
float scale_cof = 3.0f;
int tile_count{1};
std::string tile_count_str;
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
            if(y<100&&x>=10&&x<=20)
            {
             tilemap[10][y] = 2;
            // tilemap[20][y] = 3;
            tilemap[x][y]=1;
            }
            else{
                tilemap[x][y]=0;
            }
        }
    }
    SDL_FRect tile[TILE_WIDTH][TILE_HEIGHT];
     for (int x=0;x<TILE_WIDTH;x++)
    {
        for(int y=0;y<TILE_HEIGHT;y++)
        {
            tile[x][y].y=y*16*scale_cof;
            tile[x][y].x=x*16*scale_cof;
            tile[x][y].h=16*scale_cof;
            tile[x][y].w=16*scale_cof;
            tile_count_str=x;

        }
    }
    //floor
    SDL_FRect tile_empty={108,145,16,16};

    SDL_FRect tile_floor_topL={64,176,16,16};
    SDL_FRect tile_floor_bottomL={64,192,16,16};

    SDL_FRect tile_floor_topR={80,176,16,16};
    SDL_FRect tile_floor_bottomR={96,192,16,16};

    SDL_FRect tile_floor_basic={112,176,16,16};

    //walls
    SDL_FRect tile_wall_L = {0,134,16,16};




    for (int x=0;x<TILE_WIDTH;x++)
    {
        for(int y=0;y<TILE_HEIGHT;y++)
        {   

            switch (tilemap[x][y])
            {
            case 0:
                SDL_RenderTexture(renderer,map_texture,&tile_empty,&tile[x][y]);
                break;  
            case 1:
                SDL_RenderTexture(renderer,map_texture,&tile_floor_basic,&tile[x][y]);
                break;
            case 2:
                SDL_RenderTexture(renderer,map_texture,&tile_wall_L,&tile[x][y]);
                break;
           // case 3:
              //  SDL_RenderTexture(renderer,map_texture,&tile_wall_R,&tile[x][y]);
                    //break;
            
            }
        }
    }
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