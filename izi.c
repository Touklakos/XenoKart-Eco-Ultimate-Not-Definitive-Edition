#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>





#include "code/menu/menu.h"
#include "code/lobby/fonctions.h"
#include "code/map/map.h"

#include "code/combat/fonctionMain.h"



int main(int argc, char** argv){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  TTF_Font *police = NULL;
  police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);

  screen = SDL_CreateWindow("XenoKart ECO+ Ultimate (Not) Definitive Edition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

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


  map_t * map;
  map = NULL;


  int mouseX, mouseY;
  SDL_Event e;
  SDL_Surface * perso = NULL;
  perso = IMG_Load("./data/miniGuts.png");
  Personnage guts;
  initPersonnage(&guts, "./data/Guts.txt");
  case_t *pos;
  pos = malloc(sizeof(pos));
  pos->coord.x = 25; pos->coord.y = 25;
  camera.x = pos->coord.x;
  camera.y = pos->coord.y;
  camera.w = SCREEN_WIDTH/2;
  camera.h = SCREEN_HEIGHT/2;


  coop = 0;
  serveur = 0;

  indicePersonnage = 0;       //variable qui indique quel personnage on est entrain de controller

  nbEnnemi = 0;


  srand(time(NULL));

  initJeu();

  for(int i = 0; i< 1000; i++) {

    clavier[i].enfonce = 0;
    clavier[i].relache = 0;

  }




  etatProg = menu;


  while(!quit){

    if(etatProg == menu) {

      #include "code/menu/menuUtilisation.c"


    } else if(etatProg == connecte) {

      #include "code/combat/connexion.c"

    } else if(etatProg == lobby) {

      #include "code/lobby/lobbyUtilisation.c"


    } else if(etatProg == creationMap) {

      #include "code/map/mapCreation.c"


    } else if(etatProg == UtilisationMap) {

      #include "code/map/mapUtilisation.c"


    } else if(etatProg == initialisationCombat) {


      #include "code/combat/combatInit.c"


    } else if(etatProg == combat) {


      #include "code/combat/combatUtilisation.c"


    }

  }

  switch(quit){
    case 1 : printf("Programme fermé par la croix\n"); break;
    case 2 : printf("Programme fermé par le bouton\n"); break;
  }

  SDL_FreeSurface(tab[1].txt);
  SDL_FreeSurface(tab[2].txt);
  SDL_FreeSurface(tab[3].txt);
  SDL_FreeSurface(perso);

  SDL_FreeSurface(guts.image);

  free(map);
  free(pos);

  TTF_CloseFont(police);

  freeAll();


}
