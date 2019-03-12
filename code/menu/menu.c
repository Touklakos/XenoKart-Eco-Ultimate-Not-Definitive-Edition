#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "../combat/const.h"

#define N 4

int fpsCount = 0;
int fin = 0;
int deb = 0;
int quit = 0;

SDL_Event event;
SDL_Color blanc = {255,255,255};
SDL_Color noir = {0,0,0};

/**
  \file menu.c
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

/**
    \fn void afficher(affichage tab[], int tTab, SDL_Surface* pSurface, SDL_Window* screen, TTF_Font *police)
    \brief fonction qui affiche toutes la SDL ( Rectangle et texte pour le menu )
    \param tab Tableau qui contient les rectangles et les textes contenu dans une structure affichage (SDL_Rect, SDL_Surface*)
    \param tTab Taille du tableau
    \param pSurface Surface sur laquel on affiche
    \param screen Ecran sur lequel on affiche
    \param police Police d'écriture
*/

void afficher(affichage tab[], int tTab, SDL_Surface* pSurface, SDL_Window* screen, TTF_Font *police){

  SDL_Rect rect;

  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

  for(int i = 1; i < tTab; i++){
      SDL_FillRect(pSurface, &tab[i].rec, SDL_MapRGB(pSurface->format, 255, 255, 255));
  }

  SDL_FillRect(pSurface, &tab[0].rec, SDL_MapRGB(pSurface->format, 255, 0, 0));

  for(int i = 1; i < tTab; i++){
      rect = tab[i].rec;
      rect.x = rect.x+tab[i].rec.w/2 - tab[i].txt->w/2;
      rect.y = rect.y+tab[i].rec.h/2 - tab[i].txt->h/2;
      SDL_BlitSurface(tab[i].txt, NULL, pSurface, &test);
  }
  SDL_UpdateWindowSurface(screen);
}

/**
    \fn fonctionJeu(SDL_Surface* pSurface, SDL_Window* screen, TTF_Font *police)
    \brief fonction qui gère quand l'user va sur "GAME"
    \param pSurface Surface sur laquel on affiche
    \param screen Ecran sur lequel on affiche
    \param police Police d'écriture
*/

void fonctionJeu(SDL_Surface* pSurface, SDL_Window* screen, TTF_Font *police){

  int decallageBouton = BUTTON_HEIGHT+DEC;
  int recupCurs = 0;
  int nbChoix = 0;

  int tailletab = 3;

  SDL_Rect nouveau = {(SCREEN_WIDTH/2)-(BUTTON_WIDTH)/2,1*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2),BUTTON_WIDTH,BUTTON_HEIGHT}; //definition des rectangles, avec calcul sur la taille de l'cran afin de les centrés
  SDL_Rect charger = {(SCREEN_WIDTH/2)-(BUTTON_WIDTH)/2,0*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2),BUTTON_WIDTH,BUTTON_HEIGHT};
  SDL_Rect choix = {(SCREEN_WIDTH/2)-(BUTTON_WIDTH)/2,nbChoix*DEC+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2),BUTTON_WIDTH,BUTTON_HEIGHT};

  affichage tab[tailletab];
  tab[0].rec = choix;
  tab[1].rec = charger;
  tab[1].txt = TTF_RenderText_Solid(police, "LOAD SAVE", noir);
  tab[2].rec = nouveau;
  tab[2].txt = TTF_RenderText_Solid(police, "NEW SAVE", noir);

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  while(!quit){

    deb = SDL_GetTicks();

    afficher(tab, tailletab, pSurface, screen, police);
    SDL_PumpEvents();

    if(recupCurs-- < 0){ //permet la gestion de l'appuie des touches

      if(state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]){
        nbChoix++;
        if(nbChoix == 2) nbChoix = 0;
        tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2);
        afficher(tab, tailletab, pSurface, screen, police);
        recupCurs = DELAI_CURSEUR;
      }

      if(state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]){
        nbChoix--;
        if(nbChoix == -1) nbChoix = 1;
        tab[0].rec.y = nbChoix*decallageBouton+SCREEN_HEIGHT/2-((tailletab-1)*decallageBouton/2);
        afficher(tab, tailletab, pSurface, screen, police);
        recupCurs = DELAI_CURSEUR;
      }

      if(state[SDL_SCANCODE_RETURN] || state[SDL_SCANCODE_SPACE]){
        switch(nbChoix){
          case 0 : printf("LOAD\n");break;
          case 1 : printf("NEW\n");break;
        }
      }

      if(state[SDL_SCANCODE_BACKSPACE] || state[SDL_SCANCODE_ESCAPE]){
        return;
      }

    }
    fonctionFin();
    fonctionQuitter();
  }
}

int main(int argc, char** argv){

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  TTF_Font *police = NULL;
  police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);

  SDL_Window* screen = SDL_CreateWindow("Menu - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Surface* pSurface = NULL;
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

  while(!quit){

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
        switch(nbChoix){
          case 0 : fonctionJeu(pSurface, screen, police); break;
          case 1 : break;
          case 2 : quit = 2; break;
        }
      }
    }
    fonctionFin();
    fonctionQuitter();
  }
  switch(quit){
    case 1 : printf("Programme fermé par la croix\n"); break;
    case 2 : printf("Programme fermé par le bouton\n"); break;
  }
}
