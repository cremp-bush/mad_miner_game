#include <SDL.h>
#include <SDL_mixer.h>
#include "header.h"

/* Инциализация глобальных переменных */
GUIObjectList guiObjectList;
ButtonList buttonList;
GameObjectList gameObjectList;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event event = {0};
string scene = "Main Menu";
Button *select = NULL;
bool quit = false;
Mix_Music *background_music = NULL;

short SCREEN_WIDTH = 1280;
short SCREEN_HEIGHT = 720;
bool VSYNC = false;
short MASTER_VOLUME = 100;
short MUSIC_VOLUME = 100;
bool FULLSCREEN_MODE = false;