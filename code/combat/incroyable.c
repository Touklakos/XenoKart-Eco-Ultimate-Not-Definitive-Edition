
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "ennemi.h"

/**
  \file incroyable.c
  \brief XenoKart Eco Plus
  \author Mano Brabant
  \version 0.01
  \date 13 fevrier 2019
*/


#include "fonctionMain.c"


int main(int argc, char** argv)
{

  coop = 0;
  serveur = 0;
  if(argc == 3)
    serveur = 1;

  indicePersonnage = 0;       //variable qui indique quel personnage on est entrain de controller


  if(coop) connexion();

  srand(time(NULL));



  ///////Initialisation de SDL/////////

  SDL_Init(SDL_INIT_EVERYTHING);

  TTF_Init();

  IMG_Init(IMG_INIT_PNG);


  /////////////////////////////////////

  //////Création de la fenetre où s'affichera le jeu//////

  screen = SDL_CreateWindow("XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);




  pSurface = SDL_GetWindowSurface(screen);

  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255));


  initJeu();

  SDL_Event event;

  int quit = 0;               //quitte le programme si on appuie sur la croix rouge



  long long unsigned debut, fin, fpsCount = 0;


  for(int i = 0; i< 1000; i++) {

    clavier[i].enfonce = 0;
    clavier[i].relache = 0;

  }

    while(!quit) {

      //////////////////////////////////////FONCTIONS D'AFFICHAGE DES FPS, DU BACKGROUND////////////////////////////////////////////


      debut = SDL_GetTicks();

      SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255)); //on nettoye l'�cran en affichant un grand rectangle blanc


      //////////////////////////////////////FONCTIONS ++&+ SUR CANAL+////////////////////////////////////////////



      SDL_PumpEvents();
      const Uint8 *state = SDL_GetKeyboardState(NULL);      //Vérification de quelles sont les touche qui sont enfoncé sur le clavier

      for(int i = 0; i < 1000; i++) {

        if(state[i]) {

           clavier[i].enfonce = 1;

         } else {

           clavier[i].enfonce = 0;

         }

      }


      //////////////////////////////////////FONCTIONS AUTOMATIQUE DURANT LE COMBAT////////////////////////////////////////////
      mortalKombat();


      afficherCombat();




      gererTexte(camera);

      gererEnnemis(ennemis, &nbEnnemi, equipe);

      while(nbEnnemi == 0) {

        victoire(screen, ennemis, &nbEnnemi);

      }



      SDL_UpdateWindowSurface(screen);

      for(int i = 0; i < 1000; i++) {

        if(state[i]) clavier[i].relache = 0;
        else clavier[i].relache = 1;

      }

      if(clavier[SDL_SCANCODE_N].enfonce) quit = 1;

      SDL_PollEvent(&event);

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

      if(coop) {

        pthread_mutex_lock (&mutex); /* On verrouille le mutex */

        pthread_cond_signal (&condition); /* On délivre le signal : condition remplie */

        pthread_mutex_unlock (&mutex); /* On déverrouille le mutex */

      }

      if(delai > 0) {

        SDL_Delay(delai);

      }

      system("clear");


    }



    freeAll();


    return 0;

}
