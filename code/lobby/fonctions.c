#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "fonctions.h"
#include "../combat/const.h"

void load_inv(t_objet inv[nbObjets]){
  //temporaire jusqu a chargement de sauvegardes
  strcpy(inv[0].nom, "pagne");
  inv[0].nombre = 10;
  inv[0].valeurArgent = 1;
  inv[0].valeurPoints = 10;
  strcpy(inv[1].nom, "vhs");
  inv[1].nombre = 20;
  inv[1].valeurArgent = 5;
  inv[1].valeurPoints = 2;
  inv[2].nombre = NULL;
}



void echange(SDL_Window * screen, t_objet inv[nbObjets], int *argent, int *points){

  TTF_Font *police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);

  int i = 0;
  int test_touche=0;
  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);
  SDL_Rect dest;
  SDL_Surface * texte;
  SDL_Color c = {0,0,0};
  SDL_Color vert = {0,200,0};
  char string[20];
  int objets_gardes = 0;
  printf("échange des loots\n");
  do{
    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 70, 70, 70));
    do{
      SDL_PumpEvents();
      const Uint8 *state = SDL_GetKeyboardState(NULL);      //Vérification de quelles sont les touche qui sont enfoncé sur le clavier


      test_touche = 0;

      texte = TTF_RenderText_Solid(police, inv[i].nom, c);
      dest.x = SCREEN_WIDTH/2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/2 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);

      sprintf(string, "nombre : %i", inv[i].nombre - objets_gardes);
      texte = TTF_RenderText_Solid(police, string, c);
      dest.x = SCREEN_WIDTH/2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/2 + texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);

      texte = TTF_RenderText_Solid(police, "upload (1)", c);
      dest.x = SCREEN_WIDTH/3 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3*2 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);

      texte = TTF_RenderText_Solid(police, "garder (2)", c);
      dest.x = SCREEN_WIDTH/2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3*2 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);

      texte = TTF_RenderText_Solid(police, "vendre (3)", c);
      dest.x = SCREEN_WIDTH/3*2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3*2 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);

      sprintf(string, "score : %i", *points);
      texte = TTF_RenderText_Solid(police, string, c);
      dest.x = SCREEN_WIDTH/3 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);

      sprintf(string, "argents : %i", *argent);
      texte = TTF_RenderText_Solid(police, string, c);
      dest.x = SCREEN_WIDTH/3*2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);

      //test des touches
      if(state[SDL_SCANCODE_1]){
        while(state[SDL_SCANCODE_1]){SDL_PumpEvents();}
        test_touche++;
        inv[i].nombre--;
        *points += inv[i].valeurPoints;
      }
      if(state[SDL_SCANCODE_2]){
        while(state[SDL_SCANCODE_2]){SDL_PumpEvents();}
        test_touche++;
        objets_gardes++;
      }
      if(state[SDL_SCANCODE_3]){
        while(state[SDL_SCANCODE_3]){SDL_PumpEvents();}
        test_touche++;
        inv[i].nombre--;
        *argent += inv[i].valeurArgent;
      }

      SDL_UpdateWindowSurface(screen);
    }while(!test_touche);
    if(!inv[i].nombre || inv[i].nombre == objets_gardes){
      i++;
      objets_gardes = 0;
    }
  }while(i < nbObjets);
  SDL_FreeSurface(texte);

  TTF_CloseFont(police);

}

int expedition(SDL_Window * screen){
  TTF_Font *police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);
  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);
  SDL_Rect dest;
  SDL_Color c = {0,0,0};
  SDL_Surface * map = NULL;
  map = IMG_Load("./data/map.png");
  SDL_Surface * flag = NULL;
  flag = IMG_Load("./data/flag.png");
  int test_touche = 0;
  int i = 0;
  SDL_Surface * texte[4];
  texte[0] = TTF_RenderText_Solid(police, "Jungle", c);
  texte[1] = TTF_RenderText_Solid(police, "Dans les etoileuuuuh", c);
  texte[2] = TTF_RenderText_Solid(police, "Foret de Schlihpak", c);
  texte[3] = TTF_RenderText_Solid(police, "Derriere les rochers", c);
  printf("choix d'expedition");
  do{
    i %= 4;
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    dest.x = 0;
    dest.y = 0;
    SDL_BlitSurface(map, NULL, pSurface, &dest);
    dest.x = SCREEN_WIDTH/4 -50;
    dest.y = SCREEN_HEIGHT/4 +25;
    SDL_BlitSurface(flag, NULL, pSurface, &dest);
    dest.x = SCREEN_WIDTH/4*3;
    dest.y = SCREEN_HEIGHT/4;
    SDL_BlitSurface(flag, NULL, pSurface, &dest);
    dest.x = SCREEN_WIDTH/4 + 100;
    dest.y = SCREEN_HEIGHT/2 + 30;
    SDL_BlitSurface(flag, NULL, pSurface, &dest);
    dest.x = SCREEN_WIDTH/2 + flag->w/2;
    dest.y = SCREEN_HEIGHT/2 - flag->h;
    SDL_BlitSurface(flag, NULL, pSurface, &dest);

    switch (i) {
      case 0 :
        dest.x = SCREEN_WIDTH/4 -50;
        dest.y = SCREEN_HEIGHT/4 +25;
        SDL_BlitSurface(texte[i], NULL, pSurface, &dest);
        break;
      case 1 :
        dest.x = SCREEN_WIDTH/4*3;
        dest.y = SCREEN_HEIGHT/4;
        SDL_BlitSurface(texte[i], NULL, pSurface, &dest);
        break;
      case 2 :
        dest.x = SCREEN_WIDTH/4 + 100;
        dest.y = SCREEN_HEIGHT/2 + 30;
        SDL_BlitSurface(texte[i], NULL, pSurface, &dest);
        break;
      case 3 :
        dest.x = SCREEN_WIDTH/2 + flag->w/2;
        dest.y = SCREEN_HEIGHT/2 - flag->h;
        SDL_BlitSurface(texte[i], NULL, pSurface, &dest);
        break;
    }

    if(state[SDL_SCANCODE_RETURN]){
      while(state[SDL_SCANCODE_RETURN]){SDL_PumpEvents();}
      test_touche++;
    }
    if(state[SDL_SCANCODE_RIGHT]){
      while(state[SDL_SCANCODE_RIGHT]){SDL_PumpEvents();}
      i++;
    }
    if(state[SDL_SCANCODE_LEFT]){
      while(state[SDL_SCANCODE_LEFT]){SDL_PumpEvents();}
      i+=3;
    }

    SDL_UpdateWindowSurface(screen);
  }while(!test_touche);
  return i;
}
