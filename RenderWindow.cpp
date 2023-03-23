#include<iostream>
#include <SDL.h>
#include"RenderWindow.h"
#include "Entity.h"


RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow :: loadTexture( const char* file_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, file_path);

    if ( texture == NULL)
        std:: cout << "Can't load texture from file ";
    return texture;

}
  void RenderWindow::render(Entity& p_entity)
  {
    SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x ;
	dst.y = p_entity.getPos().y ;
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);

  }
  void RenderWindow::render( SDL_Rect* clip , Entity& p_entity )
  {

        SDL_Rect renderQuad = { p_entity.getPos().x, p_entity.getPos().y , clip->w , clip->h};


    SDL_RenderCopy(renderer, p_entity.getTex(), clip , &renderQuad );
  }


    void RenderWindow::render(int x, int y, SDL_Texture* p_tex)
    {
        SDL_Rect src;
        src.x = 0;
        src. y = 0;
        src.w;
        src.h;

        SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        dst.w = src.w;
        dst.h = src.h;

        SDL_RenderCopy(renderer, p_tex, &src, &dst);

    }
    void RenderWindow:: renderText(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
    {

		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h;

		SDL_Rect dst;
		dst.x = p_x;
		dst.y = p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
	 	SDL_DestroyTexture(message);
    }
    void RenderWindow::display()
    {
       SDL_RenderPresent(renderer);
    }
    void RenderWindow:: clear()
    {
        SDL_RenderClear(renderer);
    }
