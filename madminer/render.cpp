#include <iostream>
#include "header.h"

using namespace std;

void renderGameObjects()
{
    if(gameObjectList.count == 0);
    else
    {
        GameObject *e = gameObjectList.head;
        while(e != NULL)
        {
            SDL_RenderCopy(renderer, e->texture, NULL, &e->rect);
            e = e->next;
        }
    }
}