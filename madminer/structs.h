#pragma once
#include <iostream>
using namespace std;

//GUI structs
struct TextInfo
{
    string text = "";
    int size;
    string allign = "";
};

struct GameObject
{
    string name = "";
    SDL_Rect rect = {0};
    SDL_Texture *texture = NULL;
    bool isButton = false;
    TextInfo textInfo;
    GameObject *next = NULL;
};

struct GameObjectList
{
    int count = 0;
    GameObject *head = NULL;
};

struct Button
{
    string name = NULL;
    SDL_Rect rect = {0};
    SDL_Texture *texture = NULL;
    Button *next = NULL;
};

struct ButtonList
{
    int count = 0;
    Button *head = NULL;
};

struct Effect
{
    string name = NULL;
    short frames = 1;
    short current_frame = 1;
    SDL_Texture *texture;
    SDL_Rect rect;
    Effect *next = NULL;
};

struct EffectList
{
    int count = 0;
    Effect *head = NULL;
};