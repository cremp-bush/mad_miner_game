#pragma once
#include <iostream>
#include <SDL.h>;
#include <SDL_ttf.h>;
using namespace std;

//GUI structs
/* Информация о тексте */
struct Texture
{
    string name;
    SDL_Texture *texture;
    Texture *next = NULL;
};

struct TextureList
{
    Texture *head = NULL;
    unsigned short count = 0;
};

struct TextInfo
{
    string text;
    string font_name;
    unsigned short font_size;
    string allign;
    SDL_Color color;
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

/* Игровые жидкости */
struct Ground
{
    string name = "";
    SDL_Rect rect;
    SDL_Texture *texture = NULL;
    unsigned short id = 0;
    Ground *next = NULL;
};

struct GroundList
{
    Ground *head = NULL;
    unsigned short count = 0;
};

/* Игровые объекты/предметы */
struct GameObject
{
    int x;
    int y;
    unsigned short type = 0;
    unsigned long long id = 0;
    GameObject *next = NULL;
};

struct GameObjectList
{
    GameObject *head = NULL;
    unsigned long long count = 0;
};

/* Игровые стены */
struct Wall
{
    int x;
    int y;
    unsigned short type = 0;
    unsigned long long id = 0;
    Wall *next = NULL;
};

struct WallList
{
    Wall *head = NULL;
    unsigned long long count = 0;
};

/* Игровые газы */
struct Gas
{
    string name = "";
    SDL_Rect rect;
    SDL_Texture *texture = NULL;
    unsigned short id = 0;
    Gas *next = NULL;
};

struct GasList
{
    GameObject *head = NULL;
    unsigned short count = 0;
};

/* Игрок */
struct Player
{
    int x;
    int y;
    Texture *texture;
    int health = 5;
    int stamina = 55;
    bool gas_mask = false;
    int filter = 55;
    int gold = 0;
    int diamond = 0;
    int emerald = 0;
};