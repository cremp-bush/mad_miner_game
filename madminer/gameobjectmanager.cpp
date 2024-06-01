#include <iostream>
#include <SDL.h>
#include "header.h"

using namespace std;

void createGameObjectStart(GameObject object)
{
    GameObject *gameObject = new GameObject;
    *gameObject = object;
    if(gameObjectList.head == NULL) gameObjectList.head = gameObject;
    else
    {
        gameObject->next = gameObjectList.head;
        gameObjectList.head = gameObject;                          
    }
    gameObjectList.count++;
}

void createGameObjectEnd(GameObject object)
{
    GameObject *gameObject = new GameObject;
    *gameObject = object;
    if(gameObjectList.head == NULL) gameObjectList.head = gameObject;
    else
    {
        GameObject *e = gameObjectList.head;
        while(e->next != NULL) e = e->next;
        e->next = gameObject;
    }
    gameObjectList.count++;
}

void deleteGameObject(string name)
{
    if(gameObjectList.count == 0) cout << "[deleteGameObject] Пустой стек!";
    else
    {
        GameObject *e = gameObjectList.head;
        GameObject *tmp = e;
        while(e->name != name && e != NULL)
        {
            tmp = e;
            e = e->next;
        }
        if(e == NULL) cout << "[deleteGameObject] Объект не найден!";
        else
        {
            tmp->next = e->next;
            SDL_DestroyTexture(e->texture);
            delete e;
            gameObjectList.count--;
        }
    }
}

void clearGameObjects()
{
    if(gameObjectList.count == 0) cout << "[clearGameObject] Пустой стек!";
    else
    {
        GameObject *e = gameObjectList.head;
        while(e != NULL)
        {
            GameObject *tmp = e->next;
            SDL_DestroyTexture(e->texture);
            delete e;
            e = tmp;
            gameObjectList.count--;
        }
        gameObjectList.head = NULL;
    }
}

GameObject getGameObject(string name)
{
    GameObject *get = NULL;
    if(gameObjectList.count == 0) cout << "[getGameObject] Пустой стек!";
    else
    {
        GameObject *e = gameObjectList.head;
        while(e->name != name && e != NULL) e = e->next;
        if(e == NULL) cout << "[getGameObject] Объект не найден!";
        else get = e;
    }
    return *get;
}

void setGameObject(GameObject object, string name)
{
    if(gameObjectList.count == 0) cout << "[setGameObject] Пустой стек!";
    else
    {
        GameObject *e = gameObjectList.head;
        while(e->name != name && e != NULL) e = e->next;
        if(e == NULL) cout << "[setGameObject] Объект не найден!";
        else
        {
            SDL_DestroyTexture(e->texture);
            object.next = e->next;
            *e = object;
        }
    }
}