#include <iostream>
#include <SDL.h>
#include "header.h"
using namespace std;

Button* userInput()
{
    Button *button_pressed = NULL;
    
    /* Действие на закрытие окна на крестик */
    if(event.type == SDL_QUIT)
    {
        scene = "Escape";
        quit = true;
    }

    /* Действие на нажатие Escape */
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
    {
        if(scene == "Main Menu") scene = "Escape";
        else if(scene == "Settings Menu")
        {
            scene = "Main Menu";
            initSettings();
            updateFrame();
        }
        else if(scene == "New Game Menu") scene = "Main Menu";
        else if(scene == "Game") scene = "Pause";
        else if(scene == "Pause") scene = "Game";
        quit = true;
    }

    /* Нажатие на кнопку */
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        if(buttonList.count != 0)
        {
            Button *p = buttonList.head;
            while(p != NULL)
            {
                /* Проверка на нахождение курсора на кнопке */
                if((event.button.x >= p->object_info->rect.x && event.button.x <= p->object_info->rect.x + p->object_info->rect.w )&&
                    (event.button.y >= p->object_info->rect.y && event.button.y <= p->object_info->rect.y + p->object_info->rect.h))
                {
                    button_pressed = p;
                    break;
                }
                p = p->next;
            }
        }
    }

    if(event.type == SDL_MOUSEMOTION && select == NULL)
    {
        if(buttonList.count != 0)
        {
            Button *p = buttonList.head;
            while(p != NULL)
            {
                /* Проверка на нахождение курсора на кнопке */
                if((event.button.x >= p->object_info->rect.x && event.button.x <= p->object_info->rect.x + p->object_info->rect.w )&&
                    (event.button.y >= p->object_info->rect.y && event.button.y <= p->object_info->rect.y + p->object_info->rect.h))
                {
                    select = p;
                    p->object_info->text_info->text.insert(0, "> ");
                    updateGUIObject(select->object_info);
                    updateFrame();
                    break;
                }
                p = p->next;
            }
        }
    }
    if(event.type == SDL_MOUSEMOTION && select != NULL)
    {
        /* Проверка на нахождение курсора на кнопке */
        if(!(event.button.x >= select->object_info->rect.x && event.button.x <= select->object_info->rect.x + select->object_info->rect.w )||
            !(event.button.y >= select->object_info->rect.y && event.button.y <= select->object_info->rect.y + select->object_info->rect.h))
        {
            select->object_info->text_info->text.erase(0, 2);
            updateGUIObject(select->object_info);
            updateFrame();
            select = NULL;
        }
    }
    return button_pressed;
}