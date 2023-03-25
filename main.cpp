
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include"RenderWindow.h"
#include"Entity.h"
#include"soilder.h"
#include"Landmine.h"


bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if ((TTF_Init() ))
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

    bool SDLinit = init();

    RenderWindow window("Defense",960, 640);

    SDL_Texture* bgTexture =  window.loadTexture("Images/backgroundtemp.png");
    SDL_Texture* logoTexture =  window.loadTexture("Images/logo.png");
    SDL_Texture* bg01Texture = window.loadTexture("Images/bg03.png");
    SDL_Texture* soilderTexture = window.loadTexture("Images/soilder03.png");
    SDL_Texture* landmineTexture = window.loadTexture("Images/land_mine.png");
    SDL_Texture* landminetempTexture = window.loadTexture("Images/landmineSplash.png");
    SDL_Texture* soilderIdleTexture = window.loadTexture("Images/Idle.png");
    SDL_Texture* explosionTexture = window.loadTexture("Images/explo.png");
    SDL_Texture* playButtonTexture = window.loadTexture("Images/playButton01.png");
    SDL_Texture* playButtonClickTexture= window.loadTexture("Images/playButtonClick01.png");
    SDL_Texture* how2playButtonTexture = window.loadTexture("Images/how2playButton.png");
    SDL_Texture* how2playButtonClickTexture= window.loadTexture("Images/how2playButtonClick.png");
    SDL_Texture* quitButtonTexture= window.loadTexture("Images/quitButton.png");
    SDL_Texture* quitButtonClickTexture= window.loadTexture("Images/quitButtonClick.png");
    SDL_Texture* gameoverTexture = window.loadTexture("Images/gameover03.png");
    SDL_Texture* homeButtonTexture = window.loadTexture("Images/homeButton.png");
    SDL_Texture* replayButtonTexture = window.loadTexture("Images/replayButton.png");
    SDL_Texture* homeButtonClickTexture = window.loadTexture("Images/homeButtonClick.png");
    SDL_Texture* replayButtonClickTexture = window.loadTexture("Images/replayButtonClick.png");
    SDL_Texture* howToPlayTexture = window.loadTexture("Images/how2play01.png");
    SDL_Texture* okButtonTexture = window.loadTexture("Images/okButton.png");
    SDL_Texture* okClickButtonTexture = window.loadTexture("Images/okClickButton.png");
    SDL_Texture* homeButton02Texture = window.loadTexture( "Images/homeButton02.png");
    SDL_Texture* homeButton02ClickTexture = window.loadTexture( "Images/homeButton02Click.png");
    SDL_Texture* heartTexture = window.loadTexture("Images/heart.png");
    SDL_Texture* non_heartTexture = window.loadTexture("Images/heart_non.png");
    SDL_Texture* levelUpTexture = window.loadTexture("Images/leveluptemp.png");
    SDL_Texture* star1Texture = window.loadTexture("Images/1star.png");
    SDL_Texture* star2Texture = window.loadTexture("Images/2stars.png");
    SDL_Texture* star3Texture = window.loadTexture("Images/3stars.png");
    SDL_Texture* nextButtonTexture = window.loadTexture("Images/nextButton.png");
    SDL_Texture* nextButtonClickTexture = window.loadTexture("Images/nextButtonClick.png");
    SDL_Texture* shovelTexture = window.loadTexture("Images/Shovel.png");
    SDL_Texture* shovelClickTexture = window.loadTexture("Images/ShovelClick.png");
    SDL_Texture* shovel02Texture = window.loadTexture("Images/shovel02.png");
    TTF_Font* font12 = TTF_OpenFont("font/TheKingMaker.ttf" , 12);
    TTF_Font* font24 = TTF_OpenFont("font/TheKingMaker.ttf" , 24);
    TTF_Font* font48 = TTF_OpenFont("font/TheKingMaker.ttf" , 48);


    Mix_Chunk* explosion = Mix_LoadWAV("Sound/explosion.mp3");
    SDL_Color white = { 255, 255, 255 };
    SDL_Color green = { 0, 255, 0 };
    SDL_Color yellow = { 255 ,0,0};


    SDL_Event event;
    bool  gameRunning= true ;
    bool mouseDown = false;
    int num_mine = 3 ;
    int frame = 0 ;
    // status:  0: start screen , 1 : in game ,  2: next level   , -1 : lose ;
    int status = 0 ;
    int level = 0;
    int heal_point = 3;
    int soildersRemain = 0 ;
    bool displayHow2play = false;
    bool digging = false;
     Uint32 startTime = 0;
