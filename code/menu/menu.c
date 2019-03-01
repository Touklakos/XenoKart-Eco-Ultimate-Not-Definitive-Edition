#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "../combat/const.h"

int main(int argc, char** argv){

  int quit = 0;
  int fin = 0;
  int recupCurs = 0;
  int debut = 0;
  int fpsCount = 0;

  int tailleBouton = 100;


  int decallage = 15;
  int decallageBouton = tailleBouton+decallage;
  int nbChoix = 0;

  SDL_Event event;

  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  IMG_Init(IMG_INIT_PNG);

  SDL_Window* screen = SDL_CreateWindow("Menu - XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

  TTF_Font *police = NULL;
  police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);

  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);

  SDL_Rect jeu = {0,0*decallageBouton,tailleBouton,tailleBouton};
  SDL_Rect option = {0,1*decallageBouton,tailleBouton,tailleBouton};
  SDL_Rect credit = {0,2*decallageBouton,tailleBouton,tailleBouton};
  SDL_Rect quitter = {0,3*decallageBouton,tailleBouton,tailleBouton};

  SDL_Rect choix = {0,nbChoix*decallage,tailleBouton,tailleBouton};


  SDL_FillRect(pSurface, &jeu, SDL_MapRGB(pSurface->format, 255, 255, 255));
  SDL_FillRect(pSurface, &option, SDL_MapRGB(pSurface->format, 255, 255, 255));
  SDL_FillRect(pSurface, &credit, SDL_MapRGB(pSurface->format, 255, 255, 255));
  SDL_FillRect(pSurface, &quitter, SDL_MapRGB(pSurface->format, 255, 255, 255));

  //SDL_BlitSurface(TTF_RenderText_Solid(police, "Jeu", couleur), NULL, pSurface, &dest);
  TTF_CloseFont(police);


  SDL_FillRect(pSurface, &choix, SDL_MapRGB(pSurface->format, 255, 0, 0));



  SDL_UpdateWindowSurface(screen);

  while(!quit){

    debut = SDL_GetTicks();

    SDL_PollEvent(&event);
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);


    if(recupCurs-- < 0){

      if(state[SDL_SCANCODE_S]){

        nbChoix++;
        if(nbChoix == 4) nbChoix = 0;

        choix.y = nbChoix*decallageBouton;

        SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

        SDL_FillRect(pSurface, &jeu, SDL_MapRGB(pSurface->format, 255, 255, 255));
        SDL_FillRect(pSurface, &option, SDL_MapRGB(pSurface->format, 255, 255, 255));
        SDL_FillRect(pSurface, &credit, SDL_MapRGB(pSurface->format, 255, 255, 255));
        SDL_FillRect(pSurface, &quitter, SDL_MapRGB(pSurface->format, 255, 255, 255));

        SDL_FillRect(pSurface, &choix, SDL_MapRGB(pSurface->format, 255, 0, 0));
        SDL_UpdateWindowSurface(screen);

        recupCurs = DELAI_CURSEUR;
      }

      if(state[SDL_SCANCODE_W]){

        nbChoix--;
        if(nbChoix == -1) nbChoix = 3;

        choix.y = nbChoix*decallageBouton;


        SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

        SDL_FillRect(pSurface, &jeu, SDL_MapRGB(pSurface->format, 255, 255, 255));
        SDL_FillRect(pSurface, &option, SDL_MapRGB(pSurface->format, 255, 255, 255));
        SDL_FillRect(pSurface, &credit, SDL_MapRGB(pSurface->format, 255, 255, 255));
        SDL_FillRect(pSurface, &quitter, SDL_MapRGB(pSurface->format, 255, 255, 255));

        SDL_FillRect(pSurface, &choix, SDL_MapRGB(pSurface->format, 255, 0, 0));
        SDL_UpdateWindowSurface(screen);

        recupCurs = DELAI_CURSEUR;

      }
    }

      switch(event.type){
        case SDL_QUIT:
          quit = 1;
          break;
      }

    fin = SDL_GetTicks();

    printf("\nfps = %lld\n", (fpsCount++)*1000/SDL_GetTicks());
    printf("fpsCount = %lld\n", fpsCount);
    printf("fin = %lld\n", fin);
    int delai = ((1000/FPS)-(fin-debut));

    if(delai > 0){
      SDL_Delay(delai);
    }

  }
}
