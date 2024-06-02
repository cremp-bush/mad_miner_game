#include <iostream>
#include "fstream"
#include "string"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "header.h"

bool initSdl()
{
    bool success = false;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) std::cout << "Ошибка инициализации SDL!";
    else if(TTF_Init() != 0) std::cout << "Ошибка инициализации SDL_ttf!";
    else if(SDLNet_Init() != 0) std::cout << "Ошибка инициализации SDL_net!";
    else if(Mix_OpenAudio(22050, MIX_INIT_OGG, 2, 1024)) std::cout << "Ошибка инициализации SDL_mixer!";
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

void initSettings()
{
    ifstream settings("data/settings.txt", ios::in);
    string word;
    bool resolution, vsync, master_volume, music_volume, fullscreen;
    resolution = vsync =master_volume = music_volume = fullscreen = false;
    
    while(settings)
    {
        settings >> word;
        if(word == "SCREEN_WIDTH")
        {
            settings >> word;
            if(SCREEN_WIDTH != stoi(word))
            {
                resolution = true;
                SCREEN_WIDTH = stoi(word);
            }
        }
        else if(word == "SCREEN_HEIGHT")
        {
            settings >> word;
            if(SCREEN_HEIGHT != stoi(word))
            {
                resolution = true;
                SCREEN_HEIGHT = stoi(word);
            }
        }
        else if(word == "VSYNC")
        {
            settings >> word;
            if(VSYNC != stoi(word))
            {
                vsync = true;
                VSYNC = stoi(word);
            }
        }
        else if(word == "MASTER_VOLUME")
        {
            settings >> word;
            if(MASTER_VOLUME != stoi(word))
            {
                master_volume = true;
                MASTER_VOLUME = stoi(word);
            }
        }
        else if(word == "MUSIC_VOLUME")
        {
            settings >> word;
            if(MUSIC_VOLUME != stoi(word))
            {
                music_volume = true;
                MUSIC_VOLUME = stoi(word);
            }
        }
        else if(word == "FULLSCREEN_MODE")
        {
            settings >> word;
            if(FULLSCREEN_MODE != stoi(word))
            {
                fullscreen = true;
                FULLSCREEN_MODE = stoi(word);
            }
        }
    }
    settings.close();
    
    if(resolution) SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(vsync)
    {
        SDL_DestroyRenderer(renderer);
        if(VSYNC) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
        else renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        if(FULLSCREEN_MODE)
        {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
            SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN || SDL_WINDOW_BORDERLESS);
        }
    }
    Mix_MasterVolume(MIX_MAX_VOLUME/100.0 * MASTER_VOLUME);
    Mix_VolumeMusic(MIX_MAX_VOLUME/100.0 * MUSIC_VOLUME);
    if(fullscreen)
    {
        if(FULLSCREEN_MODE) SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN || SDL_WINDOW_FULLSCREEN_DESKTOP);
        else SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
    }
    if(resolution || vsync || master_volume || music_volume || fullscreen) updateFrame();
}