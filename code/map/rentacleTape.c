#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "../lobby/fonctions.h"
#include "../combat/perso.h"
#include "../combat/const.h"
#include "../combat/fonction.h"

//plus tard

void afficherMapMieux(map_t * map, SDL_Rect camera, SDL_Window* screen){

  SDL_Surface* pSurface = SDL_GetWindowSurface(screen);
  SDL_Rect test = {0,0,HEX_WIDTH,HEX_HEIGHT};
  SDL_Surface * img = NULL;
  img = IMG_Load("code/map/hex/hex.png");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map->v[i][j].val){
        test.x = map->v[i][j].coord.x * (HEX_WIDTH - HEX_WIDTH/4-0.5) -camera.x + camera.w;
        test.y = map->v[i][j].coord.y * (HEX_HEIGHT - HEX_HEIGHT/2) -camera.y + camera.h;

        SDL_BlitSurface(img, NULL, pSurface, &test);
      }
    }
  }
}

/*
  \fn void afficher_perso_map(SDL_Surface * perso, int x, int y, SDL_Rect camera, SDL_Window* screen)
  \brief affiche le personnage aux coordonnées indiquées en fonction de la position de la caméra
  \param perso sprite du Personnage
  \param x coordonnée en x du personnage
  \param y coordonnée en y du personnage
  \param camera SDL_Rect correspondant à la position de la camera
  \param screen fenetre SDL
*/

void afficher_perso_map(SDL_Surface * perso, int x, int y, SDL_Rect camera, SDL_Window* screen){
  SDL_Surface* pSurface = SDL_GetWindowSurface(screen);
  SDL_Rect dest;
  dest.x = x-camera.x + camera.w-perso->w/2;
  dest.y = y -camera.y + camera.h-perso->h/2;
  SDL_BlitSurface(perso, NULL, pSurface, &dest);
}

/*
  \fn void centrage(SDL_Rect * camera, case_t map[N][M])
  \brief centre les coordonnées de la camera sur la case la plus proche
  \param camera SDL_Rect correspondant à la position de la camera
  \param map matrice de case symbolisant la carte
*/

void centrage(SDL_Rect * camera, case_t map[N][M]){
  int dist, min = 30000, i, j, nx, ny, test;
  for(i = 0; i<N; i++){
    for(j = 0; j<M; j++){
      if(map[i][j].val){
        /*printf("cam x abs : %i\n", -(*camera).x + (*camera).w);
        scanf("%i", dist);*/
        dist = distance((*camera).x, (*camera).y, map[i][j].coord.x*(HEX_WIDTH + HEX_WIDTH/2)/2 + HEX_WIDTH/2, map[i][j].coord.y*HEX_HEIGHT/2 + HEX_HEIGHT/2);
        printf("dist : %i\n", dist);
        if(dist < min){
          /*printf(" i : %i\n", i);
          scanf("%i", &test);*/
          min = dist;
          nx = map[i][j].coord.x*(HEX_WIDTH + HEX_WIDTH/2)/2+ HEX_WIDTH/2;
          ny = map[i][j].coord.y*HEX_HEIGHT/2 + HEX_HEIGHT/2;
        }
      }
    }
  }
  (*camera).x = nx;
  (*camera).y = ny;
}

void jugement(case_t map[N][M]){
  int i, j;
  for(i = 0; i<N; i++){
    for(j = 0; j<M; j++){
      if(map[i][j].val){
        printf("map[%i][%i] : x = %i y = %i\n", i, j, map[i][j].coord.x, map[i][j].coord.y);
      }
    }
  }
  int test;
  scanf("%i", &test);
}

