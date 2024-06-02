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
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_SHOWN || SDL_WINDOW_BORDERLESS);
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
        pressed_button = userInput();
        if(pressed_button != NULL)
        {
            /*else if(pressed_button->object_info->name == "Mode1")
            {
                scene = "";
                quit = true;
            }*/
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
            if(pressed_button->object_info->name == "ReturnButton")
            {
                scene = "Main Menu";
                quit = true;
            }
        }
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

void checkGame()
{
    Button *pressed_button = NULL;
    while(!quit)
    {
        pressed_button = userInput();
        if(pressed_button != NULL)
        {
            if(pressed_button->object_info->name == "ReturnButton")
            {
                scene = "Main Menu";
                quit = true;
            }
        }
    }
}

void loadGame()
{
}