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
std:: vector<Landmine>  loadLandMine( SDL_Texture* tex, int num_mine );

