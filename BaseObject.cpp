#include "BaseObject.h"
#include "CommonFunction.h"

BaseObject::BaseObject()
{
    p_object = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{

}

bool BaseObject::LoadImage(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface != NULL)
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if(newTexture != NULL)
        {
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    p_object = newTexture;

    return newTexture != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip)
{
    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object, clip, &renderQuad);
}

void BaseObject::free()
{
    if(p_object != NULL)
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
