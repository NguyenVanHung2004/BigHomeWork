#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include"RenderWindow.h"
#include"Global.h"
#include"Entity.h"
#include"soldier.h"
#include"Landmine.h"
#include"Tank.h"
#include"ArmoredCar.h"
#include"Level.h"

std::vector<Soldier> soldiersIdle = loadSoldiers(current_level, soldierIdleTexture);
std::vector<Soldier> loadSoldiers(int current_level, SDL_Texture* tex );
std::vector<Soldier> soldiers = loadSoldiers(current_level, soldierTexture);

std::vector<Tank> loadTanks(int current_level, SDL_Texture* tex );
std::vector<Tank> tanks ;

std::vector<ArmoredCar> loadAmouredCar(int current_level, SDL_Texture* tex );
std::vector<ArmoredCar> armoredCars  ;

// load booms
std::vector<Landmine> landmines;
std:: vector<Landmine>  loadLandMine( SDL_Texture* tex, int num_mine );

std::vector<Level> Selectlevels= loadLevelSelect();

const char* getLevelText(int level)
{
    std::string s = std::to_string(level +1 );
    s = "Level: " + s;
    return s.c_str();

}
const char* getAlertText ( int time )
{
    std::string s = std::to_string(time);

    s= "The enemies will attack in " + s ;
    return s.c_str();

}
const char* getNumMineRemainText(int p_num_mine )
{
    std::string s = std::to_string(p_num_mine);
    s = "x" + s;
    return s.c_str();

}
void loadlevel( int level );
void starScreen();
void gameplay();
void graphic();
void loseScreen();
void nextLevel();
void  completeGame();
int main(int argc, char* args[])
{
    setSoldierClip( runClips );
    setTankClip( tankClips);
    setAmouredCarClip( amouredCarClips);

    loadlevel(0);

    while(gameRunning)
    {

        if (status == 0)
            starScreen();
        else
        {
            gameplay();
            graphic();

        }

        frame += int( 8*deltaTime);

        if( frame / 1000 >= 5)
            frame = 0;

    }

    return 0;
}

void loadlevel( int level )
{

    window.render(0,0, bgTexture);
    soldiersIdle = loadSoldiers(level, soldierIdleTexture);
    soldiers = loadSoldiers(level, soldierTexture);
    tanks = loadTanks( level, tankTexture);
    armoredCars = loadAmouredCar( level , armoredCarTexure);

    enemiesRemain = soldiersIdle.size() + armoredCars.size()*2 + tanks.size()*3;
    num_mine = enemiesRemain + 1;
    landmines = loadLandMine( landmineTexture , num_mine);
    camera.x = 0;
    startTime = SDL_GetTicks();
    heal_point = 3;
    attacking = false;

}
void starScreen ()
{

    window.clear();
    window.render(0, 0, bgstartTexture);
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

    bool playInside = false ;
    bool quitInside = false ;
    bool selectLevelInside = false;
    bool how2playInside = false;
    bool okInside = false ;

    SDL_GetMouseState( &mousePosX, &mousePosY );

    if ( displayHow2play == false && displaySelectLevel == false )
    {
        window.render(250, 125 + 4*SDL_sin(SDL_GetTicks()*(3.14/1500)), logoTexture);
        window.render(400, 240, playButtonTexture);
        window.render(400 , 310 , selectlevelButtonTexture);
        window.render(400, 380 ,how2playButtonTexture);
        window.render(400, 450, quitButtonTexture);

        if( mousePosX  >= 400 && mousePosX  <= 550 && mousePosY >= 240 && mousePosY <= 300 )
        {
            playInside = true;
            window.render(400, 240, playButtonClickTexture);
        }

        if( mousePosX >= 400 && mousePosX <= 550 && mousePosY >= 310 && mousePosY <= 370 )
        {
            selectLevelInside = true;
            window.render(400,310,  selectlevelButtonClickTexture );
        }
        if( mousePosX >= 400 && mousePosX <= 550 && mousePosY >= 380 && mousePosY <= 440  )
        {
            how2playInside = true;
            window.render(400, 380, how2playButtonClickTexture);
        }
         if( mousePosX >= 400 && mousePosX <= 550 && mousePosY >= 450 && mousePosY <= 510  )
        {
            quitInside = true;
            window.render(400,450 ,quitButtonClickTexture);
        }
    }

    if ( displayHow2play)
    {
        window.render( 180, 150, howToPlayTexture);
        window.render( 450, 450, okButtonTexture);
        if( mousePosX  >= 450 && mousePosX <= 500 && mousePosY >= 450 && mousePosY <= 520)
        {
            okInside = true;
            window.render( 450, 450, okClickButtonTexture);
        }
    }

    if ( displaySelectLevel )
    {
        window.render(  70 , 50, levelSelectTexture );
        window.render( 450,450, okButtonTexture);

        if( mousePosX >= 450 && mousePosX <= 500 && mousePosY >= 450 && mousePosY <= 520)
        {
            okInside = true;
            window.render( 450 , 450, okClickButtonTexture);
        }
        // unlock level
        for ( int i = 0 ; i < highest_level ; i++)
            Selectlevels[i].unlock = true;

        for( Level& l : Selectlevels )
        {
            l.onclick = false;
        }
        for( Level& l : Selectlevels )
        {
            if ( l.unlock == false)
                window.render( l.getPos().x, l.getPos().y , levelLockTexture);

            if ( mousePosX > l.getPos().x && mousePosX < l.getPos().x + 58 &&  mousePosY > l.getPos().y && mousePosY < l.getPos().y + 58 )
                l.onclick = true;

            if ( l.onclick && mouseDown &&   l.unlock )
                {
                    status =1;
                    current_level = l.index -1;
                    loadlevel( current_level );
                    mouseDown = false;
                    displaySelectLevel = false;
                    l.onclick = false;
                }
        }


    }

    if ( mouseDown && playInside)
    {
        startTime = SDL_GetTicks();
        status  =1 ;
        mouseDown = false;
    }
    // open how2play screen
    if ( mouseDown && how2playInside)
       {
        displayHow2play = true ;
        mouseDown = false;
        }
    // close how2play screen
    if (mouseDown && okInside && displayHow2play)
        {
            displayHow2play = false;
            mouseDown = false;
        }
      // open selectlevel screen
    if ( mouseDown && selectLevelInside)
            {
            displaySelectLevel = true ;
            mouseDown = false;
            }
    // close selectlevel screen
    if (mouseDown && okInside && displaySelectLevel)
            {
                displaySelectLevel = false;
                mouseDown = false;
            }
    // quit
    if ( mouseDown && quitInside)
        {
            gameRunning = false;
            mouseDown = false;
        }


    window.display();
}

