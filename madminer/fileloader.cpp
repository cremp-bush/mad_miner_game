#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "header.h"

using namespace std;

/* Генератор изображений */
SDL_Texture* imageGenerator(string image_name)
{
    SDL_Texture *image_texture = IMG_LoadTexture(renderer, ("data/Textures/" + image_name).c_str());
    SDL_SetTextureScaleMode(image_texture, SDL_ScaleModeNearest);
    
    return image_texture;
}
/* Генератор текста */
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
/* Загрузка текстуры */
void loadTexture(string texture_name)
{
    Texture *texture = new Texture;
    texture->name = texture_name;
    texture->texture = IMG_LoadTexture(renderer, ("data/Textures/" + texture_name).c_str());
    SDL_SetTextureScaleMode(texture->texture, SDL_ScaleModeNearest);

    if(textureList.head == NULL) textureList.head = texture;
    else
    {
        Texture *r = textureList.head;
        while(r->next != NULL) r = r->next;
        r->next = texture;
        r = nullptr;
    }
    textureList.count++;
}
/* Удаление текстуры */
void destroyTexture(string texture_name)
{
    if(textureList.count == 0) cout << "[destroyTexture] Пустой стек!" << endl;
    else
    {
        Texture *r = textureList.head;
        Texture *tmp = r;
        while(r != NULL && r->name != texture_name)
        {
            tmp = r;
            r = r->next;
        }
        if(r = NULL) cout << "[destroyTexture] Текстура не найдена!" << endl;
        else
        {
            if(textureList.head->name == texture_name)
                textureList.head = textureList.head->next;
            else
                tmp->next = r->next;
            delete r;
            textureList.count--;
        }
        tmp = nullptr;
        r = nullptr;
    }
}
/* Удаление текстур */
void clearTextures()
{
    if(textureList.count == 0) cout << "[clearTextures] Пустой стек!" << endl;
    else
    {
        Texture *r = textureList.head;
        Texture *tmp;
        while(r != NULL)
        {
            tmp = r->next;
            delete r;
            r = nullptr;
            r = tmp;
        }
        tmp = nullptr;
        r = nullptr;
        textureList.count = 0;
    }
}
/* Получение текстуры */
Texture* getTexture(string texture_name)
{
    Texture *get = NULL;
    if(textureList.count == 0) cout << "[getTexture] Пустой стек!" << endl;
    else
    {
        Texture *r = textureList.head;
        while(r != NULL && r->name != texture_name) r = r->next;
        if(r == NULL) cout << "[getTexture] Текстура не найдена!" << endl;
        else get = r;
    }
    return get;
}