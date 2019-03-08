#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "../combat/const.h"

#define N 4

int hauteurBouton = 100;
int largeurBouton = 100;

int decallage = 15;

int fpsCount = 0;
int fin = 0;
int debut = 0;

int quit = 0;

SDL_Event event;

void fonctionQuitter(){
  SDL_PollEvent(&event);

  switch(event.type){
      case SDL_QUIT:
        quit = 1;
        break;
  }
}

void fonctionFin(){
  fin = SDL_GetTicks();

  printf("\nfps = %i\n", (fpsCount++)*1000/SDL_GetTicks());
  printf("fin = %i\n", fin/1000);
  int delai = ((1000/FPS)-(fin-debut));

  if(delai > 0){
    SDL_Delay(delai);
  }
}

void afficher(SDL_Rect tab[], SDL_Surface* pSurface, SDL_Window* screen){

  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

  for(int i = 1; i < N; i++){
      SDL_FillRect(pSurface, &tab[i], SDL_MapRGB(pSurface->format, 255, 255, 255));
  }
  SDL_FillRect(pSurface, &tab[0], SDL_MapRGB(pSurface->format, 255, 0, 0));
  SDL_UpdateWindowSurface(screen);
}

void fonctionJeu(SDL_Surface* pSurface, SDL_Window* screen){

  int decallageBouton = hauteurBouton+decallage;
  int recupCurs = 0;
  int nbChoix = 0;


  SDL_Rect nouveau = {0,0*decallageBouton,hauteurBouton,largeurBouton};
  SDL_Rect charger = {0,1*decallageBouton,hauteurBouton,largeurBouton};
  SDL_Rect choix = {0,nbChoix*decallage,hauteurBouton,largeurBouton};

  SDL_Rect tab[N];
  tab[0] = choix;
  tab[1] = charger;
  tab[2] = nouveau;

  const Uint8 *state = SDL_GetKeyboardState(NULL);

  while(!quit){

    debut = SDL_GetTicks();

    afficher(tab, pSurface, screen);
    SDL_PumpEvents();

    if(recupCurs-- < 0){

      if(state[SDL_SCANCODE_S]){
        nbChoix++;
        if(nbChoix == 2) nbChoix = 0;
        tab[0].y = nbChoix*decallageBouton;
        afficher(tab, pSurface, screen);
        recupCurs = DELAI_CURSEUR;
      }

      if(state[SDL_SCANCODE_W]){
        nbChoix--;
        if(nbChoix == -1) nbChoix = 1;
        tab[0].y = nbChoix*decallageBouton;
        afficher(tab, pSurface, screen);
        recupCurs = DELAI_CURSEUR;
      }

      if(state[SDL_SCANCODE_E]){
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

  SDL_Window* screen = SDL_CreateWindow("Menu - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  //TTF_Font *police = NULL;
  //police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);

  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);

  int recupCurs = 0;

  int nbChoix = 0;
  int decallageBouton = hauteurBouton+decallage;

  SDL_Rect jeu = {0,0*decallageBouton,hauteurBouton,largeurBouton};
  SDL_Rect option = {0,1*decallageBouton,hauteurBouton,largeurBouton};
  SDL_Rect quitter = {0,2*decallageBouton,hauteurBouton,largeurBouton};
  SDL_Rect choix = {0,nbChoix*decallage,hauteurBouton,largeurBouton};


  SDL_Rect tab[N];
  tab[0] = choix;
  tab[1] = jeu;
  tab[2] = option;
  tab[3] = quitter;    fonctionFin();


  while(!quit){

    afficher(tab, pSurface, screen);

    debut = SDL_GetTicks();

    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);


    if(recupCurs-- < 0){
      if(state[SDL_SCANCODE_S]){
        nbChoix++;
        if(nbChoix == 3) nbChoix = 0;

        tab[0].y = nbChoix*decallageBouton;

        afficher(tab, pSurface, screen);

        recupCurs = DELAI_CURSEUR;
      }
      if(state[SDL_SCANCODE_W]){
        nbChoix--;
        if(nbChoix == -1) nbChoix = 2;

        tab[0].y = nbChoix*decallageBouton;

        afficher(tab, pSurface, screen);

        recupCurs = DELAI_CURSEUR;
      }

      if(state[SDL_SCANCODE_Q]){
        switch(nbChoix){
          case 0 : fonctionJeu(pSurface, screen); break;
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
