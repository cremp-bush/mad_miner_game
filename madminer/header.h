#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "structs.h"
using namespace std;

extern GUIObjectList guiObjectList;
extern ButtonList buttonList;
extern GameObjectList gameObjectList;
extern TextureList textureList;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event event;
extern string scene;
extern Button *select;
extern bool quit;
extern Mix_Music *background_music;
const SDL_Color black = {0,0,0};

extern int map_width;
extern int map_height;
extern int difficulty;
extern int score;

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

GUIObject* getGUIObject(string name);

// void setGUIObject(GUIObject object, string name);

void updateGUIObject(GUIObject *guiObject);
void updateGUIObject(string name, SDL_Texture *texture);

void createWall(WallList *wList, int x, int y, int type);
void deleteWall(WallList *wList, unsigned short id);
void clearWalls(WallList *wList);
void updateWall(WallList *wList, unsigned short id);
Wall* getWall(WallList *wList, int x, int y);

void createGameObject(GameObjectList *gameObjectList, int x, int y, int type);
void deleteGameObject(GameObjectList *gameObjectList, unsigned short id);
void clearGameObjects(GameObjectList *gameObjectList);
void updateGameObject(GameObjectList *gameObjectList, unsigned short id);
GameObject* getGameObject(GameObjectList *gameObjectList, int x, int y);

void addInventory(Player *player, int type);
bool checkInventory(Player *player);
void deleteInventory(Player *player, int slot);

/* init.cpp */
bool initSdl();

void stopSdl();

void initSettings();

void initMap(Player *player, int ***map);

/* textgenerator.cpp */
SDL_Texture* textGenerator(TextInfo text_info);

void loadTexture(string texture_name);
void loadTexture(string texture_name, SDL_Texture *insert_texture);
void destroyTexture(string texture_name);
void clearTextures();
Texture* getTexture(string texture_name);

/* scenes.cpp */
void checkMainMenu();
void loadMainMenu();

void checkSettingsenu();
void loadSettingsMenu();

void checkNewGameMenu();
void loadNewGameMenu();

void checkGame(Player *player, int ***map);
void loadGame();

void checkPause();
void loadPause();

/* SDL_render_h_.cpp */
void renderWalls(Player *player, int ***map);
void renderGameObjects(Player *player, int ***map);
void renderGUIObjects();
void renderInterface(Player *player, int ***map);

void updateFrame(Player *player, int ***map);
void updateFrame();

/* userinput.cpp */
Button* userInput();

/* fileloader.cpp */
SDL_Texture* imageGenerator(string image_name);