#pragma once

#include"Entity.h"
#include"RenderWindow.h"
#include<vector>


class Landmine  : public Entity
{
    public:

    Landmine(Vector2f p_pos ,  SDL_Texture* p_tex);

    private:
};


static SDL_Rect exploClips[ 6 ];
void setExploClip(SDL_Rect exploClips[] );

