#pragma once
#include <SDL.h>
#include<vector>
#include"Entity.h"
class Level
{
   public:
        Level(Vector2f p_pos , int index);
        Vector2f getPos();
        bool onclick =false;
        int index;
        void setUnlock (bool p_unlock);
        bool getUnlock ();

   private:
        Vector2f pos;
        bool unlock = false ;
    };

std::vector<Level> loadLevelSelect();
