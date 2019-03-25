#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"
#include "../combat/perso.h"
#include "fonctions.h"



int main(){



  ///////Initialisation de SDL/////////

  SDL_Init(SDL_INIT_EVERYTHING);

  TTF_Init();

  IMG_Init(IMG_INIT_PNG);

  //////Création de la fenetre où s'affichera le jeu//////

  SDL_Window* screen = SDL_CreateWindow("XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);






    //////Initailisation de la police d'écriture//////

    /*TTF_Font *police = NULL;

    police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);*/
//fenetre

  SDL_Event event;
  int quit = 0;

  long long unsigned debut;/*, fin , fpsCount = 0;*/

  SDL_Surface* pSurface = NULL;

  pSurface = SDL_GetWindowSurface(screen);

  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

  //SDL_Color c = {255,255,255};







  int argent=20000;
  int points=0;
  int etat = 0;
  int type_expedition;
  t_objet inv[nbObjets];
  load_inv(inv);
  //Personnage * equipe[4];
  /*SDL_Rect dest;
  dest.x = 100;
  dest.y = 100;

  SDL_Surface * test = TTF_RenderText_Solid(police, "test", c);*/


Personnage Picksou;

initPersonnage(&Picksou, "./data/Picksou.txt");















  while(!quit){

    debut = SDL_GetTicks();
    SDL_PollEvent(&event);
    //SDL_PumpEvents();
    //const Uint8 *state = SDL_GetKeyboardState(NULL);      //Vérification de quelles sont les touche qui sont enfoncé sur le clavier



    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));
    //SDL_BlitSurface(test, NULL, pSurface, &dest);

    switch (etat){
      case 0 : if(!inv_vide(inv)){echange(screen, inv, &argent, &points);} break;
      case 1 : type_expedition = expedition(screen); break;
      case 2 : commerce(screen, inv, &argent); break;

    }
    etat++;



printf("test2\n");

    //SDL_UpdateWindowSurface(screen);


/*
///fps
    switch(event.type) {

        case SDL_QUIT:
            quit = 1;
            break;

    }

    fin = SDL_GetTicks();

    printf("\nfps = %lld\n", (fpsCount++)*1000/SDL_GetTicks());

    printf("fpsCount = %lld\n", fpsCount);

    printf("fin = %lld\n", fin);

    int delai = ((1000/FPS)-(fin-debut));

    if(delai > 0) {

        SDL_Delay(delai);

    }
    char quitter;
    printf("quitter ?\n");
    scanf("%c", &quitter);
    if(quitter == 'y'){
      return 0;
    }*/
    if(etat == 3){
      return 0;
    }
  }
}
