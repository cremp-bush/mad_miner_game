#include <iostream>
#include <SDL.h>
#include "header.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Создание новой кнопки */
void createButton(GUIObject object)
{
    createGUIObject(object);
    /* Создание новой кнопки */
    Button *button = new Button;
    /* Инициализация кнопки */
    GUIObject *e = guiObjectList.head;
    while(e->next != NULL) e = e->next;
    button->object_info = e;
    /* Инициализация главной и следующей кнопки */
    if(buttonList.head == NULL) buttonList.head = button;
    else
    {
        Button *p = buttonList.head;
        while(p->next != NULL) p = p->next;
        p->next = button;
    }
    buttonList.count++;
}

void createButton(string name, SDL_Rect rect, SDL_Texture *texture, string allign, float size)
{
    createGUIObject(name, rect, texture, allign, size);
    /* Создание новой кнопки */
    Button *button = new Button;
    /* Инициализация кнопки */
    GUIObject *e = guiObjectList.head;
    while(e->next != NULL) e = e->next;
    button->object_info = e;
    /* Инициализация главной и следующей кнопки */
    if(buttonList.head == NULL) buttonList.head = button;
    else
    {
        Button *p = buttonList.head;
        while(p->next != NULL) p = p->next;
        p->next = button;                 
    }
    buttonList.count++;
}

