#include<iostream>
#include"soilder.h"
#include"Landmine.h"
#include<vector>

Soilder::Soilder(Vector2f p_pos ,SDL_Texture* p_tex) : Entity(p_pos,p_tex)
    {
    };
void  Soilder::update( std::vector<Landmine> landmines, int &heal_point  , int &enemiesRemain , double deltaTime , Mix_Chunk* explosion)
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
    if ( getPos().x > 700  && getDeath() == false)
        {
             heal_point-= 1;
             enemiesRemain-=1;
             setPos(-100 , -100);
        }



    }



void Soilder::setVelocity( float x, float y)
    {
    velocity.x = x;
    velocity.y = y;

    }
Vector2f Soilder:: getVelocity()
{
    return velocity;
}
void Soilder:: setDeath(bool  p_death )
{
    death = p_death;
}
bool Soilder:: getDeath()
{
    return death;
}
void setSoilerClip( SDL_Rect runClips[] )
{
        runClips[ 0 ].x =   0 ;
        runClips[ 0 ].y =   0 ;
        runClips[ 0 ].w =  48 ;
        runClips[ 0 ].h = 48 ;

        runClips[ 1 ].x =  48;
        runClips[ 1 ].y =   0;
        runClips[ 1 ].w =  48;
        runClips[ 1 ].h = 48;

        runClips[ 2 ].x = 96;
        runClips[ 2 ].y =   0;
        runClips[ 2 ].w =  48;
        runClips[ 2 ].h = 48;

        runClips[ 3 ].x = 144 ;
        runClips[ 3 ].y =   0 ;
        runClips[ 3 ].w =  48 ;
        runClips[ 3 ].h = 48 ;

        runClips[ 4 ].x = 192 ;
        runClips[ 4 ].y =   0 ;
        runClips[ 4 ].w =  48 ;
        runClips[ 4 ].h = 48 ;

        runClips[ 5 ].x = 240 ;
        runClips[ 5 ].y =   0 ;
        runClips[ 5 ].w =  48 ;
        runClips[ 5 ].h = 48 ;

        runClips[ 6 ].x = 288 ;
        runClips[ 6 ].y =   0 ;
        runClips[ 6 ].w =  48 ;
        runClips[ 6 ].h = 48 ;

        runClips[ 7 ].x = 336 ;
        runClips[ 7 ].y =   0 ;
        runClips[ 7 ].w =  48 ;
        runClips[ 7 ].h = 48 ;

        runClips[ 8 ].x = 384 ;
        runClips[ 8 ].y =   0 ;
        runClips[ 8 ].w =  48 ;
        runClips[ 8 ].h = 48 ;

        runClips[ 9 ].x = 432 ;
        runClips[ 9 ].y =   0 ;
        runClips[ 9 ].w =  48 ;
        runClips[ 9 ].h = 48 ;

        runClips[ 10 ].x = 480 ;
        runClips[ 10 ].y =   0 ;
        runClips[ 10 ].w =  48 ;
        runClips[ 10 ].h = 48 ;

        runClips[ 11 ].x = 528 ;
        runClips[ 11 ].y =   0 ;
        runClips[ 11 ].w =  48 ;
        runClips[ 11 ].h = 48 ;

        runClips[ 12 ].x = 576 ;
        runClips[ 12 ].y =   0 ;
        runClips[ 12 ].w =  48 ;
        runClips[ 12 ].h = 48 ;

        runClips[ 13 ].x = 624 ;
        runClips[ 13 ].y =   0 ;
        runClips[ 13 ].w =  48 ;
        runClips[ 13 ].h = 48 ;

}

