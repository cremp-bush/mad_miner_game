/*#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "header.h"

void createEffect(EffectList &eList, SDL_Texture *texture, std::string name, short frames = 1)
{
    Effect *effect = new Effect;
    effect->name = name;
    effect->frames = frames;
    effect->current_frame = 1;
    effect->texture = texture;
    if(eList.head == NULL) eList.head = effect;
    else
    {
        effect->next = eList.head;
        eList.head = effect;
    }
    eList.count++;
}

void deleteEffect(EffectList &eList, std::string name)
{
    if(eList.count == 0) std::cout << "[deleteEffect] Пустой стек!";
    else
    {
        Effect *e = eList.head;
        Effect *tmp = e;
        while(e->name != name && e != NULL)
        {
            tmp = e;
            e = e->next;
        }
        if(e == NULL) std::cout << "[deleteEffect] Эффект не найден!";
        else
        {
            tmp->next = e->next;
            SDL_DestroyTexture(e->texture);
            delete e;
            eList.count--;
        }
    }
}

void clearEffects(EffectList &eList)
{
    if(eList.count == 0) std::cout << "[clearEffect] Пустой стек!";
    else
    {
        Effect *e = eList.head;
        while(e != NULL)
        {
            Effect *tmp = e->next;
            SDL_DestroyTexture(e->texture);
            delete e;
            e = tmp;
            eList.count--;
        }
    }
}

void updateEffects(EffectList &eList)
{
    
}*/