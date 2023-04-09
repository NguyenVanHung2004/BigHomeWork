
#pragma once
#include"Entity.h"
#include"Tank.h"
#include"RenderWindow.h"
#include"Landmine.h"

#include<vector>
#include <fstream>


class ArmoredCar : public Tank
{
    public:
     ArmoredCar( Vector2f p_pos, SDL_Texture* p_tex );



};

// load
std::vector<ArmoredCar> loadAmouredCar ( int level, SDL_Texture* tex );

static SDL_Rect amouredCarClips[ 8 ];
void setAmouredCarClip (SDL_Rect amouredCarClips[] );



