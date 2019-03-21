#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

#define nbObjets 8








typedef struct s_objet{
  char nom[20];
  int nombre;
  int valeurPoints;
  int valeurArgent;
}t_objet;

void echange(SDL_Window * , t_objet inv[nbObjets], int *, int *);

void commerce(SDL_Window * , t_objet inv[nbObjets], int *);

int expedition(SDL_Window *);

void load_inv(t_objet inv[nbObjets]);

void load_vendeur(t_objet inv[nbObjets]);

void afficher_inv(SDL_Window *, int, int, int, int, t_objet inv[nbObjets]);

int inv_vide(t_objet inv[nbObjets]);
