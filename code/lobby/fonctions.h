#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

#define nbObjets 2








typedef struct s_objet{
  char nom[20];
  int nombre;
  int valeurPoints;
  int valeurArgent;
}t_objet;

void echange(SDL_Window * screen, t_objet inv[nbObjets], int *argent, int *points);

void commerce(SDL_Surface * psurface);

int expedition(SDL_Window * screen);

void load_inv(t_objet inv[nbObjets]);
