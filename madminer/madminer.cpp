#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "header.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");
    /* Инциализация SDL и его библиотек */
    if(initSdl())
    {
        /* Создание окна игры и рендера */
        window = SDL_CreateWindow(u8"Miner Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        initSettings();
        background_music = Mix_LoadMUS("data/Music/main_title.ogg");
        Mix_PlayMusic(background_music, -1);

        /* Основной цикл перемещения между сценами игры */
        while(!quit)
        {
            if(scene == "Main Menu") loadMainMenu();
            else if(scene == "New Game Menu") loadNewGameMenu();
            else if(scene == "Settings Menu") loadSettingsMenu();
            else if(scene == "Game") loadGame();
            else if(scene == "Pause") loadPause();
            if(scene != "Escape")
            {
                clearGUIObjects();
                select = NULL;
                quit = false;
            }
        }
        /* Уничтожение окна и рендера */
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
    /* Отключение SDL и его библиотек */
    stopSdl();
    return 0;
}
