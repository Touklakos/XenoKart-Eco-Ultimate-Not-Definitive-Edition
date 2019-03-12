#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "../combat/const.h"

int fpsCount = 0;
int fin = 0;
int deb = 0;
int quit = 0;

SDL_Event event;

const int NB_CASE=20;

int caseCount = 0;

/**
  \file map.c
  \brief XenoKart Eco Plus
  \author Benjamin Riviere
  \version 0.01
  \date 12 mars 2019
*/

/**
    \fn void fonctionQuitter()
    \brief Cette fonction vérifie si l'utilisateur veut fermer le programme avec la croix
*/

void fonctionQuitter(){

  SDL_PollEvent(&event);

  switch(event.type){
      case SDL_QUIT:
        quit = 1;
        break;
  }
}

/**
    \fn void fonctionFin()
    \brief Cette fonction affiche les statistiques à la fin des boucles dans les fonctions
*/

void fonctionFin(){
  fin = SDL_GetTicks();

  printf("\nfps = %i\n", (fpsCount++)*1000/SDL_GetTicks());
  printf("fin = %i\n", fin/1000);
  int delai = ((1000/FPS)-(fin-deb));

  if(delai > 0){
    SDL_Delay(delai);
  }
}

case_t creerCase(){
  case_t hexcase;
  hexcase.val = caseCount;
  return hexcase;
}

case_t creerCaseVoisin(case_t hexcase){
  case_t t[6];
  for(int i = 0; i < 6; i++){
    while(caseCount < NB_CASE-1){
      if(hexcase.voisin[i] != NULL){
        t[i] = creerCase();
        ajouter(t[i]);
        t[i].val = 0;
        hexcase.voisin[i] = &t[i];
        caseCount++;
      }
    }
  }
  return hexcase;
}


map_t * creerMap(enum typemap type){
  map_t * map = NULL ;
  map = malloc(sizeof(*map));

  map->c[N/2][M/2] = creerCase();
  creerCaseVoisin(map->c[N/2][M/2]);




  return map;
}

void afficherMap(case_t c[N][M], SDL_Surface* pSurface, SDL_Window* screen){
  SDL_Rect test = {(SCREEN_WIDTH/2)-(100)/2,(SCREEN_HEIGHT/2)-(100)/2,50,50};

  SDL_Surface * img = NULL;
  img = IMG_Load("code/map/test.png");
  SDL_BlitSurface(img, NULL, pSurface, &test);

  SDL_UpdateWindowSurface(screen);
}

int main(){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* screen = SDL_CreateWindow("Menu - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);

  map_t * map = creerMap(1);

  while(!quit) {

    deb = SDL_GetTicks();

    SDL_PumpEvents();

    afficherMap(map->c,pSurface, screen);
    fonctionFin();
    fonctionQuitter();
  }
  switch(quit){
    case 1 : printf("Programme fermé par la croix\n"); break;
    case 2 : printf("Programme fermé par le bouton\n"); break;
  }
}