// load soilder
    std::vector<Soilder> loadSoilders(int level, SDL_Texture* tex );
    std::vector<Soilder> soilders = loadSoilders(level , soilderTexture);
    std::vector<Soilder> soildersIdle = loadSoilders(level , soilderIdleTexture);
// load booms
    std::vector<Landmine> landmines;
    std::vector<Landmine> explosions ;

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

 std::vector<Soilder> loadSoilders(int level , SDL_Texture* tex )
 {
        int type = -1;
        std::vector<Soilder> temp = {};
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
                    temp.push_back(Soilder(Vector2f(j +5   ,i - 15), tex));
            }
    }
    Tilemap.close();
    return temp;

}



std:: vector<Landmine>  loadLandMine(int level, SDL_Texture* tex )
{

        std:: vector<Landmine> temp;
        for (int i = 0 ; i < num_mine +3; i ++)
            temp.push_back( Landmine(Vector2f(-200, -200), tex));
        return temp;


}
void loadlevel( int level )
{

    window.render(0,0, bgTexture);
    soildersIdle = loadSoilders(level, soilderIdleTexture);
    soilders = loadSoilders(level, soilderTexture);
    soildersRemain = soildersIdle.size();

    num_mine = soildersRemain + 2;
    landmines = loadLandMine(level , landmineTexture );
    explosions = loadLandMine( level, explosionTexture) ;
    startTime = SDL_GetTicks();
    heal_point = 3;


}
const char* getLevelText(int level)
{
     std::string s = std::to_string(level +1 );
    s = "Level: " + s;
    return s.c_str();

}
const char* getAlertText ( int time )
{
    std::string s = std::to_string(time);

    s= "The enemy will attack in " + s ;
    return s.c_str();

}
const char* getNumMineRemainText(int p_num_mine )
{
     std::string s = std::to_string(p_num_mine);
    s = "x" + s;
    return s.c_str();

}