/*
  \fn void deplacement(SDL_Event e, SDL_Rect * camera, int mouseX, int mouseY, case_t map[N][M], case_t * pos)
  \brief déplace le personnage sur la position de la souris si l'utilisateur clique sur une case et met a jour la caméra
  \param e SDL_Event
  \param camera pointeur sur la camera
  \param mouseX coordonnée en x de la souris
  \param mouseY coordonnée en y de la souris
  \param map matrice de case symbolisant la carte
  \param pos pointeur sur case corespondant à la position du personnage
*/

void deplacement(SDL_Event e, SDL_Rect * camera, int mouseX, int mouseY, case_t map[N][M], case_t * pos){

  if(SDL_PollEvent(&e)){
    switch(e.type) {
      case SDL_MOUSEBUTTONDOWN:
      switch(e.button.button){
        case SDL_BUTTON_MIDDLE:
          return 0;break;
        case SDL_BUTTON_LEFT:
            camera->x = mouseX - camera->w + camera->x;
            camera->y = mouseY - camera->h + camera->y;
            centrage(&camera, map);

            pos->coord.x = camera->x;
            pos->coord.y = camera->y;
          break;
      }
      break;
    }
  }
}
/****
int main(){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);
  SDL_Window* screen = SDL_CreateWindow("XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);
  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 0, 0));
  map_t * map = creerMap(1);
  SDL_Rect camera;
  int mouseX, mouseY/*, nouvX, nouvY*//****;
  SDL_Event e;
  SDL_Surface * perso = NULL;
  perso = IMG_Load("./data/miniGuts.png");
  Personnage guts;
  initPersonnage(&guts, "./data/Guts.txt");
  case_t pos = map->v[0][0];
  camera.x = pos.coord.x;
  camera.y = pos.coord.y;
  camera.w = SCREEN_WIDTH/2;
  camera.h = SCREEN_HEIGHT/2;

  while(1){
    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 0, 0));
    SDL_GetMouseState(&mouseX,&mouseY);
    afficherMapMieux(map, camera, screen);
    afficher_perso_map(perso, pos.coord.x, pos.coord.y, camera, screen);
    //printf("mouseX : %i\nmouseY : %i\n camera x : %i\ncamera y : %i\n", mouseX, mouseY, camera.x, camera.y);

    SDL_UpdateWindowSurface(screen);
    deplacement(e, &camera, mouseX, mouseY, map->v, &pos);
    /*int dist, min = 30000, i, j, nx, ny, test;
    for(i = 0; i<N; i++){
      for(j = 0; j<M; j++){
        if(map->v[i][j].val){
          printf("cam x abs : %i\n", -(*camera).x + (*camera).w);
          scanf("%i", dist);
          dist = distance(mouseX, mouseY, map->v[i][j].coord.x*(HEX_WIDTH + HEX_WIDTH/2)/2 + HEX_WIDTH/2, map->v[i][j].coord.y*HEX_HEIGHT/2 + HEX_HEIGHT/2);
          if(dist < min){
            min = dist;
            nx = i;
            ny = j;
          }
        }
      }
    }
    printf("nx : %i ny : %i\nmouseX : %i\nmouseY : %i\n camera x : %i\ncamera y : %i\n", nx, ny, mouseX, mouseY, camera.x, camera.y);*/

/*
    if(SDL_PollEvent(&e)){
      switch(e.type) {
        case SDL_MOUSEBUTTONDOWN:
        switch(e.button.button){
          case SDL_BUTTON_MIDDLE:
            return 0;break;
          case SDL_BUTTON_LEFT:
              camera.x = mouseX-camera.w+camera.x;
              camera.y = mouseY-camera.h+camera.y;
              //jugement(map->v);
              centrage(&camera, map->v);

              pos.coord.x = camera.x;
              pos.coord.y = camera.y;
            break;
        }
        break;
      }

    }

*/

  /*  camera.x = pos.coord.x;
    camera.y = pos.coord.y;*/
    /*char quitter;
    printf("quitter ?\n");
    scanf("%c", &quitter);
    if(quitter == 'y'){
      return 0;
    }*/
/*****  }

}*/
