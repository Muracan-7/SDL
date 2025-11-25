#include <string.h>
#include <math.h>
#include <stdlib.h>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

int* gFrameBuffer;
SDL_Window* gSDLWindow;
SDL_Renderer* gSDLRenderer;
SDL_Texture* gSDLTexture;
static int gDone;
constexpr int WINDOW_WIDTH = 3840 / 2;
constexpr int WINDOW_HEIGHT = 2160 / 2;

bool update()
{
  SDL_Event e;
  if (SDL_PollEvent(&e))
  {
    if (e.type == SDL_EVENT_QUIT)
    {
      return false;
    }
    if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE)
    {
      return false;
    }
  }

  char* pix;
  int pitch;
  
  SDL_LockTexture(gSDLTexture, NULL, (void**)&pix, &pitch);
  for (int i = 0, sp = 0, dp = 0; i < WINDOW_HEIGHT; i++, dp += WINDOW_WIDTH, sp += pitch)
    memcpy(pix + sp, gFrameBuffer + dp, WINDOW_WIDTH*4);

  SDL_UnlockTexture(gSDLTexture);  
  SDL_RenderTexture(gSDLRenderer, gSDLTexture, NULL, NULL);
  SDL_RenderPresent(gSDLRenderer);
  SDL_Delay(1);
  return true;
}
void putpixel(int x, int y, int color)
{
  if (x < 0 ||
      y < 0 ||
      x >= WINDOW_WIDTH ||
      y >= WINDOW_HEIGHT)
  {
      return;
  }
  gFrameBuffer[y * WINDOW_WIDTH + x] = color;
}

void render(Uint64 aTicks)
{
    SDL_Event e;
     int dotX=(aTicks /5)%WINDOW_WIDTH;
     int dotY = (aTicks /5)%WINDOW_HEIGHT;
  for (int i = 0, c = 0; i < WINDOW_HEIGHT; i++)
  {
    for (int j = 0; j < WINDOW_WIDTH; j++, c++)
    {
      gFrameBuffer[c] = (int)(i * sin(i) - j * j + aTicks) | 0xff000000;
    }
  }
  for (int i = 0; i < 100; i++)
    for (int j = 0; j < 100; j++){
       putpixel(j+dotX, i+dotY, 0xFFAE3050);
          
    }
}

void loop()
{
  if (!update())
  {
    gDone = 1;
#ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
#endif
  }
  else
  {
    render(SDL_GetTicks());
  }
}

int main(int argc, char** argv)
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {
    return -1;
  }

  gFrameBuffer = new int[WINDOW_WIDTH * WINDOW_HEIGHT];
  gSDLWindow = SDL_CreateWindow("SDL3 window", WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  gSDLRenderer = SDL_CreateRenderer(gSDLWindow, NULL);
  gSDLTexture = SDL_CreateTexture(gSDLRenderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

  if (!gFrameBuffer || !gSDLWindow || !gSDLRenderer || !gSDLTexture)
    return -1;

  gDone = 0;
#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#else
  while (!gDone)
  {
    loop();
  }
#endif

  SDL_DestroyTexture(gSDLTexture);
  SDL_DestroyRenderer(gSDLRenderer);
  SDL_DestroyWindow(gSDLWindow);
  SDL_Quit();

  return 0;
}
