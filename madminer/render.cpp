#include <iostream>
#include "header.h"
using namespace std;

void renderGUIObjects()
{
    if(guiObjectList.count == 0);
    else
    {
        GUIObject *e = guiObjectList.head;
        while(e != NULL)
        {
            SDL_RenderCopy(renderer, e->texture, NULL, &e->rect);
            e = e->next;
        }
    }
}

void updateFrame()
{
    SDL_RenderClear(renderer);
    renderGUIObjects();
    SDL_RenderPresent(renderer);
}