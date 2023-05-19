#ifndef MainObject_h
#define MainObject_h

#include "CommonFunction.h"
#include "BaseObject.h"

#include "GameMap.h"
#include <vector>

#define JUMP_SPEED 10
#define GRAVITY_SPEED 0.5
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 20

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };
    bool LoadImage(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleEvent(SDL_Event e, SDL_Renderer* screen);
    void set_clips();
    void DoPlayer(Map& map_data);
    void CheckMap(Map& map_data);
    SDL_Rect GetRectFrame();
    void SetMap(const int map_x_, const int map_y_)
    {
        map_x = map_x_;
        map_y = map_y_;
    }
    void CenterEntityOnMap(Map& map_data);

    void set_comeback_time(const int& cb_time)
    {
        come_back_time = cb_time;
    }
private:


    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[9];
    Input input_type;
    int frame;
    int status;

    bool on_ground;
    int map_x;
    int map_y;

    int gamestate;
    int come_back_time;
};
#endif // MainObject_h
