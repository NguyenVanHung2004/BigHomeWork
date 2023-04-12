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
    bool unlock = false;
    int index;
   private:
    Vector2f pos;
    };

std::vector<Level> loadLevelSelect();
