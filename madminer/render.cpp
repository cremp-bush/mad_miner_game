#include <iostream>
#include "header.h"
using namespace std;

void renderGround()
{
    
}

void renderGameObjects(Player *player, int ***map)
{
    for(int y = player->y-4; y <= player->y+4; y++)
        for(int x = player->x-7; x <= player->x+7; x++)
        {
            if(x >= 0 && y >= 0 && x < map_width && y < map_height && map[x][y])
            {
                SDL_Rect rect = {40+(x-(player->x-7))*80, (y-(player->y-4))*80, 80, 80};
                SDL_Texture *texture = NULL;
                
                if(map[x][y][1] == 1) texture = getTexture("1.png")->texture;
                else if(map[x][y][1] == 2) texture = getTexture("2.png")->texture;
                else if(map[x][y][1] == 3) texture = getTexture("3.png")->texture;
                else if(map[x][y][1] == 5) texture = getTexture("generator.png")->texture;
                SDL_RenderCopy(renderer, texture, NULL, &rect);
            }
        }
    SDL_Rect rect = {40+7*80, 4*80, 80, 80};
    SDL_RenderCopy(renderer, player->texture->texture, NULL, &rect);
}
//15:9
void renderWalls(Player *player, int ***map)
{
    for(int y = player->y-4; y <= player->y+4; y++)
        for(int x = player->x-7; x <= player->x+7; x++)
        {
            SDL_Rect rect = {40+(x-(player->x-7))*80, (y-(player->y-4))*80, 80, 80};
            SDL_Texture *texture = NULL;
            
            if(x >= 0 && y >= 0 && x < map_width && y < map_height && map[x][y][0])
            {
                bool wallUp = 0;
                if(y-1 >= 0) wallUp = map[x][y-1][0];
                bool wallLeft = 0;
                if(x-1 >= 0) wallLeft = map[x-1][y][0];
                bool wallDown = 0;
                if(y+1 < map_height) wallDown = map[x][y+1][0];
                bool wallRight = 0;
                if(x+1 < map_width) wallRight = map[x+1][y][0];
                if(wallUp && wallLeft && wallDown && wallRight) texture = getTexture("rockULDR.png")->texture;
                else
                {
                    SDL_RenderCopy(renderer, getTexture("ground.png")->texture, NULL, &rect);
                    if(!wallUp && !wallLeft && wallDown && !wallRight) texture = getTexture("rockD.png")->texture;
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
                    else if(wallUp && wallLeft && !wallDown && wallRight) texture = getTexture("rockULR.png")->texture;
                    else if(wallUp && !wallLeft && !wallDown && wallRight) texture = getTexture("rockUR.png")->texture;
                    else if(!wallUp && !wallLeft && !wallDown && !wallRight) texture = getTexture("rock.png")->texture;
                }
                SDL_RenderCopy(renderer, texture, NULL, &rect);
                
                if(map[x][y][0] == 2) texture = getTexture("gold.png")->texture;
                else if(map[x][y][0] == 3) texture = getTexture("diamond.png")->texture;
                else if(map[x][y][0] == 4) texture = getTexture("emerald.png")->texture;
                else if(map[x][y][0] == 5) texture = getTexture("elevator.png")->texture;
                if(map[x][y][0] != 1) SDL_RenderCopy(renderer, texture, NULL, &rect);

                texture = nullptr;
            }
            else SDL_RenderCopy(renderer, getTexture("ground.png")->texture, NULL, &rect);
        }
}

void renderGases()
{
    
}

void renderInterface(Player *player)
{
    // Стамина
    SDL_Rect stamina_bar = {40, 720-60, 400/100*player->stamina, 34};
    SDL_SetRenderDrawColor(renderer, 200, 200, 0, 255);
    SDL_RenderFillRect(renderer, &stamina_bar);
    stamina_bar = {40, 720-60, 400, 34};
    SDL_RenderCopy(renderer, getTexture("stamina_bar.png")->texture, NULL, &stamina_bar);
    // Здоровье
    SDL_Rect health_bar = {40, 720-100, int(320/100.0*player->health), 34};
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_RenderFillRect(renderer, &health_bar);
    health_bar = {40, 720-100, 320, 34};
    SDL_RenderCopy(renderer, getTexture("health_bar.png")->texture, NULL, &health_bar);
    // Показатели золота, алмазов, изумрудов
    SDL_Rect gold = {40, 80, 64, 64};
    SDL_RenderCopy(renderer, getTexture("gold_ingot.png")->texture, NULL, &gold);
    SDL_Rect diamond = {40, 144, 64, 64};
    SDL_RenderCopy(renderer, getTexture("diamond_ingot.png")->texture, NULL, &diamond);
    SDL_Rect emerald = {40, 208, 64, 64};
    SDL_RenderCopy(renderer, getTexture("emerald_ingot.png")->texture, NULL, &emerald);
    // Показатель противогаза
    SDL_Rect gas_mask_bar = {1280-280, 720-80, int(240/100.0*player->filter), 34};
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderFillRect(renderer, &gas_mask_bar);
    gas_mask_bar = {1280-280, 720-80, 240, 34};
    SDL_RenderCopy(renderer, getTexture("gas_mask_bar.png")->texture, NULL, &gas_mask_bar);
    SDL_Rect gas_mask = {1280-200, 720-160, 80, 80};
    SDL_RenderCopy(renderer, getTexture("gas_mask.png")->texture, NULL, &gas_mask);
    gas_mask = {1280-150, 720-120, 32, 32};
    if(player->gas_mask) SDL_RenderCopy(renderer, getTexture("yes.png")->texture, NULL, &gas_mask);
    else SDL_RenderCopy(renderer, getTexture("no.png")->texture, NULL, &gas_mask);
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

void updateFrame(Player *player, int ***map)
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    renderWalls(player, map);
    renderGameObjects(player, map);
    renderGUIObjects();
    renderInterface(player);
    SDL_RenderPresent(renderer);
}

void updateFrame()
{
    SDL_RenderClear(renderer);
    renderGUIObjects();
    SDL_RenderPresent(renderer);
}