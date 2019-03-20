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

const int NB_CASE=N*M;

int caseCount = 1;

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

void init_mat(case_t mat[N][M]){
  printf("inimat\n");
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      mat[i][j].val = 0;
    }
  }
}

int case_valide(case_t hexcase){
  return((hexcase.coord.x < 0 || hexcase.coord.x > M) && (hexcase.coord.y < 0 || hexcase.coord.y > N));
}

void afficher_matrice(case_t c[N][M]){
    printf("affichermat\n");

  printf("---------------------------------------------- \n");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      printf("%3i|",c[i][j].val);
    }
    printf("\n");
  }
}

case_t creerCase(int x, int y){

  printf("creercase\n");
  case_t hexcase;

  printf("caseCount : %i \n", caseCount);

  hexcase.val = caseCount;

  hexcase.coord.x = x;
  hexcase.coord.y = y;

  caseCount++;

  return hexcase;
}

void creerCases(map_t * map){

  printf("creercases\n");

  int i=0,j=0;

  for(i=0; i<N; i++){
    for(j; j<M; j+=4){
      map->v[i][j] = creerCase(i,j);
    }
  if((i+1)%2) j=2;
  else j = 0;
  }
}

void afficherCase(case_t hexcase, case_t v[N][M]){
  printf("affichercase\n");

  printf("%d: ",hexcase.val);

  //if(case_valide());
  //else printf("0 ");

  printf("\n");
}


map_t * creerMap(enum typemap type){
  printf("creermap\n");
  map_t * map = NULL ;
  map = malloc(sizeof(*map));

  init_mat(map->v);

  creerCases(map);

  return map;
}



/*case_t recherchecase(int i, case_t map[N][M]){

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map[i][j].val = i) return map[i][j];
    }
  }
}*/

/*void afficher_voisin(case_t hexcase, SDL_Surface* pSurface, SDL_Window* screen){

  SDL_Rect test = {hexcase.x,hexcase.y,50,50};
  SDL_Surface * img = NULL;
  img = IMG_Load("code/map/hexagone.png");

  if(hexcase.voisin[0]->val != 0) test.y -= 672;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

  if(hexcase.voisin[1]->val != 0) test.x += 0.75*422; test.y -= (sqrt(3)/2) * 422;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

  if(hexcase.voisin[2]->val != 0) test.x += 0.75*422; test.y += (sqrt(3)/2) * 422;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

  if(hexcase.voisin[3]->val != 0) test.y += 672;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

}*/

void afficherMap(map_t * map, SDL_Surface* pSurface, SDL_Window* screen){


  SDL_Rect test = {0,0,HEX_WIDTH,HEX_HEIGHT};
  SDL_Surface * img = NULL;
  img = IMG_Load("code/map/hexagone.png");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map->v[i][j].val){
        test.x = map->v[i][j].coord.x * HEX_WIDTH;
        test.x = map->v[i][j].coord.y * HEX_HEIGHT;

        SDL_BlitSurface(img, NULL, pSurface, &test);

        SDL_UpdateWindowSurface(screen);
      }
    }
  }
}





int main(){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* screen = SDL_CreateWindow("Menu - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);

  map_t * map = creerMap(1);

  afficher_matrice(map->v);

  while(!quit) {

    deb = SDL_GetTicks();

    SDL_PumpEvents();


    afficherMap(map, pSurface, screen);

    //fonctionFin();
    fonctionQuitter();
  }
  switch(quit){
    case 1 : printf("Programme fermé par la croix\n"); break;
    case 2 : printf("Programme fermé par le bouton\n"); break;
  }
}
