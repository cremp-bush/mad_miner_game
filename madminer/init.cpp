#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

bool initSdl()
{
    bool success = false;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) std::cout << "Ошибка инициализации SDL!";
    else if(TTF_Init() != 0) std::cout << "Ошибка инициализации SDL_ttf!";
    else if(SDLNet_Init() != 0) std::cout << "Ошибка инициализации SDL_net!";
    else if(Mix_Init(MIX_INIT_OGG) == 0) std::cout << "Ошибка инициализации SDL_mixer!";
    else if(IMG_Init(IMG_INIT_PNG) == 0) std::cout << "Ошибка инициализации SDL_image!";
    else success = true;
    return success;
}

void stopSdl()
{
    IMG_Quit();
    Mix_Quit();
    SDLNet_Quit();
    TTF_Quit();
    SDL_Quit();
}