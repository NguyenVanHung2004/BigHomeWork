#pragma once
#include"RenderWindow.h"
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
        std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    if (!(IMG_Init(IMG_INIT_PNG)))
        std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
    if ((TTF_Init() ))
        std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048);
    return true;
}

bool SDLinit = init();
const int SCREEN_WIDTH = 960 ;
const int SCREEN_HEIGHT = 640 ;
RenderWindow window("Defense",SCREEN_WIDTH, SCREEN_HEIGHT);

// enemies texture
SDL_Texture* soldierIdleTexture = window.loadTexture("Images/Idle.png");
SDL_Texture* soldierTexture = window.loadTexture("Images/soilderfinal.png");
SDL_Texture* tankTexture = window.loadTexture("Images/tankfinal.png");
SDL_Texture* armoredCarTexure = window.loadTexture("Images/AmouredCarSprite.png");

// gamelay texture
SDL_Texture* bgTexture =  window.loadTexture("Images/bgtemp.png");
SDL_Texture* landmineTexture = window.loadTexture("Images/land_mine.png");
SDL_Texture* landminetempTexture = window.loadTexture("Images/landmineSplash.png");
SDL_Texture* shovelTexture = window.loadTexture("Images/Shovel.png");
SDL_Texture* shovelClickTexture = window.loadTexture("Images/ShovelClick.png");
SDL_Texture* shovel02Texture = window.loadTexture("Images/shovel02.png");
SDL_Texture* homeButton02Texture = window.loadTexture( "Images/homeButton02.png");
SDL_Texture* homeButton02ClickTexture = window.loadTexture( "Images/homeButton02Click.png");
SDL_Texture* heartTexture = window.loadTexture("Images/heart.png");
SDL_Texture* non_heartTexture = window.loadTexture("Images/heart_non.png");


// startscreen texture
SDL_Texture* bgstartTexture = window.loadTexture("Images/bgStart.png");
SDL_Texture* logoTexture =  window.loadTexture("Images/logo.png");

SDL_Texture* playButtonTexture = window.loadTexture("Images/playButton.png");
SDL_Texture* playButtonClickTexture= window.loadTexture("Images/playButtonClick.png");

SDL_Texture* howToPlayTexture = window.loadTexture("Images/how2play.png");
SDL_Texture* how2playButtonTexture = window.loadTexture("Images/how2playButton.png");
SDL_Texture* how2playButtonClickTexture= window.loadTexture("Images/how2playButtonClick.png");

SDL_Texture* quitButtonTexture= window.loadTexture("Images/quitButton.png");
SDL_Texture* quitButtonClickTexture= window.loadTexture("Images/quitButtonClick.png");

SDL_Texture* okButtonTexture = window.loadTexture("Images/okButton.png");
SDL_Texture* okClickButtonTexture = window.loadTexture("Images/okClickButton.png");

SDL_Texture* selectlevelButtonTexture = window.loadTexture("Images/selectlevelButton.png");
SDL_Texture* selectlevelButtonClickTexture = window.loadTexture("Images/selectlevelClick.png");

SDL_Texture* levelSelectTexture = window.loadTexture("Images/Level-Select.png");
SDL_Texture* levelLockTexture = window.loadTexture("Images/splash.png");

// lose screen texture
SDL_Texture* gameoverTexture = window.loadTexture("Images/gameover.png");
SDL_Texture* homeButtonTexture = window.loadTexture("Images/homeButton.png");
SDL_Texture* replayButtonTexture = window.loadTexture("Images/replayButton.png");
SDL_Texture* homeButtonClickTexture = window.loadTexture("Images/homeButtonClick.png");
SDL_Texture* replayButtonClickTexture = window.loadTexture("Images/replayButtonClick.png");
SDL_Texture* completeGameTexture = window.loadTexture("Images/completeGame.png");

// next level texture
SDL_Texture* levelUpTexture = window.loadTexture("Images/levelup.png");
SDL_Texture* star1Texture = window.loadTexture("Images/1star.png");
SDL_Texture* star2Texture = window.loadTexture("Images/2stars.png");
SDL_Texture* star3Texture = window.loadTexture("Images/3stars.png");
SDL_Texture* nextButtonTexture = window.loadTexture("Images/nextButton.png");
SDL_Texture* nextButtonClickTexture = window.loadTexture("Images/nextButtonClick.png");


TTF_Font* font12 = TTF_OpenFont("font/TheKingMaker.ttf", 12);
TTF_Font* font24 = TTF_OpenFont("font/TheKingMaker.ttf", 24);
TTF_Font* font48 = TTF_OpenFont("font/TheKingMaker.ttf", 48);


Mix_Chunk* explosionSound = Mix_LoadWAV("Sound/explosion.mp3");
Mix_Chunk* tankSound = Mix_LoadWAV("Sound/tank1.mp3");
Mix_Chunk* armoredCarSound  = Mix_LoadWAV("Sound/cartemp.mp3");

SDL_Color white = { 255, 255, 255 };
SDL_Color green = { 0, 255, 0 };
SDL_Color red = { 255,0,0};



// global  variables
SDL_Event event;
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
bool  gameRunning= true ;
bool mouseDown = false;
int num_mine = 0  ;
int frame = 0 ;
// status:  0: start screen , 1 : in game ,  2: next level   , -1 : lose , 3: complete game ;
int status = 0 ;

int current_level = 0 ;
int highest_level = 1 ;
int heal_point = 3;

int enemiesRemain = 0 ;
int tank_max_heal = 3;
int amouredcar_max_heal = 2;

bool attacking = false;
bool displayHow2play = false;
bool displaySelectLevel = false;
bool digging = false;

int mousePosX ;
int mousePosY;
Uint32 startTime = 0;
Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;
