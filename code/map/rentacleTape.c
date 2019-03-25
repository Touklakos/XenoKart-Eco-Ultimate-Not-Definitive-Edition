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

void afficherMapMieux(map_t * map, SDL_Rect camera, SDL_Window* screen){

  SDL_Surface* pSurface = SDL_GetWindowSurface(screen);
  SDL_Rect test = {0,0,HEX_WIDTH,HEX_HEIGHT};
  SDL_Surface * img = NULL;
  img = IMG_Load("code/map/hex.png");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map->v[i][j].val){
        test.x = map->v[i][j].coord.y * (HEX_WIDTH - HEX_HEIGHT/4) -camera.x + camera.w;
        test.y = map->v[i][j].coord.x * (HEX_HEIGHT - HEX_HEIGHT/2) -camera.y + camera.h;

        SDL_BlitSurface(img, NULL, pSurface, &test);
      }
    }
  }
}

void afficher_perso_map(SDL_Surface * perso, int x, int y, SDL_Rect camera, SDL_Window* screen){
  SDL_Surface* pSurface = SDL_GetWindowSurface(screen);
  SDL_Rect dest;
  dest.x = x-camera.x + camera.w-perso->w/2;
  dest.y = y -camera.y + camera.h-perso->h/2;
  SDL_BlitSurface(perso, NULL, pSurface, &dest);
}

int main(){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);
  SDL_Window* screen = SDL_CreateWindow("XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);
  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));
  map_t * map = creerMap(1);
  SDL_Rect camera;
  int mouseX, mouseY;
  SDL_Event e;
  SDL_Surface * perso = NULL;
  perso = IMG_Load("./data/miniGuts.png");
  Personnage guts;
  initPersonnage(&guts, "./data/Guts.txt");
  case_t pos = map->v[0][0];
  /*guts.posX = map->v[0][0].coord.x;
  guts.posY = map->v[0][0].coord.y;*/
  camera.x = pos.coord.x;
  camera.y = pos.coord.y;
  camera.w = SCREEN_WIDTH/2;
  camera.h = SCREEN_HEIGHT/2;

  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));
  while(1){
    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));
    SDL_GetMouseState(&mouseX,&mouseY);
    afficherMapMieux(map, camera, screen);
    afficher_perso_map(perso, camera.x, camera.y, camera, screen);
    printf("mouseX : %i\nmouseY : %i\n", mouseX, mouseY);

    SDL_UpdateWindowSurface(screen);


    if(SDL_PollEvent(&e)){
      switch(e.type) {
        case SDL_MOUSEBUTTONDOWN:
        switch(e.button.button){
          case SDL_BUTTON_MIDDLE:
            return 0;break;
          case SDL_BUTTON_LEFT:
            pos.coord.x = mouseX;
              camera.x = mouseX-camera.w+camera.x;
            pos.coord.y = mouseY;
              camera.y = mouseY-camera.h+camera.y;
            break;
        }
        break;
      }

    }
  /*  camera.x = pos.coord.x;
    camera.y = pos.coord.y;*/
    /*char quitter;
    printf("quitter ?\n");
    scanf("%c", &quitter);
    if(quitter == 'y'){
      return 0;
    }*/
  }

}
