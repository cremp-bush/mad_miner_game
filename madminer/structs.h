#pragma once
#include <iostream>
#include <SDL.h>;
#include <SDL_ttf.h>;
using namespace std;

//GUI structs
/* Информация о тексте */
struct TextInfo
{
    string text = "";
    string font_name = "";
    unsigned short font_size = 0;
    string allign = "";
    SDL_Color color = {0, 0, 0};
};

/* Элементы GUI */
struct GUIObject
{
    string name = "";
    SDL_Rect rect = {0,0,0,0};
    SDL_Texture *texture = NULL;
    TextInfo *text_info = NULL;
    GUIObject *next = NULL;
    float size = 1;
};

struct GUIObjectList
{
    GUIObject *head = NULL;
    unsigned short count = 0;
};

/* Элементы GUI - Кнопки */
struct Button
{
    GUIObject *object_info = NULL;
    Button *next = NULL;
};

struct ButtonList
{
    Button *head = NULL;
    unsigned short count = 0;
};

/* Игровые объекты/предметы */
struct GameObject
{
    string name = "";
    unsigned short type = 0;
};

struct GameObjectList
{
    GameObject *head = NULL;
    unsigned short count = 0;
};

/* Игровые стены */
struct Wall
{
    string name = "";
    unsigned short type = 0;
};

struct WallList
{
    GameObject *head = NULL;
    unsigned short count = 0;
};

/* Игровые газы */
struct Gas
{
    string name = "";
    unsigned short type = 0;
};

struct GasList
{
    GameObject *head = NULL;
    unsigned short count = 0;
};