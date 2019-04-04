#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <time.h>

#include "map.h"
#include "../combat/const.h"


int main(int argc, char** argv){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* screen = SDL_CreateWindow("Map - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);

  map_t * map;
  initFile();

  do{
    if(map != NULL) free(map);
    caseCount = 1;
    map = creerMap(ARCHIPEL);
    pathfinding(map);
  }
  while(!valeurPath(map) || valeurPath(map) < 20);

  //afficher_matrice(map->v);
  afficher_path(map->v);
  //afficher_typecase(map->v);
  printf("pathfinding = %i\n", valeurPath(map));
  afficherMap(map, pSurface, screen);

  while(!quit){

    deb = SDL_GetTicks();
    SDL_PumpEvents();

    //fonctionFin();
    fonctionQuitter();

  }
  switch(quit){
    case 1 : printf("Programme fermé par la croix\n"); break;
    case 2 : printf("Programme fermé par le bouton\n"); break;

  }
  free(map);
}
