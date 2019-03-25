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
  \date 25 mars 2019
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

/**
    \fn void init_mat(case_t)
    \brief Cette fonction initialise les cases de la matrice à 0
    \param mat[N][M] Matrice de la carte
*/

void init_mat(case_t mat[N][M]){
  printf("inimat\n");
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      mat[i][j].val = 0;
    }
  }
}

/**
    \fn case_valide(case_t mat[N][M])
    \brief Cette fonction permet de vérifier que les coordonnées de la case sont valides
    \param hexcase une case t_case
*/


int case_valide(case_t hexcase){
  return((hexcase.coord.x < 0 || hexcase.coord.x > M) && (hexcase.coord.y < 0 || hexcase.coord.y > N));
}

/**
    \fn case_t creerCase(int x, int y)
    \brief Cette fonction permet de générer une case
    \param x Coordonnée X de la case
    \param y Coordonnée Y de la case
*/

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

/**
    \fn void creerCases(map_t * map)
    \brief Cette fonction permet de générer toutes les cases de la matrice
    \param map La carte
*/

void creerCases(map_t * map){

  printf("creercases\n");

  int i=0,j=0;

  for(i=0; i<N; i++){
    for(;j<M; j+=2){
      map->v[i][j] = creerCase(i,j);
    }
  if((i+1)%2) j=1;
  else j = 0;
  }
}

/**
    \fn map_t * creerMap(enum typemap type)
    \brief Cette fonction permet de créer la carte
    \param type Le type de carte
*/

map_t * creerMap(enum typemap type){
  printf("creermap\n");
  map_t * map = NULL ;
  map = malloc(sizeof(*map));

  init_mat(map->v);

  creerCases(map);

  return map;
}


void afficherMap(map_t * map, SDL_Surface* pSurface, SDL_Window* screen){


  SDL_Rect test = {0,0,HEX_WIDTH,HEX_HEIGHT};
  SDL_Surface * img = NULL;
  img = IMG_Load("code/map/hex.png");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map->v[i][j].val){
        test.x = map->v[i][j].coord.y * (HEX_WIDTH - HEX_HEIGHT/4);
        test.y = map->v[i][j].coord.x * (HEX_HEIGHT - HEX_HEIGHT/2);

        SDL_BlitSurface(img, NULL, pSurface, &test);
        SDL_UpdateWindowSurface(screen);
      }
    }
  }
}

/**
    \fn afficher_matrice(case_t [][])
    \brief Cette fonction permet de vérifier que les coordonnées de la case sont valides
    \param mat[N][M] Matrice de la carte
*/

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

/**
    \fn afficherMap(map_t * map, SDL_Surface* pSurface, SDL_Window* screen)
    \brief Cette fonction permet d'afficher la carte avec la SDL
    \param map La carte
    \param pSurface Surface sur laquel on affiche
    \param screen Ecran sur lequel on affiche
*/


int main(int argc, char** argv){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* screen = SDL_CreateWindow("Map - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);

  map_t * map = creerMap(1);

  afficher_matrice(map->v);

  afficherMap(map, pSurface, screen);

  while(!quit){

    deb = SDL_GetTicks();
    SDL_PumpEvents();

    fonctionFin();
    fonctionQuitter();

  }
  switch(quit){
    case 1 : printf("Programme fermé par la croix\n"); break;
    case 2 : printf("Programme fermé par le bouton\n"); break;
  }
}