void update()
{
    lastTick = currentTick;
    currentTick = SDL_GetPerformanceCounter();
    deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            gameRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = true;

            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = false;
            }
            break;
        }
    }


    if ( status == 1)
    {

        SDL_Rect* currentFrame = &runClips[frame / 1000];
        // watching enemies
        if ( SDL_GetTicks() - startTime < 7000 )
           {
                for( Soilder& s : soildersIdle)
                window.render(currentFrame,s);
                window.renderText(140,130,"The enemies are coming, watch carefully!" , font24 , white );

           }

        // preparing: set position of landmines
        if ( SDL_GetTicks() - startTime >=  7000 && SDL_GetTicks() - startTime <= 17000)
            {

            window.renderText( 200,130, getAlertText( int ( 17 - (SDL_GetTicks() - startTime)/1000)), font24, yellow);
            window.render(770, 1, shovelTexture);
            int x ,y;
            SDL_GetMouseState( &x, &y);

            if ( num_mine > 0  && digging == false)
                {
                if  (  y >= 170 && y  <= 590 && x <= 800 )
                    {
                    window.render( (x/32) * 32 +5 , (y /33) *33 + 10 , landminetempTexture) ;
                    window.renderText( (x/32) * 32 +5  + 30 , (y /33) *33 + 10 , getNumMineRemainText( num_mine) , font12, green );
                    for( Landmine& l : landmines)
                        if ( mouseDown == true && l.getPos().x== -200 && l.getPos().y == -200 )
                         {
                        l.setPos( x/32 * 32 +5, (y /33) *33 + 10 );
                          num_mine--;
                          mouseDown = false;
                          break;
                         }
                    }
                }
            if ( digging )
            {
                window.render( x  , y  - 40  , shovel02Texture);
                window.render( 770 , 1, shovelClickTexture);
                 if ( mouseDown == true )
                         {
                          for( Landmine& l : landmines)
                                if( x >= l.getPos().x && x<= l.getPos().x + 25
                                   && y >=  l.getPos().y && y <=  l.getPos().y +25 )
                                    {
                                    l.setPos( -200, -200);
                                    num_mine++;
                                    }
                          mouseDown = false;
                        }

            }



             }

        for( Landmine& l : landmines)
            window.render(l);


        if ( SDL_GetTicks() - startTime >  17000)
        {
        for( Soilder& s : soilders)
        {
            s.update(landmines, heal_point , soildersRemain,deltaTime );
            if ( s.getDeath() == false)
                    window.render(currentFrame,s);

            // soilder dead

            else
                {
                    if ( s.animationDone  == false)
                        {
                        s.tempFrame = 6000 ;
                        Mix_PlayChannel( -1 , explosion ,0);
                        s.animationDone = true ;
                        }
                    s.setVelocity( 0, 0 );
                    s.tempFrame+= int(deltaTime*8);

                    window.render( &runClips[ s.tempFrame / 1000] ,s);
                    if ( s.tempFrame/1000 >= 13)
                        {
                            s.setPos(-200,-200);
                            s.tempFrame= 0;
                            }

                  for( Landmine& l : landmines)
                    {
                        if ( s.getPos().y + 48    >= l.getPos().y -   10  + 12  &&
                                s.getPos().y + 48  <= l.getPos().y  + 20 + 12  && s.getPos().x  + 24 > l.getPos().x)
                                l.setPos(-100, -100);
                    }
                }
        }

        //  lose status
        if ( heal_point <= 0 )
            status = -1;

        // win status , next level
        if ( soildersRemain <= 0  && heal_point >= 1)
            {
             //   level++;
               // loadlevel(level);
               status = 2;
            }

        }
    }
    window.display();
}
void graphic()
{   window.clear();
    window.render(0,0, bgTexture);
     window.render( 5 ,5  , homeButton02Texture);
    window.renderText( 400, 0, getLevelText(level) , font24, white);
    int x, y;
    SDL_GetMouseState(&x, &y);
     bool home02Inside = false;
     bool digInside = false;
    if ( status == 1 )
    {
        if  ( x>= 5 && x<= 30 && y >= 5 && y <= 30  )
            {
                home02Inside = true;
                window.render( 5,5, homeButton02ClickTexture);
            }
        if  ( x>= 770 && x<= 810  && y >= 1 && y <= 42   )
            {
                digInside = true;
            }
        if (home02Inside || digInside)
                while (SDL_PollEvent(&event))
                    {
                        switch(event.type)
                        {
                        case SDL_QUIT:
                            gameRunning = false;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if ( home02Inside && event.button.button == SDL_BUTTON_LEFT)
                                {
                                loadlevel(0);
                                status = 0;
                                }
                            else if ( digInside && event.button.button == SDL_BUTTON_LEFT && digging == false)
                                {
                                    digging = true;
                                }
                            else if  ( digInside && event.button.button == SDL_BUTTON_LEFT && digging)
                                {
                                    digging = false;
                                }
                            break;
                        }
                    }


        switch( heal_point )
        {
            case 0:
                window.render(840, 1, non_heartTexture );
                window.render(880, 1, non_heartTexture );
                window.render(920, 1, non_heartTexture );
                break;
            case 1:
                window.render(840, 1, heartTexture );
                window.render(880, 1, non_heartTexture );
                window.render(920, 1, non_heartTexture );
                break;
            case 2:
                window.render(840, 1, heartTexture );
                window.render(880, 1, heartTexture );
                window.render(920, 1, non_heartTexture );
                break;
            case 3:
                window.render(840, 1, heartTexture );
                window.render(880, 1, heartTexture );
                window.render(920, 1, heartTexture );
                break;
        }
}


    if ( status == -1 )
    {
        window.render( 0,0, gameoverTexture);
        window.render( 400, 300  , homeButtonTexture);
        window.render( 500  , 300  , replayButtonTexture);
        bool homeInside = false;
        bool replayInside = false;
        if ( x >= 400 && x <= 450 && y>= 300 && y <= 350 )
            homeInside = true;
        if( homeInside)
            window.render(400, 300  , homeButtonClickTexture);
        if ( x >= 500 && x <= 550 && y>= 300 && y <= 350 )
            replayInside = true ;
        if ( replayInside)
            window.render(500,300, replayButtonClickTexture);
        window.display();
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if ( homeInside && event.button.button == SDL_BUTTON_LEFT)
                    {
                    status = 0 ;
                    loadlevel(0);
                    level = 0 ;
                    heal_point =3;

                    }
                  else if ( replayInside && event.button.button == SDL_BUTTON_LEFT)
                    {
                    status = 1 ;
                    loadlevel(level);
                    heal_point =3;
                    }
                break;
            }
        }
    }
    if ( status == 2 )
    {

        window.render(  180 , 100  , levelUpTexture);
        switch( heal_point)
        {
            case 1:
                window.render( 355  , 200 , star1Texture );
                break;
            case 2:
                window.render( 355  , 200 , star2Texture );
                break;
            case 3 :
                window.render( 355  , 200 , star3Texture );
                break;
        }

        window.render ( 450 , 350 , nextButtonTexture );
        bool nextButtonInside = false;
        if (   x>= 450  && x<= 500 && y >= 350 && y <=400 )
        {
            nextButtonInside =true;
            window.render( 450, 350 ,  nextButtonClickTexture);
        }
        while (SDL_PollEvent(&event))
                    {
                        switch(event.type)
                        {
                        case SDL_QUIT:
                            gameRunning = false;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if( nextButtonInside && event.button.button ==  SDL_BUTTON_LEFT)
                            {
                                // next level
                                level++;
                                loadlevel(level);
                                status = 1;

                            }

                            break;
                        }
                    }
    }


}
void starScreen ()
{

        window.clear();
        window.render(0, 0, bgTexture);
        bool playInside = false ;
        bool quitInside = false ;
        bool how2playInside = false;
        bool okInside = false ;
        int x, y;
        SDL_GetMouseState( &x, &y );

        if ( displayHow2play == false)
        {
            window.render(275, 125 + 4*SDL_sin(SDL_GetTicks()*(3.14/1500)), logoTexture);
            window.render(400, 220, playButtonTexture);
            window.render(400, 370, quitButtonTexture);
            window.render(400,300,how2playButtonTexture);


            if( x >= 400 && x <= 550 && y >= 220 && y <= 280)
                {
                playInside = true;
                window.render(400,220,playButtonClickTexture);
                }

            if( x >= 400 && x <= 550 && y >= 370 && y <= 530)
                {
                quitInside = true;
                window.render(400,370,quitButtonClickTexture);
                }
            if( x >= 400 && x <= 550 && y >= 300 && y <= 360 )
                {
                how2playInside = true;
                window.render(400,300,how2playButtonClickTexture);
                }
        }

        if ( displayHow2play)
            {
            window.render( 200, 150 , howToPlayTexture);
            window.render( 500,400 , okButtonTexture);
             if( x >= 500 && x <= 550 && y >= 400 && y <= 470)
                {
                okInside = true;
                window.render( 500, 400 , okClickButtonTexture);
                }
            }

        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:

                if (event.button.button == SDL_BUTTON_LEFT && playInside)
                {
                    startTime = SDL_GetTicks();
                    status  =1 ;
                }
                if (event.button.button == SDL_BUTTON_LEFT && how2playInside)
                        displayHow2play = true ;
                if (event.button.button == SDL_BUTTON_LEFT && okInside && displayHow2play)
                        displayHow2play = false;
                if (event.button.button == SDL_BUTTON_LEFT && quitInside)
                    gameRunning = false;
                break;

            }
        }

    window.display();
}
int main(int argc, char* args[])
{

    setSoilerClip( runClips );
    setExploClip( exploClips);
    loadlevel(0);
    frame = 0;

    while(gameRunning)
    {
        if (status == 0)
            starScreen();
        else
        {
        graphic();
        update();
        }
        std::cout << num_mine << std::endl;
        frame += int( 8*deltaTime);

        if( frame / 1000 >= 5)
            frame = 0;



    }

    return 0;
}
