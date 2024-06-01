#include <SDL.h>
#include "header.h"

GameObjectList gameObjectList;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event event = {0};
string scene = "Main Menu";
GameObject *select = NULL;
bool quit = false;

short SCREEN_WIDTH = 1280;
short SCREEN_HEIGHT = 720;
bool VSYNC = false;
short MASTER_VOLUME = 100;
short MUSIC_VOLUME = 100;
bool FULLSCREEN_MODE = false;