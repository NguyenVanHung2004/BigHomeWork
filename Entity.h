#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>

struct Vector2f
{
    Vector2f(float p_x, float p_y) : x(p_x) , y(p_y)
    {

    }
    Vector2f():x(0.0f), y(0.0f)
    {

    }
    float x;
    float y;

};
class Entity
{
    public:
        Entity( Vector2f p_pos ,SDL_Texture* p_tex );
        Vector2f& getPos()
        {
            return pos;
        }

        SDL_Rect getCurrentFrame();
        void setPos(float x, float y);
        void setVelocity (float x, float y);
        Vector2f setVelocity();
        Vector2f getVelocity();
        SDL_Texture* getTex();

    private:
        Vector2f pos;
        SDL_Rect currentFrame;
        SDL_Texture* tex;

};
