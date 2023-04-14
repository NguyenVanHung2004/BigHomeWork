#include"Landmine.h"

Landmine::Landmine(Vector2f p_pos ,SDL_Texture* p_tex) :  Entity(p_pos, p_tex)
{

}


std:: vector<Landmine>  loadLandMine( SDL_Texture* tex , int num_mine)
{

    std:: vector<Landmine> temp;
    for (int i = 0 ; i < num_mine ; i ++)
        temp.push_back( Landmine(Vector2f(-200, -200), tex));
    return temp;
}


