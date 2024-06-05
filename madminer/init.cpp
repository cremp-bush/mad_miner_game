#include <iostream>
#include "fstream"
#include "string"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include "header.h"

bool initSdl()
{
    bool success = false;
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) std::cout << "Ошибка инициализации SDL!";
    else if(TTF_Init() != 0) std::cout << "Ошибка инициализации SDL_ttf!";
    else if(SDLNet_Init() != 0) std::cout << "Ошибка инициализации SDL_net!";
    else if(Mix_OpenAudio(22050, MIX_INIT_OGG, 2, 1024)) std::cout << "Ошибка инициализации SDL_mixer!";
    else if(IMG_Init(IMG_INIT_PNG) == 0) std::cout << "Ошибка инициализации SDL_image!";
    else success = true;
    return success;
}

void stopSdl()
{
    IMG_Quit();
    Mix_Quit();
    SDLNet_Quit();
    TTF_Quit();
    SDL_Quit();
}

void initSettings()
{
    ifstream settings("data/settings.txt", ios::in);
    string word;
    bool resolution, vsync, master_volume, music_volume, fullscreen;
    resolution = vsync =master_volume = music_volume = fullscreen = false;
    
    while(settings)
    {
        settings >> word;
        if(word == "SCREEN_WIDTH")
        {
            settings >> word;
            if(SCREEN_WIDTH != stoi(word))
            {
                resolution = true;
                SCREEN_WIDTH = stoi(word);
            }
        }
        else if(word == "SCREEN_HEIGHT")
        {
            settings >> word;
            if(SCREEN_HEIGHT != stoi(word))
            {
                resolution = true;
                SCREEN_HEIGHT = stoi(word);
            }
        }
        else if(word == "VSYNC")
        {
            settings >> word;
            if(VSYNC != stoi(word))
            {
                vsync = true;
                VSYNC = stoi(word);
            }
        }
        else if(word == "MASTER_VOLUME")
        {
            settings >> word;
            if(MASTER_VOLUME != stoi(word))
            {
                master_volume = true;
                MASTER_VOLUME = stoi(word);
            }
        }
        else if(word == "MUSIC_VOLUME")
        {
            settings >> word;
            if(MUSIC_VOLUME != stoi(word))
            {
                music_volume = true;
                MUSIC_VOLUME = stoi(word);
            }
        }
        else if(word == "FULLSCREEN_MODE")
        {
            settings >> word;
            if(FULLSCREEN_MODE != stoi(word))
            {
                fullscreen = true;
                FULLSCREEN_MODE = stoi(word);
            }
        }
    }
    settings.close();
    
    if(resolution) SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(vsync)
    {
        SDL_DestroyRenderer(renderer);
        if(VSYNC) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
        else renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        if(FULLSCREEN_MODE)
        {
            SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
            SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN || SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }
    Mix_MasterVolume(MIX_MAX_VOLUME/100.0 * MASTER_VOLUME);
    Mix_VolumeMusic(MIX_MAX_VOLUME/100.0 * MUSIC_VOLUME);
    if(fullscreen)
    {
        if(FULLSCREEN_MODE) SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN || SDL_WINDOW_FULLSCREEN_DESKTOP);
        else SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
    }
    if(resolution || vsync || master_volume || music_volume || fullscreen) updateFrame();
}

bool intersection(SDL_Rect *rooms, int i)
{
    bool intersection = false;
    if(rooms[i].x == 0) intersection = true;
    else
    {
        for(int j = 0; j < i; j++)
        {
            if(abs(rooms[i].x - rooms[j].x) < (rooms[i].w + rooms[j].w) &&
            abs(rooms[i].y - rooms[j].y) < (rooms[i].h + rooms[j].h))
            {
                intersection = true;
                break;
            }
        }
    }
    return intersection;
}

