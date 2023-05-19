#ifndef BaseObject_h
#define BaseObject_h

#include "CommonFunction.h"

class BaseObject{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x, const int& y)
    {
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Rect getRect()   const
    {
        return rect_;
    }
    SDL_Texture* GetObject()
    {
        return p_object;
    }
    virtual bool LoadImage(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void free();
protected:
    SDL_Texture* p_object;
    SDL_Rect rect_;
};
#endif // BaseObject_h
