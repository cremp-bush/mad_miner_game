#include <iostream>
#include <SDL.h>
#include "header.h"

using namespace std;

void userInteraction()
{
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        if(gameObjectList.count == 0);
        else
        {
            GameObject *e = gameObjectList.head;
            while(e != NULL)
            {
                if(e->isButton)
                {
                    if((event.button.x >= e->rect.x && event.button.x <= e->rect.x + e->rect.w )&&
                        (event.button.y >= e->rect.y && event.button.y <= e->rect.y + e->rect.h))
                    {
                        if(e->name == "SettingsButton") loadSettingsMenu();
                        else if(e->name == "ToMainMenuButton") loadMainMenu();
                        else if(e->name == "NewGameButton") loadNewGameMenu();
                        else if(e->name == "mode1Button") loadNewGameMenu();
                        else if(e->name == "QuitButton") quit = true;
                        break;
                    }
                }
                e = e->next;
            }
    }
    if(event.type == SDL_MOUSEMOTION && select == NULL)
    {
        if(gameObjectList.count == 0);
        else
        {
            GameObject *e = gameObjectList.head;
            while(e != NULL)
            {
                if(e->isButton)
                {
                    if((event.button.x >= e->rect.x && event.button.x <= e->rect.x + e->rect.w )&&
                        (event.button.y >= e->rect.y && event.button.y <= e->rect.y + e->rect.h))
                    {
                        select = e;
                        if(select->textInfo.allign == "left") select->rect.x;
                        else if(select->textInfo.allign == "center") select->rect.x += select->rect.w/2;
                        else if(select->textInfo.allign == "right") select->rect.x += select->rect.w;
                        setGameObject(textGenerator(select->name, "> "+select->textInfo.text, select->rect.x, select->rect.y, select->textInfo.size, select->textInfo.allign, select->isButton), select->name);
                        
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
                        SDL_RenderClear(renderer);
                        
                        renderGameObjects();
                        SDL_RenderPresent(renderer);
                    }
                }
                e = e->next;
            }
        }
    }
    else if(event.type == SDL_MOUSEMOTION && select != NULL)
    {
        if(!(event.button.x >= select->rect.x && event.button.x <= select->rect.x + select->rect.w )||
            !(event.button.y >= select->rect.y && event.button.y <= select->rect.y + select->rect.h))
        {
            select->textInfo.text.erase(0, 2);
            if(select->textInfo.allign == "left") select->rect.x;
            else if(select->textInfo.allign == "center") select->rect.x += select->rect.w/2;
            else if(select->textInfo.allign == "right") select->rect.x += select->rect.w;
            setGameObject(textGenerator(select->name, select->textInfo.text, select->rect.x, select->rect.y, select->textInfo.size, select->textInfo.allign, select->isButton), select->name);
            select = NULL;
            
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
            SDL_RenderClear(renderer);
            
            renderGameObjects();
            SDL_RenderPresent(renderer);
        }
    }
}