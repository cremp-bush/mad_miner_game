#include <iostream>
#include <SDL.h>
#include "header.h"

int main(int argc, char* argv[])
{
    if(initSdl())
    {
        window = SDL_CreateWindow(u8"Miner Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        loadMainMenu();
        while(!quit)
        {
            if(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT) quit = true;
                if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) quit = true;
                userInteraction();
            }
            
            SDL_Delay(1);
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
    stopSdl();
    return 0;
}
