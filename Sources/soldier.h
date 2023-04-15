#pragma once
#include"Entity.h"
#include"RenderWindow.h"
#include"Landmine.h"

#include<vector>
#include <fstream>



class Soldier : public Entity
{
    public:
        Soldier(Vector2f p_pos, SDL_Texture* p_tex);
        void setVelocity( float x, float y);
        Vector2f getVelocity();
        void update( std::vector<Landmine> landmines , int &heal_point, int &enemiesRemain , double deltaTime , Mix_Chunk* explosion);
        void setDeath( bool p_death) ;
        bool getDeath();
        bool animationDone = false;
        int tempFrame;

    private:
        Vector2f velocity{0.03,0};
        bool death =false ;

};


static SDL_Rect runClips[ 13 ];
void setSoldierClip(SDL_Rect runClips[] );
std::vector<Soldier> loadSoldiers(int level, SDL_Texture* tex );
