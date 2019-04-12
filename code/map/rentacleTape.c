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

void afficherMapMieux(map_t * map, SDL_Rect camera, SDL_Surface* pSurface){


  SDL_Rect test = {0,0,HEX_WIDTH,HEX_HEIGHT};
  SDL_Surface * img = NULL;
  SDL_Surface * imgsubtype = NULL;


  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(map->v[i][j].val){
        test.x = map->v[i][j].coord.x * (HEX_WIDTH - HEX_WIDTH/4-0.5) -camera.x + camera.w;
        test.y = map->v[i][j].coord.y * (HEX_HEIGHT - HEX_HEIGHT/2) -camera.y + camera.h;

        switch(map->v[i][j].type){
          case 0 : img = IMG_Load("code/map/hex/hex_volcan.png"); break;
          case 1 : img = IMG_Load("code/map/hex/hex_montagne.png"); break;
          case 2 : img = IMG_Load("code/map/hex/hex_pic.png"); break;
          case 3 : img = IMG_Load("code/map/hex/hex_desert.png"); break;
          case 4 : img = IMG_Load("code/map/hex/hex_plateau.png"); break;
          case 5 : img = IMG_Load("code/map/hex/hex_plaine.png"); break;
          case 6 : img = IMG_Load("code/map/hex/hex_donjon.png"); break;
          case 7 : img = IMG_Load("code/map/hex/hex_marais.png"); break;
          case 8 : img = IMG_Load("code/map/hex/hex_tundra.png"); break;
          case 9 : img = IMG_Load("code/map/hex/hex_foret.png"); break;
          case 10 : img = IMG_Load("code/map/hex/hex_ocean.png"); break;
          case 11 : img = IMG_Load("code/map/hex/hex_archipel.png"); break;
          default : img = IMG_Load("code/map/hex/hex.png"); break;
        }
        switch(map->v[i][j].subtype){
          case 0 : imgsubtype = NULL;break;
          case 1 : imgsubtype = IMG_Load("code/map/hex/spawn.png"); break;
          case 2 : imgsubtype = IMG_Load("code/map/hex/end.png"); break;
          default : img = IMG_Load("code/map/hex/hex.png"); break;
        }

        SDL_BlitSurface(img, NULL, pSurface, &test);
        SDL_BlitSurface(imgsubtype, NULL, pSurface, &test);
        SDL_FreeSurface(img);
        SDL_FreeSurface(imgsubtype);

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

case_t * centrage(SDL_Rect * camera, case_t map[N][M]){
  int dist, min = 30000, i, j, nx, ny, test, indiceI, indiceJ;
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
          indiceI = i;
          indiceJ = j;
        }
      }
    }
  }
  (*camera).x = nx;
  (*camera).y = ny;
  return &map[indiceI][indiceJ];
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

void deplacement(SDL_Event e, SDL_Rect * camera, int mouseX, int mouseY, case_t map[N][M], case_t ** pos){

  if(SDL_PollEvent(&e)){
    switch(e.type) {
      case SDL_MOUSEBUTTONDOWN:
      switch(e.button.button){
        case SDL_BUTTON_MIDDLE:
          return;break;
        case SDL_BUTTON_LEFT:
            camera->x = mouseX - camera->w + camera->x;
            camera->y = mouseY - camera->h + camera->y;
            *pos = centrage(camera, map);

          break;
      }
      break;
    }
  }
}
