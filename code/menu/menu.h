#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/**
  \file menu.h
  \brief XenoKart Eco Plus
  \author Benjamin Riviere
  \version 0.01
  \date 12 mars 2019
*/

typedef struct {SDL_Rect rec; SDL_Surface* txt;} affichage;

void fonctionQuitter();
void fonctionFin();
void afficher(affichage tab[], int tTab, SDL_Surface* pSurface, SDL_Window* screen, TTF_Font *police);
void fonctionJeu(SDL_Surface* pSurface, SDL_Window* screen, TTF_Font *police);
