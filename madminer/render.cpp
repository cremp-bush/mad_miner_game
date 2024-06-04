#include <iostream>
#include "header.h"
using namespace std;

void renderGround()
{
    
}

void renderGameObjects()
{
    
}
//15:9
void renderWalls(WallList *wList, int x, int y)
{
    SDL_RenderClear(renderer);
    for(int j = y-4; j <= y+4; j++)
        for(int i = x-7; i <= x+7; i++)
        {
            Wall *wall = getWall(wList, i, j);
            if(wall != NULL)
            {
                SDL_Rect rect = {40+(i-(x-7))*80, (j-(y-4))*80, 80, 80};
                SDL_Texture *texture = NULL;

                if(wall->type != 0 && wall->type != 5)
                {
                    Wall *wallUp = getWall(wList, i, j-1);
                    Wall *wallLeft = getWall(wList, i-1, j);
                    Wall *wallDown = getWall(wList, i, j+1);
                    Wall *wallRight = getWall(wList, i+1, j);
                    if(!wallUp && !wallLeft && !wallDown && !wallRight) texture = getTexture("rock.png")->texture;
                    else if(!wallUp && !wallLeft && wallDown && !wallRight) texture = getTexture("rockD.png")->texture;
                    else if(!wallUp && !wallLeft && wallDown && wallRight) texture = getTexture("rockDR.png")->texture;
                    else if(!wallUp && wallLeft && !wallDown && !wallRight) texture = getTexture("rockL.png")->texture;
                    else if(!wallUp && wallLeft && wallDown && !wallRight) texture = getTexture("rockLD.png")->texture;
                    else if(!wallUp && wallLeft && wallDown && wallRight) texture = getTexture("rockLDR.png")->texture;
                    else if(!wallUp && wallLeft && !wallDown && wallRight) texture = getTexture("rockLR.png")->texture;
                    else if(!wallUp && !wallLeft && !wallDown && wallRight) texture = getTexture("rockR.png")->texture;
                    else if(wallUp && !wallLeft && !wallDown && !wallRight) texture = getTexture("rockU.png")->texture;
                    else if(wallUp && !wallLeft && wallDown && !wallRight) texture = getTexture("rockUD.png")->texture;
                    else if(wallUp && !wallLeft && wallDown && wallRight) texture = getTexture("rockUDR.png")->texture;
                    else if(wallUp && wallLeft && !wallDown && !wallRight) texture = getTexture("rockUL.png")->texture;
                    else if(wallUp && wallLeft && wallDown && !wallRight) texture = getTexture("rockULD.png")->texture;
                    else if(wallUp && wallLeft && wallDown && wallRight) texture = getTexture("rockULDR.png")->texture;
                    else if(wallUp && wallLeft && !wallDown && wallRight) texture = getTexture("rockULR.png")->texture;
                    else if(wallUp && !wallLeft && !wallDown && wallRight) texture = getTexture("rockUR.png")->texture;
                    SDL_RenderCopy(renderer, texture, NULL, &rect);
                    wallUp = nullptr;
                    wallLeft = nullptr;
                    wallDown = nullptr;
                    wallRight = nullptr;
                    
                    if(wall->type == 2) texture = getTexture("gold.png")->texture;
                    else if(wall->type == 3) texture = getTexture("rockLR.png")->texture;
                    else if(wall->type == 5) texture = getTexture("gold.png")->texture;
                    if(wall->type == 2 || wall->type == 3 || wall->type == 5) SDL_RenderCopy(renderer, texture, NULL, &rect);
                }
                texture = nullptr;
            }
            wall = nullptr;
        }
    SDL_Rect rect = {40+7*80, 4*80, 80, 80};
    SDL_RenderCopy(renderer, getTexture("diamond.png")->texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

void renderGases()
{
    
}

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