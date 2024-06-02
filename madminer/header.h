#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "structs.h"
using namespace std;

extern GUIObjectList guiObjectList;
extern ButtonList buttonList;
extern GameObjectList gameObjectList;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern string scene;
extern Button *select;
extern bool quit;
extern Mix_Music *background_music;
const SDL_Color black = {0,0,0};

extern short SCREEN_WIDTH;
extern short SCREEN_HEIGHT;
extern bool VSYNC;
extern short MASTER_VOLUME;
extern short MUSIC_VOLUME;
extern bool FULLSCREEN_MODE;

/* objectmanager.cpp */
void createButton(GUIObject object);
void createButton(string name, SDL_Rect rect, SDL_Texture *texture, string allign = "left", float size = 1);
void createButton(string name, SDL_Rect rect, TextInfo text_info);

void createGUIObject(GUIObject object);
void createGUIObject(string name, SDL_Rect rect, SDL_Texture *texture, string allign = "left", float size = 1);
void createGUIObject(string name, SDL_Rect rect, TextInfo text_info);

void createGUIObjectEnd(GUIObject object);

void deleteGUIObject(string name);

void clearGUIObjects();

GUIObject getGUIObject(string name);

// void setGUIObject(GUIObject object, string name);

void updateGUIObject(GUIObject *guiObject);

/* init.cpp */
bool initSdl();

void stopSdl();

void initSettings();

/* textgenerator.cpp */
SDL_Texture* textGenerator(TextInfo text_info);

/* scenes.cpp */
void checkMainMenu();
void loadMainMenu();

void checkSettingsenu();
void loadSettingsMenu();

void checkNewGameMenu();
void loadNewGameMenu();

/* SDL_render_h_.cpp */
void renderGUIObjects();

void updateFrame();

/* userinput.cpp */
Button* userInput();

/* fileloader.cpp */
SDL_Texture* imageGenerator(string image_name);