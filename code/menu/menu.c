#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "../combat/const.h"

const int tailleBouton = 100;
const int decallage = 15;



void affichage(SDL_Rect jeu, SDL_Rect option, SDL_Rect quitter, SDL_Rect choix, SDL_Surface* pSurface, SDL_Window* screen){

  SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

  SDL_FillRect(pSurface, &jeu, SDL_MapRGB(pSurface->format, 255, 255, 255));
  SDL_FillRect(pSurface, &option, SDL_MapRGB(pSurface->format, 255, 255, 255));
  SDL_FillRect(pSurface, &quitter, SDL_MapRGB(pSurface->format, 255, 255, 255));

  SDL_FillRect(pSurface, &choix, SDL_MapRGB(pSurface->format, 255, 0, 0));
  SDL_UpdateWindowSurface(screen);
}

int main(int argc, char** argv){
affichage(jeu, option, quitter, choix, pSurface);
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* screen = SDL_CreateWindow("Menu - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

  //TTF_Font *police = NULL;
  //police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);

  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);

  int quit = 0;
  int fin = 0;
  int recupCurs = 0;
  int debut = 0;
  int fpsCount = 0;

  int nbChoix = 0;
  int decallageBouton = tailleBouton+decallage;

  SDL_Rect jeu = {0,0*decallageBouton,tailleBouton,tailleBouton};
  SDL_Rect option = {0,1*decallageBouton,tailleBouton,tailleBouton};
  SDL_Rect quitter = {0,2*decallageBouton,tailleBouton,tailleBouton};
  SDL_Rect choix = {0,nbChoix*decallage,tailleBouton,tailleBouton};

  SDL_Event event;

  //  SDL_BlitSurface(TTF_RenderText_Solid(police, "Jeu", couleur), NULL, pSurface, &jeu);
  //  TTF_CloseFont(police);


  affichage(jeu, option, quitter, choix, pSurface, screen);

  while(!quit){

    debut = SDL_GetTicks();

    SDL_PollEvent(&event);
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);


    if(recupCurs-- < 0){

      if(state[SDL_SCANCODE_S]){

        nbChoix++;
        if(nbChoix == 3) nbChoix = 0;

        choix.y = nbChoix*decallageBouton;

        affichage(jeu, option, quitter, choix, pSurface, screen);

        recupCurs = DELAI_CURSEUR;
      }

      if(state[SDL_SCANCODE_W]){

        nbChoix--;
        if(nbChoix == -1) nbChoix = 2;

        choix.y = nbChoix*decallageBouton;

        affichage(jeu, option, quitter, choix, pSurface, screen);

        recupCurs = DELAI_CURSEUR;

      }
    }

      switch(event.type){
        case SDL_QUIT:
          quit = 1;
          break;
      }

    fin = SDL_GetTicks();

    printf("\nfps = %i\n", (fpsCount++)*1000/SDL_GetTicks());
    printf("fpsCount = %i\n", fpsCount);
    printf("fin = %i\n", fin);
    int delai = ((1000/FPS)-(fin-debut));

    if(delai > 0){
      SDL_Delay(delai);
    }

  }
}
