#include <string>
#include <SDL.h>
#include <SDL_mixer.h>

#include "fstream"
#include "header.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Главное меню игры */
void checkMainMenu()
{
    Button *pressed_button = NULL;
    while(!quit)
    {
        if(SDL_PollEvent(&event))
        {
            pressed_button = userInput();
            if(pressed_button != NULL)
            {
                if(pressed_button->object_info->name == "NewGameButton")
                {
                    scene = "New Game Menu";
                    quit = true;
                }
                /*else if(pressed_button->object_info->name == "LoadGameButton")
                {
                    scene = "Load Game Menu";
                    quit = true;
                }*/
                /*else if(pressed_button->object_info->name == "MultiplayerButton")
                {
                    scene = "Multiplayer Menu";
                    quit = true;
                }*/
                else if(pressed_button->object_info->name == "SettingsButton")
                {
                    scene = "Settings Menu";
                    quit = true;
                }
                else if(pressed_button->object_info->name == "QuitButton")
                {
                    scene = "Escape";
                    quit = true;
                }
            }
        }
        SDL_Delay(1);
    }
}
/* Инициализация главного меню игры */
void loadMainMenu()
{
    createGUIObject("BackgroundImage", {0,0}, imageGenerator("main_menu_background.png"), "left", 5.3);
    createGUIObject("GameLogo", {640,50}, {"MINER GAME", "font.ttf", 128, "center", black});
    createGUIObject("Records", {1230,360}, {"Рекорды", "font.ttf", 64, "right", black});
    createButton("NewGameButton", {50,360}, {"Новая игра", "font.ttf", 64, "left", black});
    createButton("LoadGameButton", {50,360+66*1}, {"Загрузить игру", "font.ttf", 64, "left", black});
    createButton("MultiplayerButton", {50,360+66*2}, {"Мультиплеер", "font.ttf", 64, "left", black});
    createButton("SettingsButton", {50,360+66*3}, {"Настройки", "font.ttf", 64, "left", black});
    createButton("QuitButton", {50,360+66*4}, {"Выйти из игры", "font.ttf", 64, "left", black});
    
    updateFrame();

    checkMainMenu();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Меню Настроек игры */
void checkSettingsMenu()
{
    Button *pressed_button = NULL;
    while(!quit)
    {
        if(SDL_PollEvent(&event))
        {
            pressed_button = userInput();
            if(pressed_button != NULL)
            {
                /*else if(pressed_button->object_info->name == "ScreenResolutionButton")
                {
                    
                }*/
                if(pressed_button->object_info->name == "FullscreenModeButton")
                {
                    if(FULLSCREEN_MODE == false)
                    {
                        FULLSCREEN_MODE = true;
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN || SDL_WINDOW_BORDERLESS);
                    }
                    else
                    {
                        FULLSCREEN_MODE = false;
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
                    }
                    pressed_button->object_info->text_info->text = "> " + to_string(FULLSCREEN_MODE);
                    updateGUIObject(pressed_button->object_info);
                    quit = true;
                }
                else if(pressed_button->object_info->name == "VSyncButton")
                {
                    if(VSYNC == false)
                    {
                        VSYNC = true;
                        SDL_DestroyRenderer(renderer);
                        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
                    }
                    else
                    {
                        VSYNC = false;
                        SDL_DestroyRenderer(renderer);
                        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                    }
                    if(FULLSCREEN_MODE)
                    {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN);
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN || SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                
                    pressed_button->object_info->text_info->text = "> " + to_string(VSYNC);
                    updateGUIObject(pressed_button->object_info);
                    quit = true;
                }
                /*else if(pressed_button->object_info->name == "MasterVolumeButton")
                {
                    
                }*/
                /*else if(pressed_button->object_info->name == "MusicVolumeButton")
                {
                    
                }*/
                else if(pressed_button->object_info->name == "ApplyButton")
                {
                    ofstream settings("data/settings.txt", ios::out);
                    settings.clear();
                    settings
                    << "SCREEN_WIDTH " + to_string(SCREEN_WIDTH) << endl
                    << "SCREEN_HEIGHT " + to_string(SCREEN_HEIGHT) << endl
                    << "VSYNC " + to_string(VSYNC) << endl
                    << "MASTER_VOLUME " + to_string(MASTER_VOLUME) << endl
                    << "MUSIC_VOLUME " + to_string(MUSIC_VOLUME) << endl
                    << "FULLSCREEN_MODE " + to_string(FULLSCREEN_MODE);
                    settings.close();
                }
                else if(pressed_button->object_info->name == "ReturnButton")
                {
                    initSettings();
                    scene = "Main Menu";
                    quit = true;
                }
            }
        }
        SDL_Delay(1);
    }
}
/* Инициализация Меню Настроек игры */
void loadSettingsMenu()
{
    createGUIObject("BackgroundImage", {0,0}, imageGenerator("main_menu_background.png"), "left", 5.3);
    createGUIObject("SettingsLogo", {160,60}, {"Настройки", "font.ttf", 64, "left"});
    createGUIObject("ScreenResolution", {160,60+34*2}, {"Разрешение экрана", "font.ttf", 32, "left"});
    createButton("ScreenResolutionButton", {1120,60+34*2}, {to_string(SCREEN_WIDTH)+"x"+to_string(SCREEN_HEIGHT), "font.ttf", 32, "right"});
    createGUIObject("FullscreenMode", {160,60+34*3}, {"Полноэкранный режим", "font.ttf", 32, "left"});
    createButton("FullscreenModeButton", {1120,60+34*3}, {to_string(FULLSCREEN_MODE), "font.ttf", 32, "right"});
    createGUIObject("VSync", {160,60+34*4}, {"VSync", "font.ttf", 32, "left"});
    createButton("VSyncButton", {1120,60+34*4}, {to_string(VSYNC), "font.ttf", 32, "right"});
    createGUIObject("MasterVolume", {160,60+34*5}, {"Громкость игры", "font.ttf", 32, "left"});
    createButton("MasterVolumeButton", {1120,60+34*5}, {to_string(MASTER_VOLUME), "font.ttf", 32, "right"});
    createGUIObject("MusicVolume", {160,60+34*6}, {"Громкость музыки", "font.ttf", 32, "left"});
    createButton("MusicVolumeButton", {1120,60+34*6}, {to_string(MUSIC_VOLUME), "font.ttf", 32, "right"});
    createButton("ApplyButton", {1120,60+34*8}, {"Применить", "font.ttf", 48, "right"});
    createButton("ReturnButton", {160,60+34*8}, {"Вернуться", "font.ttf", 48, "left"});
    
    updateFrame();

    checkSettingsMenu();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Меню Новой игры */
void checkNewGameMenu()
{
    Button *pressed_button = NULL;
    while(!quit)
    {
        if(SDL_PollEvent(&event))
        {
            pressed_button = userInput();
            if(pressed_button != NULL)
            {
                if(pressed_button->object_info->name == "Mode1")
                {
                    scene = "Game";
                    map_width = 100;
                    map_height = 100;
                    quit = true;
                }
                /*else if(pressed_button->object_info->name == "Mode2")
                {
                    scene = "";
                    quit = true;
                }*/
                /*else if(pressed_button->object_info->name == "Mode3")
                {
                    scene = "";
                    quit = true;
                }*/
                else if(pressed_button->object_info->name == "ReturnButton")
                {
                    scene = "Main Menu";
                    quit = true;
                }
            }
        }
        SDL_Delay(1);
    }
}
/* Инициализация Меню Новой игры */
void loadNewGameMenu()
{
    createGUIObject("BackgroundImage", {0,0}, imageGenerator("main_menu_background.png"), "left", 5.3);
    createGUIObject("SelectDifficulty", {640,150}, {"Выберите сложность", "font.ttf", 64, "center", black});
    createButton("Mode1", {160,500}, {"Лёгкая", "font.ttf", 64, "left", black});
    createGUIObject("Mode1Image", {160,250}, imageGenerator("diamond_rock.png"), "left", 6);
    createButton("Mode2", {640,500}, {"Средняя", "font.ttf", 64, "center", black});
    createGUIObject("Mode2Image", {640,250}, imageGenerator("gold_rock.png"), "center", 6);
    createButton("Mode3", {1120,500}, {"Хардкор", "font.ttf", 64, "right", black});
    createGUIObject("Mode3Image", {1120,250}, imageGenerator("rock.png"), "right", 6);
    createButton("ReturnButton", {160,600}, {"Вернуться", "font.ttf", 64, "left", black});
    
    updateFrame();

    checkNewGameMenu();
}

void checkGame(Player *player, int ***map)
{
    unsigned short cooldown = 0;
    Button *pressed_button = NULL;
    
    createGUIObject("Mine Selection", {0, 0, 0, 0}, getTexture("mine_selection.png")->texture);
    GUIObject *mine_selection = getGUIObject("Mine Selection");
    mine_selection->rect = {0,0,0,0};
    
    while(!quit)
    {
        
        if(cooldown)
            if(time(NULL)-5 >= cooldown) cooldown = 0;
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                /* Система копания */
                /* Система собирания предметов */
                // Верхний тайл
                if((event.button.x >= 640-40 && event.button.x < 640+40) &&
                    (event.button.y >= 360-40-80 && event.button.y < 360-40))
                {
                    int wallUp = map[player->x][player->y-1][0];
                    int objectUp = map[player->x][player->y-1][1];
                    // Копание верхнего тайла
                    if(wallUp)
                    {
                        player->texture = getTexture("playerU.png");
                        if(wallUp != 5)
                        {
                            if(wallUp == 1) player->stamina -= 3;
                            else if(wallUp == 2) updateGUIObject("Gold Counter", textGenerator({to_string(++player->gold), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallUp == 3) updateGUIObject("Diamond Counter", textGenerator({to_string(++player->diamond), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallUp == 4) updateGUIObject("Emerald Counter", textGenerator({to_string(++player->emerald), "font.ttf", 64,  "left", {0,0,0}}));
                            player->stamina -= 2;
                            map[player->x][player->y-1][0] = 0;
                        }
                        else
                        {
                            // Магазин
                        }
                        updateFrame(player, map);
                    }
                    // Собирание предмета верхнего тайла
                    else if(objectUp)
                    {
                        if(checkInventory(player))
                        {
                            player->texture = getTexture("playerU.png");
                            addInventory(player, objectUp);
                            map[player->x][player->y-1][1] = 0;
                            updateFrame(player, map);
                        }
                    }
                }
                // Левый тайл
                else if((event.button.x >= 640-40-80 && event.button.x < 640-40) &&
                    (event.button.y >= 360-40 && event.button.y < 360+40))
                {
                    int wallLeft = map[player->x-1][player->y][0];
                    int objectLeft = map[player->x-1][player->y][1];
                    // Копание левого тайла
                    if(wallLeft)
                    {
                        player->texture = getTexture("playerL.png");
                        if(wallLeft != 5)
                        {
                            if(wallLeft == 1) player->stamina -= 3;
                            else if(wallLeft == 2) updateGUIObject("Gold Counter", textGenerator({to_string(++player->gold), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallLeft == 3) updateGUIObject("Diamond Counter", textGenerator({to_string(++player->diamond), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallLeft == 4) updateGUIObject("Emerald Counter", textGenerator({to_string(++player->emerald), "font.ttf", 64,  "left", {0,0,0}}));
                            player->stamina -= 2;
                            map[player->x-1][player->y][0] = 0;
                        }
                        else
                        {
                            // Магазин
                        }
                        updateFrame(player, map);
                    }
                    // Собирание предмета левого тайла
                    else if(objectLeft)
                    {
                        if(checkInventory(player))
                        {
                            player->texture = getTexture("playerL.png");
                            addInventory(player, objectLeft);
                            map[player->x-1][player->y][1] = 0;
                            updateFrame(player, map);
                        }
                    }
                }
                // Нижний тайл
                else if((event.button.x >= 640-40 && event.button.x < 640+40) &&
                    (event.button.y >= 360+40 && event.button.y < 360+40+80))
                {
                    int wallDown = map[player->x][player->y+1][0];
                    int objectDown = map[player->x][player->y+1][1];
                    // Копание нижнего тайла
                    if(wallDown)
                    {
                        player->texture = getTexture("playerD.png");
                        if(wallDown != 5)
                        {
                            if(wallDown == 1) player->stamina -= 3;
                            else if(wallDown == 2) updateGUIObject("Gold Counter", textGenerator({to_string(++player->gold), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallDown == 3) updateGUIObject("Diamond Counter", textGenerator({to_string(++player->diamond), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallDown == 4) updateGUIObject("Emerald Counter", textGenerator({to_string(++player->emerald), "font.ttf", 64,  "left", {0,0,0}}));
                            player->stamina -= 2;
                            map[player->x][player->y+1][0] = 0;
                        }
                        else
                        {
                            // Магазин
                        }
                        updateFrame(player, map);
                    }
                    // Собирание предмета нижнего тайла
                    else if(objectDown)
                    {
                        if(checkInventory(player))
                        {
                            player->texture = getTexture("playerD.png");
                            addInventory(player, objectDown);
                            map[player->x][player->y+1][1] = 0;
                            updateFrame(player, map);
                        }
                    }
                }
                // Правый тайл
                else if((event.button.x >= 640+40 && event.button.x < 640+40+80) &&
                    (event.button.y >= 360-40 && event.button.y < 360+40))
                {
                    int wallRight = map[player->x+1][player->y][0];
                    int objectRight = map[player->x+1][player->y][1];
                    // Копание правого тайла
                    if(wallRight)
                    {
                        player->texture = getTexture("playerR.png");
                        if(wallRight != 5)
                        {
                            if(wallRight == 1) player->stamina -= 3;
                            else if(wallRight == 2) updateGUIObject("Gold Counter", textGenerator({to_string(++player->gold), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallRight == 3) updateGUIObject("Diamond Counter", textGenerator({to_string(++player->diamond), "font.ttf", 64,  "left", {0,0,0}}));
                            else if(wallRight == 4) updateGUIObject("Emerald Counter", textGenerator({to_string(++player->emerald), "font.ttf", 64,  "left", {0,0,0}}));
                            player->stamina -= 2;
                            map[player->x+1][player->y][0] = 0;
                        }
                        else
                        {
                            // Магазин
                        }
                        updateFrame(player, map);
                    }
                    // Собирание предмета правого тайла
                    else if(objectRight)
                    {
                        if(checkInventory(player))
                        {
                            player->texture = getTexture("playerR.png");
                            addInventory(player, objectRight);
                            map[player->x+1][player->y][1] = 0;
                            updateFrame(player, map);
                        }
                    }
                }
            }
            /* Система перемещения игрока */
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
            {
                if(!map[player->x][player->y-1][0] || map[player->x][player->y-1][0] == 5)
                {
                    player->texture = getTexture("playerU.png");
                    player->y--;
                    player->stamina -= 1;
                    updateFrame(player, map);
                }
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
            {
                if(!map[player->x-1][player->y][0] || map[player->x-1][player->y][0] == 5)
                {
                    player->texture = getTexture("playerL.png");
                    player->x--;
                    player->stamina -= 1;
                    updateFrame(player, map);
                }
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
            {
                if(!map[player->x][player->y+1][0] || map[player->x][player->y+1][0] == 5)
                {
                    player->texture = getTexture("playerD.png");
                    player->y++;
                    player->stamina -= 1;
                    updateFrame(player, map);
                }
            }
            else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
            {
                if(!map[player->x+1][player->y][0] || map[player->x+1][player->y][0] == 5)
                {
                    player->texture = getTexture("playerR.png");
                    player->x++;
                    player->stamina -= 1;
                    updateFrame(player, map);
                }
            }
        //     /* Система выделения копания */
        //     if((event.button.x >= 640-40 && event.button.x < 640+40) &&
        //         (event.button.y >= 360-40-80 && event.button.y < 360-40))
        //     {
        //         if((event.button.x < mine_selection->rect.x || event.button.x >= mine_selection->rect.x+80) ||
        //            event.button.y < mine_selection->rect.y || event.button.y >= mine_selection->rect.y+80)
        //         {
        //             if(map[player->x][player->y-1][0])
        //             {
        //                 mine_selection->rect = {640-40, 360-40-80, 80, 80};
        //                 updateFrame(player, map);
        //             }
        //         }
        //     }
        //     else if((event.button.x >= 640-40-80 && event.button.x < 640-40) &&
        //             (event.button.y >= 360-40 && event.button.y < 360+40))
        //     {
        //         if((event.button.x < mine_selection->rect.x || event.button.x >= mine_selection->rect.x+80) ||
        //            event.button.y < mine_selection->rect.y || event.button.y >= mine_selection->rect.y+80)
        //         {
        //             if(map[player->x-1][player->y][0])
        //             {
        //                 mine_selection->rect = {640-40-80, 360-40, 80, 80};
        //                 updateFrame(player, map);
        //             }
        //         }
        //     }
        //     else if((event.button.x >= 640-40 && event.button.x < 640+40) &&
        //             (event.button.y >= 360+40 && event.button.y < 360+40+80))
        //     {
        //         if((event.button.x < mine_selection->rect.x || event.button.x >= mine_selection->rect.x+80) ||
        //            event.button.y < mine_selection->rect.y || event.button.y >= mine_selection->rect.y+80)
        //         {
        //             if(map[player->x][player->y+1][0])
        //             {
        //                 mine_selection->rect = {640-40, 360+40, 80, 80};
        //                 updateFrame(player, map);
        //             }
        //         }
        //     }
        //     else if((event.button.x >= 640+40 && event.button.x < 640+40+80) &&
        //             (event.button.y >= 360-40 && event.button.y < 360+40))
        //     {
        //         if((event.button.x < mine_selection->rect.x || event.button.x >= mine_selection->rect.x+80) ||
        //            event.button.y < mine_selection->rect.y || event.button.y >= mine_selection->rect.y+80)
        //         {
        //             if(map[player->x+1][player->y][0])
        //             {
        //                 mine_selection->rect = {640+40, 360-40, 80, 80};
        //                 updateFrame(player, map);
        //             }
        //         }
        //     }
        //     else if(mine_selection->rect.w != 0)
        //     {
        //         mine_selection->rect = {0,0,0,0};
        //         updateFrame(player, map);
        //     }
        }
        if(player->stamina <= 0)
        {
            scene = "Main Menu";
            quit = true;
        }
        pressed_button = userInput();
        if(pressed_button != NULL)
        {
            // if(pressed_button->object_info->name == "ReturnButton")
            // {
            //     scene = "Main Menu";
            //     quit = true;
            // }
        }
        SDL_Delay(1);
    }
}

void loadGame()
{
    Player player;
    int ***map = new int**[map_width]{0};
    for(int i = 0; i < map_width; i++)
    {
        map[i] = new int*[map_height]{0};
        for(int j = 0; j < map_height; j++)
            map[i][j] = new int[2]{0};
    }
    // Загрузка текстуры земли
    loadTexture("ground.png");
    // Загрузка текстуры камня
    loadTexture("rock.png");
    loadTexture("rockD.png");
    loadTexture("rockDR.png");
    loadTexture("rockL.png");
    loadTexture("rockLD.png");
    loadTexture("rockLDR.png");
    loadTexture("rockLR.png");
    loadTexture("rockR.png");
    loadTexture("rockU.png");
    loadTexture("rockUD.png");
    loadTexture("rockUDR.png");
    loadTexture("rockUL.png");
    loadTexture("rockULD.png");
    loadTexture("rockULDR.png");
    loadTexture("rockULR.png");
    loadTexture("rockUR.png");
    // Загрузка лифта
    loadTexture("elevator.png");
    // Загрузка руд
    loadTexture("gold.png");
    loadTexture("diamond.png");
    loadTexture("emerald.png");
    // Загрузка игрока
    loadTexture("playerU.png");
    loadTexture("playerL.png");
    loadTexture("playerD.png");
    loadTexture("playerR.png");
    // Загрузка предметов
    loadTexture("generator.png");
    loadTexture("item_gold.png");
    loadTexture("2.png");
    loadTexture("3.png");
    // Загрузка выделения
    loadTexture("mine_selection.png");
    // Загрузка интерфейса
    loadTexture("stamina_bar.png");
    loadTexture("health_bar.png");
    loadTexture("gold_ingot.png");
    loadTexture("diamond_ingot.png");
    loadTexture("emerald_ingot.png");
    createGUIObject("Gold Counter", {110, 80, 0, 0}, textGenerator({to_string(player.gold), "font.ttf", 64, "left", {0,0,0}}));
    createGUIObject("Diamond Counter", {110, 144, 0, 0}, textGenerator({to_string(player.diamond), "font.ttf", 64, "left", {0,0,0}}));
    createGUIObject("Emerald Counter", {110, 208, 0, 0}, textGenerator({to_string(player.emerald), "font.ttf", 64, "left", {0,0,0}}));
    loadTexture("gas_mask.png");
    loadTexture("gas_mask_bar.png");
    loadTexture("yes.png");
    loadTexture("no.png");
    loadTexture("inventory_slot.png");
    loadTexture("Hint", textGenerator({"Нажмите E, чтобы войти в лифт", "font.ttf", 40, "center", {0,0,0}}));
    
    initMap(&player, map);
    
    updateFrame(&player, map);
    
    checkGame(&player, map);
}

void checkPause()
{
    Button *pressed_button = NULL;
    while(!quit)
    {
        pressed_button = userInput();
        if(pressed_button != NULL)
        {
            // if(pressed_button->object_info->name == "ReturnButton")
            // {
            //     scene = "Main Menu";
            //     quit = true;
            // }
        }
        SDL_Delay(1);
    }
}

void loadPause()
{
    updateFrame();
    checkPause();
}