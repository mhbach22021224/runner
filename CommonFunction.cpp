#include "CommonFunction.h"

bool SDLCommonFunction::CheckCollision(const SDL_Rect a, const SDL_Rect b)
{
    bool ret = SDL_HasIntersection(&a, &b);
    if(ret == true)
    {
        return true;
    }
    else return false;
}
