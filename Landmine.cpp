#include"Landmine.h"


Landmine::Landmine(Vector2f p_pos ,SDL_Texture* p_tex) :  Entity(p_pos, p_tex)
{

}

void setExploClip( SDL_Rect exploClips[] )
{
        exploClips[ 0 ].x =   0 ;
        exploClips[ 0 ].y =   0 ;
        exploClips[ 0 ].w =  40 ;
        exploClips[ 0 ].h = 40 ;

        exploClips[ 1 ].x =  40;
        exploClips[ 1 ].y =   0;
        exploClips[ 1 ].w =  40;
        exploClips[ 1 ].h = 40;

        exploClips[ 2 ].x = 80;
        exploClips[ 2 ].y =   0;
        exploClips[ 2 ].w =  40;
        exploClips[ 2 ].h = 40;

        exploClips[ 3 ].x = 0 ;
        exploClips[ 3 ].y =   40 ;
        exploClips[ 3 ].w =  40 ;
        exploClips[ 3 ].h = 40 ;

        exploClips[ 4 ].x = 40 ;
        exploClips[ 4 ].y =   40 ;
        exploClips[ 4 ].w =  40 ;
        exploClips[ 4 ].h = 40 ;

        exploClips[ 5 ].x = 80 ;
        exploClips[ 5 ].y =   80 ;
        exploClips[ 5 ].w =  40 ;
        exploClips[ 5 ].h = 40 ;
}
