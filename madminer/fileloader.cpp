#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "header.h"

using namespace std;

SDL_Texture* imageGenerator(string image_name)
{
    SDL_Texture *image_texture = IMG_LoadTexture(renderer, ("data/Textures/" + image_name).c_str());
    SDL_SetTextureScaleMode(image_texture, SDL_ScaleModeNearest);
    
    return image_texture;
}