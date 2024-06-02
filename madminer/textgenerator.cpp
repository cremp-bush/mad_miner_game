#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "header.h"
using namespace std;

SDL_Texture* textGenerator(TextInfo text_info)
{
    /* Создание шрифта с обводкой */
    TTF_Font *text = TTF_OpenFont(("data/Fonts/" + text_info.font_name).c_str(), text_info.font_size);
    TTF_Font *outline = TTF_OpenFont(("data/Fonts/" + text_info.font_name).c_str(), text_info.font_size);
    TTF_SetFontOutline(outline, 2);
    /* Рендер текста */
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(text, text_info.text.c_str(), text_info.color);
    SDL_Surface *textOutline = TTF_RenderUTF8_Blended(outline, text_info.text.c_str(), {225, 225, 225});
    /* Нанесение обводки на текст */
    SDL_Rect rect = {2, 2, textSurface->w, textSurface->h};
    SDL_SetSurfaceBlendMode(textSurface, SDL_BLENDMODE_BLEND);
    SDL_BlitSurface(textSurface, NULL, textOutline, &rect);
    /* Уничтожение шрифтов */
    TTF_CloseFont(text);
    TTF_CloseFont(outline);
    
    /* Конвертация SDL_Surface в SDL_Texture */
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textOutline);
    /* Уничтожение SDL_Surface */
    SDL_FreeSurface(textOutline);
    SDL_FreeSurface(textSurface);
    
    return textTexture;
}