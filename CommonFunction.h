#ifndef CommonFunction_h
#define CommonFunction_h

#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <fstream>
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_renderer = NULL;
static SDL_Event e;

const int FRAME_PER_SECOND = 25;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 168;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

#define STATE_SPIKE 5
enum GameStates
{
    PLAYING = 0,
    GAMEOVER = 1,
};

typedef struct Input
{
    int left;
    int right;
    int up;
    int down;
    int jump;
};

typedef struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;

};

namespace SDLCommonFunction
{
    bool CheckCollision(const SDL_Rect a, const SDL_Rect b);
}
#endif // CommonFunction_h
