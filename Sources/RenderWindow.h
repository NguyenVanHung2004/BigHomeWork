#pragma once
#include <SDL.h>
#include<SDL_ttf.h>

#include"Entity.h"

class RenderWindow
{

public:
    RenderWindow( const char* title , int w, int h);
    SDL_Texture* loadTexture( const char* file_path);
    void renderFrame( SDL_Rect* clip ,Entity& p_entity );
    void renderBg( SDL_Texture* p_tex , SDL_Rect* src  );
    void render( int x, int y, SDL_Texture* p_tex);
    void render(Entity& p_entity);
    void renderText( float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void display();
    void clear();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
