#include "CommonFunction.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "Timer.h"
#include "BulletObject.h"


BaseObject g_background;

bool init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_renderer == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
            int ImgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(ImgFlags) & ImgFlags))
                success = false;
        }
    }

    return success;
}

bool LoadBackground()
{
    bool ret = g_background.LoadImage("E:/SDL/testSDL/game2SDL/Image/bluemoon.png", g_renderer);
    if(ret == false)
        return false;

    return true;
}

void close()
{
    g_background.free();

    SDL_DestroyRenderer(g_renderer);
    g_renderer = NULL;
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char** args)
{
    Timer timer;

    if(init() == false)
        return -1;
    if(LoadBackground() == false)
        return -1;

    GameMap game_map;
    game_map.LoadMap("E:/SDL/testSDL/game2SDL/Map/gamemap.txt");
    game_map.LoadTiles(g_renderer);

    MainObject player;
    player.LoadImage("E:/SDL/testSDL/game2SDL/Image/newrun.png", g_renderer);
    player.set_clips();

    int num_die = 0;
    int gamestate = 0;

    bool is_quit = false;
    while(!is_quit)
    {
        timer.start();
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                is_quit = true;
            }
            player.HandleEvent(e, g_renderer);
        }

        SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
        SDL_RenderClear(g_renderer);
        if(gamestate == GameStates::PLAYING){
        g_background.Render(g_renderer, NULL);

        Map map_data = game_map.getMap();


        player.SetMap(map_data.start_x, map_data.start_y);
        player.DoPlayer(map_data);
        player.Show(g_renderer);

        game_map.setMap(map_data);
        game_map.DrawMap(g_renderer);
        SDL_Rect rect_player = player.GetRectFrame();
        }
        else if(gamestate == GameStates::GAMEOVER)
        {
            SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        }
        SDL_RenderPresent(g_renderer);

        num_die++;
        if(num_die <= 3)
        {
            player.SetRect(0, 0);
            player.set_comeback_time(60);
            SDL_Delay(1000);
            continue;
        }

        int real_time = timer.getTicks();
        int time_per_frame = 1000 / FRAME_PER_SECOND;
        if(real_time < time_per_frame)
        {
            int delay = time_per_frame - real_time;
            if(delay >= 0){
            SDL_Delay(delay);
            }
        }
    }
    close();
    return 0;
}
