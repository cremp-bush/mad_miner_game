#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "header.h"

using namespace std;

GameObject textGenerator(string name, string text, int x, int y, int size, string allign, bool isButton)
{
    GameObject object;
    TTF_Font *font = TTF_OpenFont("data/font.ttf", size);
    SDL_Surface *textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), black);
    TTF_CloseFont(font);

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    SDL_QueryTexture(textTexture, nullptr, nullptr, &object.rect.w, &object.rect.h);

    if(allign == "left") object.rect.x = x;
    else if(allign == "center") object.rect.x = x-object.rect.w/2;
    else if(allign == "right") object.rect.x = x-object.rect.w;

    object.name = name;
    object.rect.y = y;
    object.isButton = isButton;
    object.textInfo.text = text;
    object.textInfo.size = size;
    object.textInfo.allign = allign;
    object.texture = textTexture;
    return object;
}