void createButton(string name, SDL_Rect rect, TextInfo text_info)
{
    createGUIObject(name, rect, text_info);
    /* Создание новой кнопки */
    Button *button = new Button;
    /* Инициализация кнопки */
    GUIObject *e = guiObjectList.head;
    while(e->next != NULL) e = e->next;
    button->object_info = e;
    /* Инициализация главной и следующей кнопки */
    if(buttonList.head == NULL) buttonList.head = button;
    else
    {
        Button *p = buttonList.head;
        while(p->next != NULL) p = p->next;
        p->next = button;                    
    }
    buttonList.count++;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Создание нового GUI объекта */
void createGUIObject(GUIObject object)
{
    /* Создание нового GUI объекта */
    GUIObject *guiObject = new GUIObject;
    /* Инициализация GUI объекта */
    *guiObject = object;
    /* Инициализация главного и следующего GUI объекта */
    if(guiObjectList.head == NULL) guiObjectList.head = guiObject;
    else
    {
        GUIObject *e = guiObjectList.head;
        while(e->next != NULL) e = e->next;
        e->next = guiObject;                         
    }
    guiObjectList.count++;
}

void createGUIObject(string name, SDL_Rect rect, SDL_Texture *texture, string allign, float size)
{
    /* Создание нового GUI объекта */
    GUIObject *guiObject = new GUIObject;
    /* Инициализация GUI объекта */
    guiObject->name = name;
    guiObject->rect = rect;
    SDL_QueryTexture(texture, nullptr, nullptr, &guiObject->rect.w, &guiObject->rect.h);
    guiObject->rect.w *= size;
    guiObject->rect.h *= size;
    if(allign == "left");
    else if(allign == "center") guiObject->rect.x -= guiObject->rect.w/2;
    else if(allign == "right") guiObject->rect.x -= guiObject->rect.w;
    guiObject->size = size;
    guiObject->texture = texture;
    /* Инициализация главного и следующего GUI объекта */
    if(guiObjectList.head == NULL) guiObjectList.head = guiObject;
    else
    {
        GUIObject *e = guiObjectList.head;
        while(e->next != NULL) e = e->next;
        e->next = guiObject;  
    }
    guiObjectList.count++;
}

void createGUIObject(string name, SDL_Rect rect, TextInfo text_info)
{
    /* Создание нового GUI объекта */
    GUIObject *guiObject = new GUIObject;
    /* Инициализация GUI объекта */
    guiObject->name = name;
    guiObject->rect = rect;
    SDL_Texture *texture = textGenerator(text_info);
    SDL_QueryTexture(texture, nullptr, nullptr, &guiObject->rect.w, &guiObject->rect.h);
    if(text_info.allign == "left");
    else if(text_info.allign == "center") guiObject->rect.x -= guiObject->rect.w/2;
    else if(text_info.allign == "right") guiObject->rect.x -= guiObject->rect.w;
    guiObject->texture = texture;
    TextInfo *text = new TextInfo;
    *text = text_info;
    guiObject->text_info = text;
    /* Инициализация главного и следующего GUI объекта */
    if(guiObjectList.head == NULL) guiObjectList.head = guiObject;
    else
    {
        GUIObject *e = guiObjectList.head;
        while(e->next != NULL) e = e->next;
        e->next = guiObject;
    }
    guiObjectList.count++;
}
// void createGameObjectEnd(GameObject object)
// {
//     GameObject *gameObject = new GameObject;
//     *gameObject = object;
//     if(gameObjectList.head == NULL) gameObjectList.head = gameObject;
//     else
//     {
//         GameObject *e = gameObjectList.head;
//         while(e->next != NULL) e = e->next;
//         e->next = gameObject;
//     }
//     gameObjectList.count++;
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Удаление GUI объекта */
void deleteGUIObject(string name)
{
    if(guiObjectList.count == 0) cout << "[deleteGUIObject] Пустой стек!" << endl;
    else
    {
        /* Поиск объекта по имени */
        GUIObject *e = guiObjectList.head;
        GUIObject *tmp1 = e;
        while(e->name != name && e != NULL)
        {
            tmp1 = e;
            e = e->next;
        }
        if(e == NULL) cout << "[deleteGUIObject] Объект не найден!" << endl;
        else
        {
            Button *p = buttonList.head;
            Button *tmp2 = p;
            /* Поиск объекта в структуре кнопок */
            while(p->object_info != e && p != NULL)
            {
                tmp2 = p;
                p = p->next;
            }
            /* Удаление кнопки */
            if(p != NULL)
            {
                if(p == buttonList.head) buttonList.head = NULL;
                tmp2->next = p->next;
                delete p;
            }
            tmp1->next = e->next;
            /* Удаление объекта */
            if(e == guiObjectList.head) guiObjectList.head = NULL;
            SDL_DestroyTexture(e->texture);
            if(e->text_info != NULL) delete e->text_info;
            delete e;
            guiObjectList.count--;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Удалить все GUI объекты */
void clearGUIObjects()
{
    if(guiObjectList.count == 0) cout << "[clearGUIObjects] Пустой стек!" << endl;
    else
    {
        GUIObject *e = guiObjectList.head;
        /* Очистка объектов */
        while(e != NULL)
        {
            GUIObject *tmp1 = e->next;
            SDL_DestroyTexture(e->texture);
            if(e->text_info != NULL) delete e->text_info;
            delete e;
            e = tmp1;
            guiObjectList.count--;
        }
        /* Очистка кнопок */
        Button *p = buttonList.head;
        while(p != NULL)
        {
            Button *tmp2 = p->next;
            delete p;
            p = tmp2;
            buttonList.count--;
        }
        /* Подготовка структур к дальнейшему использованию */
        guiObjectList.head = NULL;
        buttonList.head = NULL;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Получить GUI объект */
GUIObject getGUIObject(string name)
{
    GUIObject *get = NULL;
    if(gameObjectList.count == 0) cout << "[getGUIObject] Пустой стек!" << endl;
    else
    {
        GUIObject *e = guiObjectList.head;
        while(e->name != name && e != NULL) e = e->next;
        if(e == NULL) cout << "[getGUIObject] Объект не найден!" << endl;
        else get = e;
    }
    return *get;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Заменить GUI объект */
// void setGUIObject(GUIObject object, string name)
// {
//     if(guiObjectList.count == 0) cout << "[setGUIObject] Пустой стек!";
//     else
//     {
//         GUIObject *e = guiObjectList.head;
//         while(e->name != name && e != NULL) e = e->next;
//         if(e == NULL) cout << "[setGUIObject] Объект не найден!";
//         else
//         {
//             SDL_DestroyTexture(e->texture);
//             if(e->text_info != NULL)
//             {
//                 delete e->text_info;
//                 e->text_info = NULL;
//             }
//
//             if(object.text_info != NULL)
//             {
//                 TextInfo *text = new TextInfo;
//                 SDL_Texture *texture = textGenerator(*object.text_info);
//                 SDL_QueryTexture(texture, nullptr, nullptr, &object.rect.w, &object.rect.h);
//                 object.texture = texture;
//             }
//             else
//             {
//                 SDL_QueryTexture(object.texture, nullptr, nullptr, &object.rect.w, &object.rect.h);
//                 object.rect.w *= object.size;
//                 object.rect.h *= object.size;
//             }
//             object.next = e->next;
//             *e = object;
//         }
//     }
// }

void updateGUIObject(GUIObject *guiObject)
{
    /* Возвращаем на место смещение */
    if(guiObject->text_info->allign == "left");
    else if(guiObject->text_info->allign == "center") guiObject->rect.x += guiObject->rect.w/2;
    else if(guiObject->text_info->allign == "right") guiObject->rect.x += guiObject->rect.w;

    /* Заменяем текстуру */
    SDL_DestroyTexture(guiObject->texture);
    guiObject->texture = textGenerator(*guiObject->text_info);

    /* Смещаем снова */
    SDL_QueryTexture(guiObject->texture, nullptr, nullptr, &guiObject->rect.w, &guiObject->rect.h);
    if(guiObject->text_info->allign == "left");
    else if(guiObject->text_info->allign == "center") guiObject->rect.x -= guiObject->rect.w/2;
    else if(guiObject->text_info->allign == "right") guiObject->rect.x -= guiObject->rect.w;
}