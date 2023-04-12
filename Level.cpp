
#include"Level.h"

Level::Level(Vector2f p_pos, int p_index)
{
    pos = p_pos;
    index = p_index;
}
Vector2f Level::getPos()
{
    return pos;
}


std::vector<Level> loadLevelSelect ()
{
    std::vector<Level> temp= {} ;
    temp.push_back( Level( Vector2f(267,292), 1 ));
    temp.push_back(Level( Vector2f( 379,292),2 ));
    temp.push_back(Level(Vector2f(493,292),3));
    temp.push_back(Level(Vector2f(607,292),4 ));
    temp.push_back(Level(Vector2f(267,395),5 ));
    temp.push_back(Level(Vector2f(380,395),6 ));
    temp.push_back(Level(Vector2f(496,395),7 ));
    temp.push_back(Level(Vector2f(607,395),8 ));

    return temp;

}
