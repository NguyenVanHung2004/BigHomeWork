#pragma once
#include"Entity.h"
#include"Soilder.h"
#include"RenderWindow.h"
#include"Landmine.h"

#include<vector>
#include <fstream>

class Tank : public Soilder
{
    public:
        Tank( Vector2f p_pos, SDL_Texture* p_tex );
        void set_heal( int p_heal );
        int get_heal();
        void updateTank(std::vector<Landmine> landmines,int &heal_point ,int max_heal , int &enemiesRemain , double deltaTime ,Mix_Chunk* explosion, Mix_Chunk* tankSound );
        bool getDamage();
        void setDamage( bool p_damage);
    private:
        int heal  ;
        bool damage = false;
};


static SDL_Rect tankClips[ 8 ];
void setTankClip(SDL_Rect tankClips[] );

std::vector<Tank> loadTanks(int level, SDL_Texture* tex );
