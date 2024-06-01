#pragma once
#include <iostream>
#include <SDL.h>
#include "structs.h"

using namespace std;

extern GameObjectList gameObjectList;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern string scene;
extern GameObject *select;
extern bool quit;
const SDL_Color black = {0,0,0};

/* setting s*/
extern short SCREEN_WIDTH;
extern short SCREEN_HEIGHT;
extern bool VSYNC;
extern short MASTER_VOLUME;
extern short MUSIC_VOLUME;
extern bool FULLSCREEN_MODE;

/* gameobjectmanager.cpp */
void createGameObjectStart(GameObject object);

void createGameObjectEnd(GameObject object);

void deleteGameObject(string name);

void clearGameObjects();

GameObject getGameObject(string name);

void setGameObject(GameObject object, string name);

/* init.cpp */
bool initSdl();

void stopSdl();

/* textgenerator.cpp */
GameObject textGenerator(string name, string text, int x, int y, int size, string allign, bool isButton = false);

/* scenes.cpp */
void loadMainMenu();

void loadSettingsMenu();

void loadNewGameMenu();

/* SDL_render_h_.cpp */
void renderGameObjects();

/* userinteraction.cpp */
void userInteraction();

/* fileloader.cpp */
GameObject imageGenerator(string name, string path, int x, int y, string allign, int size = 1, bool isButton = false);