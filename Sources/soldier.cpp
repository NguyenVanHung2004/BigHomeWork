#include<iostream>
#include"soldier.h"
#include"Landmine.h"
#include<vector>

Soldier::Soldier(Vector2f p_pos ,SDL_Texture* p_tex) : Entity(p_pos,p_tex)
    {
    };
void  Soldier::update( std::vector<Landmine> landmines, int &heal_point  , int &enemiesRemain , double deltaTime , Mix_Chunk* explosion)
    {
    setPos( getPos().x + getVelocity().x*deltaTime*2 , getPos().y + getVelocity().y*deltaTime*2 );

    for ( Landmine& l : landmines)
            if ( getPos().y +  getCurrentFrame().h   >= l.getPos().y - 10  + 12  && getPos().y + getCurrentFrame().h   <=  l.getPos().y  + 20 + 12  && getPos().x  + 24 > l.getPos().x)
            {
                    if ( getDeath() == false)
                        {
                        enemiesRemain-= 1;
                        Mix_PlayChannel( 2, explosion,0);
                        }
                    setDeath ( true );

            }
    if ( getDeath() == true )
    {
            if ( animationDone  == false)
                    {
                        tempFrame = 6000 ;
                        animationDone = true ;
                    }
            setVelocity( 0, 0 );
            tempFrame+= int(deltaTime*8);
            if ( tempFrame/1000 >= 13)
                {
                    setPos(-200,-200);
                    tempFrame = 0;
                }
    }
    if ( getPos().x > 750  && getDeath() == false)
        {

             heal_point-= 1;
             enemiesRemain-=1;
             setPos(-100 , -100);
             setVelocity( 0, 0 );
        }



    }



void Soldier::setVelocity( float x, float y)
    {
    velocity.x = x;
    velocity.y = y;

    }
Vector2f Soldier:: getVelocity()
{
    return velocity;
}
void Soldier:: setDeath(bool  p_death )
{
    death = p_death;
}
bool Soldier:: getDeath()
{
    return death;
}


void setSoldierClip( SDL_Rect soldierClips[] )
{
        soldierClips[ 0 ].x =   0 ;
        soldierClips[ 0 ].y =   0 ;
        soldierClips[ 0 ].w =  48 ;
        soldierClips[ 0 ].h = 48 ;

        soldierClips[ 1 ].x =  48;
        soldierClips[ 1 ].y =   0;
        soldierClips[ 1 ].w =  48;
        soldierClips[ 1 ].h = 48;

        soldierClips[ 2 ].x = 96;
        soldierClips[ 2 ].y =   0;
        soldierClips[ 2 ].w =  48;
        soldierClips[ 2 ].h = 48;

        soldierClips[ 3 ].x = 144 ;
        soldierClips[ 3 ].y =   0 ;
        soldierClips[ 3 ].w =  48 ;
        soldierClips[ 3 ].h = 48 ;

        soldierClips[ 4 ].x = 192 ;
        soldierClips[ 4 ].y =   0 ;
        soldierClips[ 4 ].w =  48 ;
        soldierClips[ 4 ].h = 48 ;

        soldierClips[ 5 ].x = 240 ;
        soldierClips[ 5 ].y =   0 ;
        soldierClips[ 5 ].w =  48 ;
        soldierClips[ 5 ].h = 48 ;

        soldierClips[ 6 ].x = 288 ;
        soldierClips[ 6 ].y =   0 ;
        soldierClips[ 6 ].w =  48 ;
        soldierClips[ 6 ].h = 48 ;

        soldierClips[ 7 ].x = 336 ;
        soldierClips[ 7 ].y =   0 ;
        soldierClips[ 7 ].w =  48 ;
        soldierClips[ 7 ].h = 48 ;

        soldierClips[ 8 ].x = 384 ;
        soldierClips[ 8 ].y =   0 ;
        soldierClips[ 8 ].w =  48 ;
        soldierClips[ 8 ].h = 48 ;

        soldierClips[ 9 ].x = 432 ;
        soldierClips[ 9 ].y =   0 ;
        soldierClips[ 9 ].w =  48 ;
        soldierClips[ 9 ].h = 48 ;

        soldierClips[ 10 ].x = 480 ;
        soldierClips[ 10 ].y =   0 ;
        soldierClips[ 10 ].w =  48 ;
        soldierClips[ 10 ].h = 48 ;

        soldierClips[ 11 ].x = 528 ;
        soldierClips[ 11 ].y =   0 ;
        soldierClips[ 11 ].w =  48 ;
        soldierClips[ 11 ].h = 48 ;

        soldierClips[ 12 ].x = 576 ;
        soldierClips[ 12 ].y =   0 ;
        soldierClips[ 12 ].w =  48 ;
        soldierClips[ 12 ].h = 48 ;

        soldierClips[ 13 ].x = 624 ;
        soldierClips[ 13 ].y =   0 ;
        soldierClips[ 13 ].w =  48 ;
        soldierClips[ 13 ].h = 48 ;

}

  std::vector<Soldier> loadSoldiers(int level, SDL_Texture* tex )
{
    int type = -1;
    std::vector<Soldier> temp = {};
    std::string filepath ="Maps/map";
    filepath += std::to_string(level) +".txt";
    std::ifstream Tilemap(filepath);
    if( Tilemap.fail() )
    {
        printf( "Unable to load map file!\n" );
    }
    else
    {
        for ( int i = 171  ; i < 640 ; i+= 33 )
            for( int j = 0 ; j < 960 ; j += 32)
            {
                Tilemap >> type;
                if ( type == 1 )
                    temp.push_back(Soldier(Vector2f(j +5,i - 15), tex));
            }
    }
    Tilemap.close();
    return temp;

}