void gameplay()
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
    SDL_GetMouseState( &mousePosX, &mousePosY );

    // game play = 3 section : watching enemies , preparing , being attacked
    if ( status == 1)
    {

        SDL_Rect* soldierFrame = &runClips[frame / 1000];
        SDL_Rect* tankFrame = &tankClips[frame /1000];
        SDL_Rect* amouredCarsFrame = &amouredCarClips[frame/1000];

        // watching enemies
        if ( SDL_GetTicks() - startTime < 7000 )
            {
            for( Soldier& s : soldiersIdle)
                window.renderFrame(soldierFrame,s);
            for ( ArmoredCar& a: armoredCars )
                   {
                    window.renderFrame( &amouredCarClips[0] , a  );
                    a.set_heal(2);
                    }
            for( Tank& t: tanks)
                {
                    window.renderFrame( &tankClips[0], t  );
                    t.set_heal(3);
                }
            }

        // scrolling screen
        if ( SDL_GetTicks() - startTime >=  7000 && SDL_GetTicks() - startTime <=  8000)
        {

            if( camera.x == 960 )
                camera.x= 960;
            else camera.x +=  3 ;
            window.renderBg(bgTexture, &camera);
        }

        // preparing: set position of land-mines
        if ( SDL_GetTicks() - startTime >=  8000 && SDL_GetTicks() - startTime <= 18000)
        {
            // setting position of landmines
            if ( num_mine > 0  && digging == false)
            {
                if  (  mousePosY >= 170 && mousePosY  <= 590 && mousePosX <= 800 )
                {
                    window.render( (mousePosX/32) * 32 +5, (mousePosY /33) *33 + 10, landminetempTexture) ;
                    window.renderText( (mousePosX/32) * 32 +5  + 30, ( mousePosY /33) *33 + 10, getNumMineRemainText( num_mine), font12, green );
                    for( Landmine& l : landmines)
                        if ( mouseDown == true && l.getPos().x == -200 && l.getPos().y == -200 )
                        {
                            l.setPos( mousePosX/32 * 32 +5, (mousePosY /33) *33 + 10 );
                            num_mine--;
                            mouseDown = false;
                            break;
                        }
                }
            }
            // digging  landmines
            if ( digging && mousePosY >= 170 && mousePosY  <= 590 && mousePosX <= 800 )
            {
                window.render( mousePosX,mousePosY  - 40, shovel02Texture);
                if ( mouseDown == true )
                {
                    for( Landmine& l : landmines)
                        if( mousePosX >= l.getPos().x && mousePosX <= l.getPos().x + 25
                                && mousePosY >=  l.getPos().y && mousePosY <=  l.getPos().y +25 )
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


        // being attacked by enemies
        if ( SDL_GetTicks() - startTime >  18000)
        {
            // set positon of enemies
            if ( attacking == false )
            {
                for( Soldier& s : soldiers)
                    s.setPos( s.getPos().x - 300, s.getPos().y  );
                for( Tank& t : tanks)
                    {
                    t.setPos( t.getPos().x - 300, t.getPos().y  );
                    t.setVelocity( 0.03, 0);
                    }
                for( ArmoredCar& a : armoredCars)
                   {
                    a.setPos( a.getPos().x - 300, a.getPos().y );
                    a.setVelocity(0.04, 0);
                   }

                attacking = true;
            }

            for ( Tank& t: tanks)
            {

                t.updateTank(  landmines, heal_point, tank_max_heal  ,enemiesRemain ,deltaTime , explosionSound , tankSound);
                if ( t.getDeath() == false)
                {
                    if ( t.getDamage() == true )
                        window.renderFrame( tankFrame, t);
                    else
                        window.renderFrame( &tankClips[0], t );

                    for( Landmine& l : landmines)
                        {

                        if ( t.getPos().y + 75    >= l.getPos().y  -   10  + 12  &&
                                t.getPos().y + 75  <= l.getPos().y  + 20 + 12  && t.getPos().x +130  > l.getPos().x  )
                            l.setPos(-100, -100);
                        }
                }
                // death
                else
                {
                     for( Landmine& l : landmines)
                    {

                        if ( t.getPos().y + 75    >= l.getPos().y  -   10  + 12  &&
                                t.getPos().y + 75  <= l.getPos().y  + 20 + 12  && t.getPos().x +130  > l.getPos().x  )
                            l.setPos(-100, -100);
                    }
                    window.renderFrame( &tankClips[ t.tempFrame / 1000] ,t );
                }
            }

            for ( ArmoredCar& a : armoredCars)
            {
                a.updateTank( landmines, heal_point, amouredcar_max_heal , enemiesRemain, deltaTime, explosionSound ,armoredCarSound);
                if ( a.getDeath() == false)
                {
                    if ( a.getDamage() == true )
                        window.renderFrame( amouredCarsFrame , a);
                    else
                        window.renderFrame( &amouredCarClips[0], a );
                    for( Landmine& l : landmines)
                        {

                        if ( a.getPos().y + 75    >= l.getPos().y  -   10  + 12  &&
                                a.getPos().y + 75  <= l.getPos().y  + 20 + 12  && a.getPos().x +130  > l.getPos().x  )
                            l.setPos(-100, -100);
                        }

                }
                // death
                else
                {

                     for( Landmine& l : landmines)
                    {

                        if ( a.getPos().y + 75    >= l.getPos().y  -   10  + 12  &&
                                a.getPos().y + 75  <= l.getPos().y  + 20 + 12  && a.getPos().x +130  > l.getPos().x  )
                            l.setPos(-100, -100);
                    }

                    window.renderFrame( &amouredCarClips[ a.tempFrame / 1000] ,a  );

                }
            }


            for( Soldier& s : soldiers)
            {
                s.update(landmines , heal_point, enemiesRemain,deltaTime, explosionSound );
                if ( s.getDeath() == false)
                    window.renderFrame( soldierFrame , s);

                //  death

                else
                {

                    window.renderFrame( &runClips[ s.tempFrame / 1000],s);
                    for( Landmine& l : landmines)
                    {
                        if ( s.getPos().y + 48    >= l.getPos().y -  10  + 12  &&
                                s.getPos().y + 48  <= l.getPos().y  + 20 + 12  && s.getPos().x  + 24 > l.getPos().x)
                            l.setPos(-100, -100);
                    }
                }
            }

            if ( heal_point <= 0 )
                //  lose status
                status = -1;

            if ( enemiesRemain <= 0  && heal_point >= 1)
            {
                // next level status
                status = 2;
            }

        }
    }
    window.display();
}

void graphic()
{
    window.clear();

    // in game status
    if ( status == 1 )
    {
        window.renderBg( bgTexture, &camera);
        window.render( 5,5, homeButton02Texture);
        window.renderText( 400, 0, getLevelText(current_level), font24, white);
        bool home02Inside = false;
        bool digInside = false;
        if  ( mousePosX >= 5 && mousePosX <= 30 && mousePosY >= 5 && mousePosY <= 30  )
        {
            home02Inside = true;
            window.render( 5,5, homeButton02ClickTexture);
        }
        if  ( mousePosX >= 770 && mousePosX <= 810  && mousePosY >= 1 && mousePosY <= 42   )
            digInside = true;


        if (home02Inside || digInside)
        {

                if ( home02Inside && mouseDown )
                {
                   loadlevel(current_level);
                   status = 0 ;
                   mouseDown = false;

                }
                 if ( digInside && digging == false && mouseDown )
                {
                    digging = true ;
                    mouseDown = false;

                }
                if ( digInside && digging == true   && mouseDown )
                {
                    digging = false;
                    mouseDown = false;
                }

        }


          if ( SDL_GetTicks() - startTime < 7000 )
        {
              window.renderText(140,130,"The enemies are coming, watch carefully!", font24, red );

        }

          if ( SDL_GetTicks() - startTime >=  8000 && SDL_GetTicks() - startTime <= 18000)
        {

            window.renderText( 200,130, getAlertText( int ( 17 - (SDL_GetTicks() - startTime)/1000)), font24, red);
            window.render( 770, 1, shovelTexture);
            if ( digging )
                window.render( 770, 1, shovelClickTexture);

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
    // lose screen
    if ( status == -1 )
    {
        loseScreen();
    }
    // next level status
    if ( status == 2 )
    {
        nextLevel();
    }
    // complete game
    if ( status == 3  )
    {
       completeGame();
    }

}

void nextLevel()
{
    window.render(0, 0, bgTexture);
        window.render(  180, 100, levelUpTexture);
        switch( heal_point)
        {
        case 1:
            window.render( 355, 200, star1Texture );
            break;
        case 2:
            window.render( 355, 200, star2Texture );
            break;
        case 3 :
            window.render( 355, 200, star3Texture );
            break;
        }

        window.render ( 450, 350, nextButtonTexture );
        bool nextButtonInside = false;
        if (   mousePosX >= 450  &&  mousePosX <= 500 && mousePosY >= 350 && mousePosY <=400 )
        {
            nextButtonInside =true;
            window.render( 450, 350,  nextButtonClickTexture);
        }
        if ( nextButtonInside && mouseDown )
            {
                current_level++;
                if ( current_level >= highest_level)
                    highest_level = current_level;
                if ( current_level <= 7  )
                {
                    loadlevel( current_level );
                    status = 1;  // in game status ( next level)
                }
                else
                {
                   status = 3;  // complete game
                }
            }
}
void loseScreen()
{
        window.render( 0,0, gameoverTexture);
        window.render( 400, 300, homeButtonTexture);
        window.render( 500, 300, replayButtonTexture);
        bool homeInside = false;
        bool replayInside = false;
        if ( mousePosX >= 400 && mousePosX <= 450 && mousePosY >= 300 && mousePosY <= 350 )
            {
            homeInside = true;
            window.render(400, 300, homeButtonClickTexture);
            }
        if ( mousePosX >= 500 && mousePosX <= 550 && mousePosY >= 300 && mousePosY <= 350 )
            {
            replayInside = true ;
            window.render(500,300, replayButtonClickTexture);
            }
        window.display();

        if ( homeInside && mouseDown )
        {
             status = 0 ;
             current_level = 0 ;
             loadlevel(current_level);
             mouseDown = false;

        }
        else if ( replayInside && mouseDown )
        {
            status = 1 ;
            loadlevel(current_level);
             mouseDown = false;

        }

}
void completeGame()
{
        window.render(0,0 , completeGameTexture);
        window.renderText(160,450, "You complete the game!", font48 , white);
        window.render( 450, 530, homeButtonTexture);
        bool homeInside = false;
        if ( mousePosX >= 450 && mousePosX <= 500 && mousePosY >= 530 && mousePosY <= 580 )
            {
            homeInside = true;
            window.render( 450, 530 , homeButtonClickTexture);
            }
        if ( homeInside && mouseDown )
            {
            mouseDown = false;
            status =0;
            }
}

