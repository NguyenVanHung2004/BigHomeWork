
#include<iostream>
#include"ArmoredCar.h"
#include"Landmine.h"
#include<vector>


ArmoredCar:: ArmoredCar ( Vector2f p_pos , SDL_Texture* p_tex) : Tank(p_pos, p_tex)
{

}



std::vector<ArmoredCar> loadAmouredCar ( int level, SDL_Texture* tex )
{
    int type = -1;
    std::vector<ArmoredCar> temp = {};
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
                if ( type == 3 )
                    temp.push_back(ArmoredCar(Vector2f(j + 5 , i -  45 ), tex));
            }
    }
    Tilemap.close();
    return temp;

}


void setAmouredCarClip ( SDL_Rect amouredCarClips[] )
{
        amouredCarClips[ 0 ].x =   0 ;
        amouredCarClips[ 0 ].y =   0 ;
        amouredCarClips[ 0 ].w =  160  ;
        amouredCarClips[ 0 ].h = 80 ;

        amouredCarClips[ 1 ].x =  160 ;
        amouredCarClips[ 1 ].y =   0;
        amouredCarClips[ 1 ].w =  160;
        amouredCarClips[ 1 ].h = 80 ;

        amouredCarClips[ 2 ].x =  320 ;
        amouredCarClips[ 2 ].y =   0;
        amouredCarClips[ 2 ].w =  160;
        amouredCarClips[ 2 ].h = 80;

        amouredCarClips[ 3 ].x = 480 ;
        amouredCarClips[ 3 ].y =   0 ;
        amouredCarClips[ 3 ].w = 160 ;
        amouredCarClips[ 3 ].h = 80  ;

        amouredCarClips[ 4 ].x = 640  ;
        amouredCarClips[ 4 ].y =   0 ;
        amouredCarClips[ 4 ].w = 160 ;
        amouredCarClips[ 4 ].h = 80 ;

        amouredCarClips[ 5 ].x = 800 ;
        amouredCarClips[ 5 ].y =   0 ;
        amouredCarClips[ 5 ].w = 160 ;
        amouredCarClips[ 5 ].h = 80 ;

        amouredCarClips[ 6 ].x = 960 ;
        amouredCarClips[ 6 ].y =   0 ;
        amouredCarClips[ 6 ].w = 160 ;
        amouredCarClips[ 6 ].h = 80 ;

        amouredCarClips[ 7 ].x = 1120 ;
        amouredCarClips[ 7 ].y =   0 ;
        amouredCarClips[ 7 ].w = 160 ;
        amouredCarClips[ 7 ].h = 80 ;
}