void initMap(Player *player, int ***map)
{
    int map_layers = 4;
    int room_minW = 3;
    int room_maxW = 4;
    int room_minH = 2;
    int room_maxH = 6;

    int room_x, room_y, room_width, room_height, room_count;
    
    ofstream groundlayer("data/Saves/groundlayer.txt");
    ofstream walllayer("data/Saves/walllayer.txt");
    ofstream objectlayer("data/Saves/objectlayer.txt");
    ofstream gaslayer("data/Saves/gaslayer.txt");

    srand(time(NULL));
    
    room_count = map_width*map_height/(map_width+map_height);

    /* Массив пространств золота */
    SDL_Rect *gold = new SDL_Rect[room_count*2];
    
    for(int i = 0; i < room_count*2; i++)
    {
        room_x = rand()%(map_width-1-1)+1;
        room_y = rand()%(map_width-1-1)+1;
        room_width = rand()%(1 - 3) + 1;
        room_height = rand()%(1 - 2) + 1;

        if(room_x + room_width >= map_width)
        {
            i--;
            continue;
        }
        if(room_y + room_height >= map_height)
        {
            i--;
            continue;
        }
        gold[i] = {room_x, room_y, room_width, room_height};
    }

    /* Создание пространств золота */
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            bool room = false;
            for(int i = 0; i < room_count*2; i++)
            {
                if((x >= gold[i].x && x < gold[i].x+gold[i].w) && (y >= gold[i].y && y < gold[i].y+gold[i].h))
                {
                    map[x][y][0] = 2;
                    
                    room = true;
                    break;
                }
            }
        }
    }
    /* Массив пространств алмазов */
    SDL_Rect *diamond = new SDL_Rect[room_count*2];
    
    for(int i = 0; i < room_count*2; i++)
    {
        room_x = rand()%(map_width-1-1)+1;
        room_y = rand()%(map_width-1-1)+1;
        room_width = rand()%(1 - 3) + 1;
        room_height = rand()%(1 - 2) + 1;

        if(room_x + room_width >= map_width)
        {
            i--;
            continue;
        }
        if(room_y + room_height >= map_height)
        {
            i--;
            continue;
        }
        diamond[i] = {room_x, room_y, room_width, room_height};
    }

    /* Создание пространств алмазов */
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            bool room = false;
            for(int i = 0; i < room_count*2; i++)
            {
                if((x >= diamond[i].x && x < diamond[i].x+diamond[i].w) && (y >= diamond[i].y && y < diamond[i].y+diamond[i].h))
                {
                    map[x][y][0] = 3;
                    
                    room = true;
                    break;
                }
            }
        }
    }
    /* Массив пространств изумрудов */
    SDL_Rect *emerald = new SDL_Rect[room_count*2];
    
    for(int i = 0; i < room_count*2; i++)
    {
        room_x = rand()%(map_width-1-1)+1;
        room_y = rand()%(map_width-1-1)+1;
        room_width = rand()%(1 - 3) + 1;
        room_height = rand()%(1 - 2) + 1;

        if(room_x + room_width >= map_width)
        {
            i--;
            continue;
        }
        if(room_y + room_height >= map_height)
        {
            i--;
            continue;
        }
        emerald[i] = {room_x, room_y, room_width, room_height};
    }

    /* Создание пространств изумрудов */
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            bool room = false;
            for(int i = 0; i < room_count*2; i++)
            {
                if((x >= emerald[i].x && x < emerald[i].x+emerald[i].w) && (y >= emerald[i].y && y < emerald[i].y+emerald[i].h))
                {
                    map[x][y][0] = 4;
                    
                    room = true;
                    break;
                }
            }
        }
    }
    /* Массив пустых пространств */
    SDL_Rect *rooms = new SDL_Rect[room_count];
    
    for(int i = 0; i < room_count; i++)
    {
        do
        {
            room_x = rand()%(map_width-1-1)+1;
            room_y = rand()%(map_width-1-1)+1;
            room_width = rand()%(room_maxW - room_minW) + room_minW;
            room_height = rand()%(room_maxH - room_minH) + room_minH;

            if(room_x + room_width >= map_width)
            {
                rooms[i] = {0, 0, 0, 0};
            }
            else if(room_y + room_height >= map_height)
            {
                rooms[i] = {0, 0, 0, 0};
            }
            else rooms[i] = {room_x, room_y, room_width, room_height};
        }
        while(intersection(rooms, i));
    }
    SDL_Rect center = rooms[rand()%(room_count)];

    /* Создание пустых пространств */
    for(int y = 0; y < map_height; y++)
    {
        for(int x = 0; x < map_width; x++)
        {
            bool room = false;
            for(int i = 0; i < room_count; i++)
            {
                if((x >= rooms[i].x && x < rooms[i].x+rooms[i].w) && (y >= rooms[i].y && y < rooms[i].y+rooms[i].h))
                {
                    map[x][y][0] = 0;
                    
                    room = true;
                    break;
                }
            }
            if(!room)
            {
                if(map[x][y][0] == 0) map[x][y][0] = 1;
            }
        }
    }
    /* Массив пространств которые имеют корридоры */
    SDL_Rect *corridor = new SDL_Rect[room_count];
    int corridor_count = 0;
    for(int i = 0; i < room_count; i++)
    {
        if(rand()%2) corridor[corridor_count++] = rooms[i];
        if(rand()%2) map[rooms[i].x][rooms[i].y][1] = rand()%3+1;
    }

    /* Генерация туннелей */
    for(int i = 0; i < corridor_count; i++)
    {
        int miner_x = corridor[i].x;
        int miner_y = corridor[i].y;
        int side = 4;
        int shaft_rotates = rand()%(14-6)+6;
        bool mining = false;
        
        for(int j = 0; j < shaft_rotates; j++)
        {
            int shaft_len;
            bool correct;
            do
            {
                shaft_len = rand()%(8-3)+3; // Длина пролёта
                int new_side = rand()%4;    //  0 - верх, 1 - лево, 2 - низ, 3 - право

                // if(side != 4 && (side == new_side)) correct = false;
                if(new_side == 0 && (miner_y-shaft_len <= 0)) correct = false;
                else if(new_side == 1 && (miner_x-shaft_len <= 0)) correct = false;
                else if(new_side == 2 && (miner_y+shaft_len >= map_height-1)) correct = false;
                else if(new_side == 3 && (miner_x+shaft_len >= map_width-1)) correct = false;
                else
                {
                    side = new_side;
                    correct = true;
                }
            }
            while(!correct);

            for(int go = 0; go < shaft_len; go++)
            {
                if(!mining && (bool(map[miner_x][miner_y-1][0]) + bool(map[miner_x-1][miner_y][0]) + bool(map[miner_x][miner_y+1][0]) + bool(map[miner_x+1][miner_y][0])) == 1)
                {
                    mining = true;
                }
                else if(mining && (bool(map[miner_x][miner_y-1][0]) + bool(map[miner_x-1][miner_y][0]) + bool(map[miner_x][miner_y+1][0]) + bool(map[miner_x+1][miner_y][0])) < 2)
                {
                    map[miner_x][miner_y][1] = rand()%3+1;
                    break;
                }
                if(side == 0) map[miner_x][--miner_y][0] = 0;
                else if(side == 1) map[--miner_x][miner_y][0] = 0;
                else if(side == 2) map[miner_x][++miner_y][0] = 0;
                else if(side == 3) map[++miner_x][miner_y][0] = 0;
            }
            if(mining && (bool(map[miner_x][miner_y-1][0]) + bool(map[miner_x-1][miner_y][0]) + bool(map[miner_x][miner_y+1][0]) + bool(map[miner_x+1][miner_y][0])) < 2)
            {
                if(rand()%3) i--;
                break;
            }
        }
    }

    /* Размещение лифта и игрока и генератора */
    map[center.x][center.y][0] = 5;
    map[center.x][center.y][1] = 0;
    map[center.x][center.y+1][1] = 0;
    map[center.x+1][center.y][1] = 5;

    delete[] rooms;
    delete[] gold;
    delete[] corridor;
    rooms = nullptr;
    gold = nullptr;
    corridor = nullptr;
    
    /*/* Вывод в консоль для отладки #1#
    for(int n = 0; n < map_height; n++)
    {
        for(int m = 0; m < map_width; m++)
            cout << map[m][n][0];
        cout << endl;
    }
    cout << endl;*/

    /* Вывод стен в файл для отладки */
    for(int n = 0; n < map_height; n++)
    {
        for(int m = 0; m < map_width; m++)
            walllayer << map[m][n][0];
        walllayer << endl;
    }
    walllayer << endl;
    
    /* Вывод объектов в файл для отладки */
    for(int n = 0; n < map_height; n++)
    {
        for(int m = 0; m < map_width; m++)
            objectlayer << map[m][n][1];
        objectlayer << endl;
    }
    objectlayer << endl;
    
    groundlayer.close();
    walllayer.close();
    objectlayer.close();
    gaslayer.close();
    // /* Запись стен в структуру */
    // for(int n = 0; n < map_height; n++)
    //     for(int m = 0; m < map_width; m++)
    //         if(map[m][n][0]) createWall(wallList, m, n, map[m][n][0]);
    // /* Запись объектов в структуру */
    // for(int n = 0; n < map_height; n++)
    //     for(int m = 0; m < map_width; m++)
    //         if(map[m][n][1]) createGameObject(gameObjectList, m, n, map[m][n][1]);

    /* Удаление карты */
    // //Удаление третьего измерения
    // for(int i = 0; i < map_width; i++)
    //     for(int j = 0; j < map_height; j++)
    //         delete [] map[i][j];
    // //Удаление второго измерения
    // for(int i = 0; i < map_width; i++)
    //     delete [] map[i];
    // //Удаление массива
    // delete [] map;
    // map = nullptr;
    // return {center.x, center.y+1, getTexture("new_player.png"), 100};
    *player = {center.x, center.y+1, getTexture("playerD.png")};
}

/* Загрузка игровых текстур */