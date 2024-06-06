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
        if(e->name == name)
        {
            guiObjectList.head = e->next;
            
            Button *p = buttonList.head;
            Button *tmp2 = p;
            if(p->object_info == e)
            {
                buttonList.head = p->next;
                delete p;
                p = nullptr;
            }
            else
            {
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
                    p = nullptr;
                }
            }
            delete e;
            e = nullptr;
        }
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
GUIObject* getGUIObject(string name)
{
    GUIObject *get = NULL;
    if(guiObjectList.count == 0) cout << "[getGUIObject] Пустой стек!" << endl;
    else
    {
        GUIObject *e = guiObjectList.head;
        while(e->name != name && e != NULL) e = e->next;
        if(e == NULL) cout << "[getGUIObject] Объект не найден!" << endl;
        else get = e;
    }
    return get;
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
    if(guiObject->text_info)
    {
        if(guiObject->text_info->allign == "left");
        else if(guiObject->text_info->allign == "center") guiObject->rect.x += guiObject->rect.w/2;
        else if(guiObject->text_info->allign == "right") guiObject->rect.x += guiObject->rect.w;
    }

    /* Заменяем текстуру */
    SDL_DestroyTexture(guiObject->texture);
    guiObject->texture = textGenerator(*guiObject->text_info);

    /* Смещаем снова */
    if(guiObject->text_info)
    {
        SDL_QueryTexture(guiObject->texture, nullptr, nullptr, &guiObject->rect.w, &guiObject->rect.h);
        if(guiObject->text_info->allign == "left");
        else if(guiObject->text_info->allign == "center") guiObject->rect.x -= guiObject->rect.w/2;
        else if(guiObject->text_info->allign == "right") guiObject->rect.x -= guiObject->rect.w;
    }
}

