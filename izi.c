#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>





#include "code/menu/menu.h"
#include "code/combat/ennemi.h"
#include "code/lobby/fonctions.h"

#include "code/combat/fonctionMain.c"



int main(int argc, char** argv){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  TTF_Font *police = NULL;
  police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);

  screen = SDL_CreateWindow("XenoKart ECO+ (Not) Definitive Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  pSurface = SDL_GetWindowSurface(screen);

  int recupCurs = 0;

  int nbChoix = 0;
  int decallageBouton = BUTTON_HEIGHT+DEC;

  int tailletab = 4;

  SDL_Rect jeu = {(SCREEN_WIDTH/2)-(BUTTON_WIDTH)/2,0*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2),BUTTON_WIDTH,BUTTON_HEIGHT}; //definition des rectangles, avec calcul sur la taille de l'cran afin de les centrés
  SDL_Rect option = {(SCREEN_WIDTH/2)-(BUTTON_WIDTH)/2,1*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2),BUTTON_WIDTH,BUTTON_HEIGHT};
  SDL_Rect quitter = {(SCREEN_WIDTH/2)-(BUTTON_WIDTH)/2,2*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2),BUTTON_WIDTH,BUTTON_HEIGHT};
  SDL_Rect choix = {(SCREEN_WIDTH/2)-(BUTTON_WIDTH)/2,nbChoix*DEC+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2),BUTTON_WIDTH,BUTTON_HEIGHT};


  affichage tab[4];
  tab[0].rec = choix;
  tab[1].rec = jeu;
  tab[2].rec = option;
  tab[3].rec = quitter;

  tab[1].txt = TTF_RenderText_Solid(police, "GAME", noir);
  tab[2].txt = TTF_RenderText_Solid(police, "OPTIONS", noir);
  tab[3].txt = TTF_RenderText_Solid(police, "QUIT", noir);




  int argent=20000;
  int points=0;
  int etat = 0;
  int type_expedition;
  t_objet inv[nbObjets];
  load_inv(inv);




  coop = 0;
  serveur = 0;
  if(argc == 3) serveur = 1;

  indicePersonnage = 0;       //variable qui indique quel personnage on est entrain de controller

  if(coop) connexion();

  srand(time(NULL));

  initJeu();

  for(int i = 0; i< 1000; i++) {

    clavier[i].enfonce = 0;
    clavier[i].relache = 0;

  }


  etatProg = menu;


  while(!quit){

    fprintf(stderr, "etatProg : %d\n", etatProg);

    if(etatProg == menu) {

      afficher(tab, tailletab, pSurface, screen, police);

      deb = SDL_GetTicks();

      SDL_PumpEvents();
      const Uint8 *state = SDL_GetKeyboardState(NULL);


      if(recupCurs-- < 0){ //permet la gestion de l'appuie des touches

        if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]){
          nbChoix++;
          if(nbChoix == 3) nbChoix = 0;

          tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2);

          afficher(tab, tailletab, pSurface, screen, police);

          recupCurs = DELAI_CURSEUR;
        }
        if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]){
          nbChoix--;
          if(nbChoix == -1) nbChoix = 2;

          tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2);

          afficher(tab, tailletab, pSurface, screen, police);

          recupCurs = DELAI_CURSEUR;
        }

        if(state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE]){
          while(state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE]) {SDL_PumpEvents(); state = SDL_GetKeyboardState(NULL);};
          switch(nbChoix){
            case 0 : fonctionJeu(pSurface, screen, police); break;
            case 1 : break;
            case 2 : quit = 2; break;
          }
        }
      }
      fonctionFin();
      fonctionQuitter();


    } else if(etatProg == lobby) {

      SDL_PollEvent(&event);



      SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

      switch (etat){
        case 0 : if(!inv_vide(inv)){echange(screen, inv, &argent, &points);} break;
        case 1 : type_expedition = expedition(screen); break;
        case 2 : commerce(screen, inv, &argent); break;

      }
      etat++;



      printf("test2\n");


      if(etat == 3){
        etatProg = combat;
      }

    } else if(etatProg == map) {



    } else if(etatProg == combat) {


      //////////////////////////////////////FONCTIONS D'AFFICHAGE DES FPS, DU BACKGROUND////////////////////////////////////////////


      deb = SDL_GetTicks();

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

      gererEnnemis();

      if(nbEnnemi == 0) {

        victoire();

        etatProg = map;

      }


      if(equipe[0]->PV <= 0 && equipe[1]->PV <= 0 && equipe[2]->PV <= 0) {

        defaite();

        etatProg = map;

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

      int delai;

      fin = SDL_GetTicks();

      printf("\nfps = %lld\n", (fpsCount++)*1000/SDL_GetTicks());

      printf("fpsCount = %lld\n", fpsCount);

      printf("fin = %lld\n", fin);

      delai = ((1000/FPS)-(fin-deb));

      do {

        if(coop) {

          pthread_mutex_lock(&mutex); /* On verrouille le mutex */

          pthread_cond_signal(&condition); /* On délivre le signal : condition remplie */

          pthread_mutex_unlock(&mutex); /* On déverrouille le mutex */

        }

        fin = SDL_GetTicks();

        delai = ((1000/FPS)-(fin-deb));


      } while(delai > 0);

      system("clear");

    }

  }

  switch(quit){
    case 1 : printf("Programme fermé par la croix\n"); break;
    case 2 : printf("Programme fermé par le bouton\n"); break;
  }

  SDL_FreeSurface(tab[1].txt);
  SDL_FreeSurface(tab[2].txt);
  SDL_FreeSurface(tab[3].txt);

  TTF_CloseFont(police);

  freeAll();


}
