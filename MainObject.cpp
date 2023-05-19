#include "MainObject.h"

MainObject::MainObject()
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = -1;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.up = 0;
    input_type.down = 0;
    on_ground = false;
    map_x = 0;
    map_y = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImage(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImage(path, screen);

    if(ret == true)
    {
        width_frame = rect_.w / 5;
        height_frame = rect_.h / 2;
    }

    return ret;
}

void MainObject::set_clips()
{
    if(width_frame > 0 && height_frame > 0)
    {

        frame_clip[0].x = width_frame;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame - 10;
        frame_clip[0].h = height_frame;

        frame_clip[1].x = 2* width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].w = width_frame - 10;
        frame_clip[1].h = height_frame;

        frame_clip[2].x = 3* width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].w = width_frame - 10;
        frame_clip[2].h = height_frame;

        frame_clip[3].x = 4* width_frame;
        frame_clip[3].y = 0;
        frame_clip[3].w = width_frame - 10;
        frame_clip[3].h = height_frame;

        frame_clip[4].x = 0;
        frame_clip[4].y = height_frame;
        frame_clip[4].w = width_frame - 10;
        frame_clip[4].h = 2* height_frame;

        frame_clip[5].x = width_frame;
        frame_clip[5].y = height_frame;
        frame_clip[5].w = width_frame - 10;
        frame_clip[5].h = 2* height_frame;

        frame_clip[6].x = 2* width_frame;
        frame_clip[6].y = height_frame;
        frame_clip[6].w = width_frame - 10;
        frame_clip[6].h = 2* height_frame;

        frame_clip[7].x = 3* width_frame;
        frame_clip[7].y = height_frame;
        frame_clip[7].w = width_frame - 10;
        frame_clip[7].h = 2* height_frame;

        frame_clip[8].x = 4* width_frame;
        frame_clip[8].y = height_frame;
        frame_clip[8].w = width_frame - 10;
        frame_clip[8].h = 2* height_frame;
    }
}

void MainObject::Show(SDL_Renderer* des)
{
    if(status == WALK_RIGHT)
    {
        LoadImage("E:/SDL/testSDL/game2SDL/Image/newrun.png", des);
    }
    if(input_type.left == 1 || input_type.right == 1)
    {
        ++frame;
    }
    else
    {
        frame = 0;
    }

    if(frame >= 8)
    {
        frame = 0;
    }

    rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;

    SDL_Rect* currentClip = &frame_clip[frame];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame, height_frame};

    SDL_RenderCopy(des, p_object, currentClip, &renderQuad);
}

void MainObject::HandleEvent(SDL_Event e, SDL_Renderer* screen)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
            status = WALK_RIGHT;
            input_type.right = 1;
            input_type.left = 0;
            input_type.jump = 0;
            if(on_ground == true)
            {
                LoadImage("E:/SDL/testSDL/game2SDL/Image/newrun.png", screen);
            }

            }
            break;

        case SDLK_UP:
            {
                input_type.jump = 1;

            }
            break;
        case SDLK_DOWN:
            {
                input_type.down = 1;
            }
            break;
       }

    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type.right = 0;
            }
        case SDLK_UP:
            {
                input_type.jump = 0;
            }
        }
    }
}


void MainObject::DoPlayer(Map& map_data)
{
    x_val = 0;
    y_val += 0.5;

    if(y_val >= MAX_FALL_SPEED)
    {
        y_val = MAX_FALL_SPEED;
    }

    if(input_type.left == 1)
    {
        x_val -= PLAYER_SPEED;
    }
    if(input_type.right == 1)
    {
        x_val += PLAYER_SPEED;
    }
    if(input_type.jump == 1)
    {
        if(on_ground == true)
        {
            y_val = - JUMP_SPEED;
        }
        input_type.jump = 0;
    }
    CheckMap(map_data);
    CenterEntityOnMap(map_data);
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos - (SCREEN_WIDTH / 2);
    if(map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
    if(map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

void MainObject::CheckMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

    x1 = (x_pos + x_val) / TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val > 0)
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if(val1 == STATE_SPIKE || val2 == STATE_SPIKE)
            {
                gamestate = GameStates::GAMEOVER;
            }
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos = x2* TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if(x_val < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos = (x1 + 1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }

    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min) / TILE_SIZE;

    y1 = (y_pos + x_val) / TILE_SIZE;
    y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val > 0)
        {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                y_pos = y2 * TILE_SIZE;
                y_pos -= height_frame + 1;
                y_val = 0;
                on_ground = true;
            }
        }
        else if(y_val < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
            {
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0)
    {
        x_pos = 0;
    }
    else if(x_pos + width_frame > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame - 1;
    }
    if(y_pos < 0)
    {
        y_pos = 0;
    }
    else if(y_pos + height_frame > map_data.max_y)
    {
        y_pos = map_data.max_y - height_frame - 1;
    }
}

SDL_Rect MainObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;
}