void updateGUIObject(string name, SDL_Texture *texture)
{
    if(guiObjectList.count == 0) cout << "[updateGUIObject] Пустой стек!" << endl;
    else
    {
        GUIObject *e = guiObjectList.head;
        while(e->name != name && e != NULL) e = e->next;
        if(e == NULL) cout << "[updateGUIObject] Объект не найден!" << endl;
        else
        {
            SDL_DestroyTexture(e->texture);
            e->texture = texture;
        };
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Создание новой стены */
void createWall(WallList *wList, int x, int y, int type)
{
    Wall *new_wall = new Wall;
    
    new_wall->x = x;
    new_wall->y = y;
    new_wall->type = type;
    new_wall->id = wList->count;
    
    if(wList->head == NULL) wList->head = new_wall;
    else
    {
        Wall *r = wList->head;
        while(r->next != NULL) r = r->next;
        r->next = new_wall;
        r = nullptr;
    }
    wList->count++;
}
/* Удалить стену */
void deleteWall(WallList *wList, unsigned short id)
{
    if(wList->count == 0) cout << "[deleteWall] Пустой стек!" << endl;
    else
    {
        Wall *r = wList->head;
        Wall *tmp = r;
        while(r != NULL && r->id != id)
        {
            tmp = r;
            r = r->next;
        }
        if(r == NULL) cout << "[deleteWall] Стена не найдена!" << endl;
        else
        {
            if(wList->head->id == id)
                wList->head = wList->head->next;
            else
                tmp->next = r->next;
            delete r;
            wList->count--;
        }
        tmp = nullptr;
        r = nullptr;
    }
}
/* Очистка стен */
void clearWalls(WallList *wList)
{
    if(wList->count == 0) cout << "[clearWalls] Пустой стек!" << endl;
    else
    {
        Wall *r = wList->head;
        Wall *tmp;
        while(r != NULL)
        {
            tmp = r->next;
            delete r;
            r = nullptr;
            r = tmp;
        }
        tmp = nullptr;
        r = nullptr;
        wList->count = 0;
    }
}
/* Обновление стены */
void updateWall(WallList *wList, unsigned short id)
{
    if(wList->count == 0) cout << "[updateWall] Пустой стек!" << endl;
    else
    {
        Wall *r = wList->head;
        Wall *tmp = r;
        while(r != NULL && r->id != id)
        {
            tmp = r;
            r = r->next;
        }
        if(r != NULL) cout << "[updateWall] Стена не найдена!" << endl;
        else
        {
            if(wList->head->id == id)
                wList->head = wList->head->next;
            else
                tmp->next = r->next;
            delete r;
            wList->count--;
        }
        tmp = nullptr;
        r = nullptr;
    }
}
/* Получение стены */
Wall* getWall(WallList *wList, int x, int y)
{
    Wall *get = NULL;
    if(wList->count == 0) cout << "[getWall] Пустой стек!" << endl;
    else
    {
        Wall *r = wList->head;
        while(r != NULL && (r->x != x || r->y != y)) r = r->next;
        if(r == NULL) /*cout << "[getWall] Стена не найдена!" << endl*/;
        else get = r;
        r = nullptr;
    }
    return get;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Создание нового объекта */
void createGameObject(GameObjectList *gameObjectList, int x, int y, int type)
{
    GameObject *new_object = new GameObject;
    
    new_object->x = x;
    new_object->y = y;
    new_object->type = type;
    new_object->id = gameObjectList->count;
    
    if(gameObjectList->head == NULL) gameObjectList->head = new_object;
    else
    {
        GameObject *r = gameObjectList->head;
        while(r->next != NULL) r = r->next;
        r->next = new_object;
        r = nullptr;
    }
    gameObjectList->count++;
}
/* Удалить объект */
void deleteGameObject(GameObjectList *gameObjectList, unsigned short id)
{
    if(gameObjectList->count == 0) cout << "[deleteGameObject] Пустой стек!" << endl;
    else
    {
        GameObject *r = gameObjectList->head;
        GameObject *tmp = r;
        while(r != NULL && r->id != id)
        {
            tmp = r;
            r = r->next;
        }
        if(r == NULL) cout << "[deleteGameObject] Объект не найден!" << endl;
        else
        {
            if(gameObjectList->head->id == id)
                gameObjectList->head = gameObjectList->head->next;
            else
                tmp->next = r->next;
            delete r;
            gameObjectList->count--;
        }
        tmp = nullptr;
        r = nullptr;
    }
}
/* Очистка объектов */
void clearGameObjects(GameObjectList *gameObjectList)
{
    if(gameObjectList->count == 0) cout << "[clearGameobjects] Пустой стек!" << endl;
    else
    {
        GameObject *r = gameObjectList->head;
        GameObject *tmp;
        while(r != NULL)
        {
            tmp = r->next;
            delete r;
            r = nullptr;
            r = tmp;
        }
        tmp = nullptr;
        r = nullptr;
        gameObjectList->count = 0;
    }
}
/* Обновление объекта */
void updateGameObject(GameObjectList *gameObjectList, unsigned short id)
{
    if(gameObjectList->count == 0) cout << "[updateGameObject] Пустой стек!" << endl;
    else
    {
        GameObject *r = gameObjectList->head;
        GameObject *tmp = r;
        while(r != NULL && r->id != id)
        {
            tmp = r;
            r = r->next;
        }
        if(r != NULL) cout << "[updateGameObject] Объект не найден!" << endl;
        else
        {
            if(gameObjectList->head->id == id)
                gameObjectList->head = gameObjectList->head->next;
            else
                tmp->next = r->next;
            delete r;
            gameObjectList->count--;
        }
        tmp = nullptr;
        r = nullptr;
    }
}
/* Получение объекта */
GameObject* getGameObject(GameObjectList *gameObjectList, int x, int y)
{
    GameObject *get = NULL;
    if(gameObjectList->count == 0) cout << "[getGameObject] Пустой стек!" << endl;
    else
    {
        GameObject *r = gameObjectList->head;
        while(r != NULL && (r->x != x || r->y != y)) r = r->next;
        if(r == NULL) /*cout << "[getGameObject] Объект не найден!" << endl*/;
        else get = r;
        r = nullptr;
    }
    return get;
}

void addInventory(Player *player, int type)
{
    if(player->inventory[0] == 0) player->inventory[0] = type;
    else if(player->inventory[1] == 0) player->inventory[1] = type;
    else if(player->inventory[2] == 0) player->inventory[2] = type;
}

bool checkInventory(Player *player)
{
    return !(player->inventory[0]*player->inventory[1]*player->inventory[2]);
}

void deleteInventory(Player *player, int slot)
{
    if(player->inventory[slot-1] != 0) player->inventory[0] = 0;
    else if(player->inventory[slot-1] != 0) player->inventory[1] = 0;
    else if(player->inventory[slot-1] != 0) player->inventory[2] = 0;
}