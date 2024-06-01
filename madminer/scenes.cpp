#include <string>
#include <SDL.h>
#include "header.h"

using namespace std;

void loadMainMenu()
{
    select = NULL;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    
    clearGameObjects();
    createGameObjectEnd(textGenerator("GameLogo", "MINER GAME", 640, 50, 128, "center"));
    createGameObjectEnd(textGenerator("Records", "Рекорды", 1230, 360, 64, "right"));
    createGameObjectEnd(textGenerator("NewGameButton", "Новая игра", 50, 360, 64, "left", true));
    createGameObjectEnd(textGenerator("LoadGameButton", "Загрузить игру", 50, 360+66*1, 64, "left", true));
    createGameObjectEnd(textGenerator("MultiplayerButton", "Мультиплеер", 50, 360+66*2, 64, "left", true));
    createGameObjectEnd(textGenerator("SettingsButton", "Настройки", 50, 360+66*3, 64, "left", true));
    createGameObjectEnd(textGenerator("QuitButton", "Выйти из игры", 50, 360+66*4, 64, "left", true));
    
    renderGameObjects();
    SDL_RenderPresent(renderer);
}

void loadSettingsMenu()
{
    select = NULL;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);

    clearGameObjects();
    createGameObjectEnd(textGenerator("SettingsLogo", "Настройки", 160, 60, 64, "left"));
    createGameObjectEnd(textGenerator("ScreenResolution", "Разрешение экрана", 160, 60+34*2, 32, "left"));
    createGameObjectEnd(textGenerator("ScreenResolutionButton", to_string(SCREEN_WIDTH)+"x"+to_string(SCREEN_HEIGHT), 1120, 60+34*2, 32, "right", true));
    createGameObjectEnd(textGenerator("FullscreenMode", "Полноэкранный режим", 160, 60+34*3, 32, "left"));
    createGameObjectEnd(textGenerator("FullscreenModeButton", to_string(FULLSCREEN_MODE), 1120, 60+34*3, 32, "right", true));
    createGameObjectEnd(textGenerator("VSync", "VSync", 160, 60+34*4, 32, "left"));
    createGameObjectEnd(textGenerator("VSyncButton", to_string(VSYNC), 1120, 60+34*4, 32, "right", true));
    createGameObjectEnd(textGenerator("MasterSound", "Громкость игры", 160, 60+34*5, 32, "left"));
    createGameObjectEnd(textGenerator("MasterSoundButton", to_string(MASTER_VOLUME), 1120, 60+34*5, 32, "right", true));
    createGameObjectEnd(textGenerator("MusicSound", "Громкость музыки", 160, 60+34*6, 32, "left"));
    createGameObjectEnd(textGenerator("MusicSoundButton", to_string(MUSIC_VOLUME), 1120, 60+34*6, 32, "right", true));
    createGameObjectEnd(textGenerator("ApplyButton", "Применить", 1120, 60+34*8, 48, "right", true));
    createGameObjectEnd(textGenerator("ToMainMenuButton", "Вернуться", 160, 60+34*8, 48, "left", true));
    
    renderGameObjects();
    SDL_RenderPresent(renderer);
}

void loadNewGameMenu()
{
    select = NULL;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer);
    
    clearGameObjects();
    createGameObjectEnd(textGenerator("SelectDifficulty", "Выберите сложность", 640, 150, 64, "center"));
    createGameObjectEnd(textGenerator("Mode1", "Лёгкая", 160, 500, 64, "left", true));
    createGameObjectEnd(imageGenerator("Mode1Image", "data/Textures/diamond_rock.png", 160+96, 250, "center", 6));
    createGameObjectEnd(textGenerator("Mode2", "Средняя", 640, 500, 64, "center", true));
    createGameObjectEnd(imageGenerator("Mode2Image", "data/Textures/gold_rock.png", 640, 250, "center", 6));
    createGameObjectEnd(textGenerator("Mode3", "Хардкор", 1120, 500, 64, "right", true));
    createGameObjectEnd(imageGenerator("Mode3Image", "data/Textures/rock.png", 1120-96-24, 250, "center", 6));
    createGameObjectEnd(textGenerator("ToMainMenuButton", "Вернуться", 160, 600, 64, "left", true));
    
    renderGameObjects();
    SDL_RenderPresent(renderer);
}