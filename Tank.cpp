
#include<iostream>
#include"Tank.h"
#include"Landmine.h"
#include<vector>

Tank::Tank( Vector2f p_pos, SDL_Texture* p_tex) : Soilder(p_pos, p_tex)
{

};

void Tank::set_heal( int p_heal)
{
    heal = p_heal;
}
int Tank::get_heal()
{
    return heal;

}
bool Tank::getDamage()
  {
    return damage;
  }
void Tank::setDamage(bool p_damage)
{
    damage=  p_damage;
}

void  Tank::updateTank( std::vector<Landmine> landmines, int &heal_point, int max_heal  , int &enemiesRemain , double deltaTime ,Mix_Chunk* explosion , Mix_Chunk* Sound)
    {

    setPos( getPos().x + getVelocity().x*deltaTime*2 , getPos().y + getVelocity().y*deltaTime*2 );

    if ( getDeath() == false )
           {
                Mix_PlayChannel(  -1, Sound , 0);
                //setVelocity(0.04 , 0);
               for ( Landmine& l : landmines)
                if ( getPos().y +  75   >= l.getPos().y - 10  + 12  && getPos().y + 75  <=  l.getPos().y  + 20 + 12
                    && getPos().x + 130 > l.getPos().x)
                    {
                        set_heal(get_heal() -1);
                        Mix_HaltChannel( -1 );
                        Mix_PlayChannel(  0 , explosion, 0);

                    }

           }
    else  // getDeath == true
        {
            if ( animationDone == false )
                           {
                           tempFrame = 5000;
                           enemiesRemain -= max_heal ;
                           animationDone = true ;
                           }
                tempFrame+= int(deltaTime*8);
                if (tempFrame/1000 >= 8)
                        tempFrame= 5000;
                if( getVelocity().x < 0.001)
                        setVelocity( 0, 0 );
                else
                        setVelocity( getVelocity().x - 0.0001, 0 );

        }
    if ( get_heal() < max_heal )
            setDamage( true);
    if ( get_heal() == 0)
            setDeath(true);

    if ( getPos().x > 700  && getDeath() == false)
        {
             heal_point-= 1;
             enemiesRemain-=1;
              setDeath(true);
              Mix_HaltChannel( -1 );
             setPos(-100 , -100);
        }

    }


void  setTankClip ( SDL_Rect tankClips[] )
{
        tankClips[ 0 ].x =   0 ;
        tankClips[ 0 ].y =   0 ;
        tankClips[ 0 ].w =  192 ;
        tankClips[ 0 ].h = 96 ;

        tankClips[ 1 ].x =  192 ;
        tankClips[ 1 ].y =   0;
        tankClips[ 1 ].w =  192;
        tankClips[ 1 ].h = 96;

        tankClips[ 2 ].x =  384 ;
        tankClips[ 2 ].y =   0;
        tankClips[ 2 ].w =  192;
        tankClips[ 2 ].h = 96;

        tankClips[ 3 ].x = 576 ;
        tankClips[ 3 ].y =   0 ;
        tankClips[ 3 ].w = 192 ;
        tankClips[ 3 ].h = 96  ;

        tankClips[ 4 ].x = 768 ;
        tankClips[ 4 ].y =   0 ;
        tankClips[ 4 ].w = 192 ;
        tankClips[ 4 ].h = 96 ;

        tankClips[ 5 ].x = 960 ;
        tankClips[ 5 ].y =   0 ;
        tankClips[ 5 ].w = 192 ;
        tankClips[ 5 ].h = 96 ;

        tankClips[ 6 ].x = 1152 ;
        tankClips[ 6 ].y =   0 ;
        tankClips[ 6 ].w = 192 ;
        tankClips[ 6 ].h = 96 ;

        tankClips[ 7 ].x = 1344 ;
        tankClips[ 7 ].y =   0 ;
        tankClips[ 7 ].w = 192 ;
        tankClips[ 7 ].h = 96 ;
}

std::vector<Tank> loadTanks(int level, SDL_Texture* tex )
{
    int type = -1;
    std::vector<Tank> temp = {};
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
                if ( type == 2 )
                    temp.push_back(Tank(Vector2f(j +5 , i -  55 ), tex));
            }
    }
    Tilemap.close();
    return temp;

}

