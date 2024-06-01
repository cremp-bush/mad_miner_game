#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "header.h"

using namespace std;

GameObject imageGenerator(string name, string path, int x, int y, string allign, int size, bool isButton)
{
    GameObject object;
    object.name = name;
    object.rect = {x, y, 32*size, 32*size};
    object.isButton = isButton;
    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());
    SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
    object.texture = texture;
    
    if(allign == "left") object.rect.x = x;
    else if(allign == "center") object.rect.x = x-object.rect.w/2;
    else if(allign == "right") object.rect.x = x-object.rect.w;
    return object;
}