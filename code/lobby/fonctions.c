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
  inv[0].nombre = 0;
  inv[0].valeurArgent = 1;
  inv[0].valeurPoints = 10;
  strcpy(inv[1].nom, "vhs");
  inv[1].nombre = 1;
  inv[1].valeurArgent = 5;
  inv[1].valeurPoints = 2;
  strcpy(inv[2].nom, "love");
  inv[2].nombre = 0;
  inv[2].valeurArgent = 2900;
  inv[2].valeurPoints = 8000;
  strcpy(inv[3].nom, "machette");
  inv[3].nombre = 0;
  inv[3].valeurArgent = 5;
  inv[3].valeurPoints = 0;
  strcpy(inv[4].nom, "corde");
  inv[4].nombre = 0;
  inv[4].valeurArgent = 5;
  inv[4].valeurPoints = 0;
  strcpy(inv[5].nom, "raquettes");
  inv[5].nombre = 0;
  inv[5].valeurArgent = 5;
  inv[5].valeurPoints = 0;
  strcpy(inv[6].nom, "materiel d'escalade");
  inv[6].nombre = 0;
  inv[6].valeurArgent = 5;
  inv[6].valeurPoints = 0;
  strcpy(inv[7].nom, "burger");
  inv[7].nombre = 0;
  inv[7].valeurArgent = 5;
  inv[7].valeurPoints = 0;
}

void load_vendeur(t_objet inv[nbObjets]){
  //temporaire jusqu a chargement de sauvegardes
  strcpy(inv[0].nom, "pagne");
  inv[0].nombre = 10;
  inv[0].valeurArgent = 1;
  inv[0].valeurPoints = 10;
  strcpy(inv[1].nom, "vhs");
  inv[1].nombre = 20;
  inv[1].valeurArgent = 5;
  inv[1].valeurPoints = 2;
  strcpy(inv[2].nom, "love");
  inv[2].nombre = 1;
  inv[2].valeurArgent = 2900;
  inv[2].valeurPoints = 8000;
  strcpy(inv[3].nom, "machette");
  inv[3].nombre = 0;
  inv[3].valeurArgent = 5;
  inv[3].valeurPoints = 0;
  strcpy(inv[4].nom, "corde");
  inv[4].nombre = 0;
  inv[4].valeurArgent = 5;
  inv[4].valeurPoints = 0;
  strcpy(inv[5].nom, "raquettes");
  inv[5].nombre = 0;
  inv[5].valeurArgent = 5;
  inv[5].valeurPoints = 0;
  strcpy(inv[6].nom, "materiel d'escalade");
  inv[6].nombre = 0;
  inv[6].valeurArgent = 5;
  inv[6].valeurPoints = 0;
  strcpy(inv[7].nom, "burger");
  inv[7].nombre = 0;
  inv[7].valeurArgent = 5;
  inv[7].valeurPoints = 0;
}

int inv_vide(t_objet inv[nbObjets]){
  for(int i = 0; i<nbObjets; i++){
    if(inv[i].nombre){
      return 0;
    }
  }
  return 1;
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
  char string[20];
  int objets_gardes = 0;
  printf("échange des loots\n");
  while(!inv[i].nombre && i<nbObjets){
    i++;
  }
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
      SDL_FreeSurface(texte);

      sprintf(string, "nombre : %i", inv[i].nombre - objets_gardes);
      texte = TTF_RenderText_Solid(police, string, c);
      dest.x = SCREEN_WIDTH/2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/2 + texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);
      SDL_FreeSurface(texte);

      texte = TTF_RenderText_Solid(police, "upload (1)", c);
      dest.x = SCREEN_WIDTH/3 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3*2 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);
      SDL_FreeSurface(texte);

      texte = TTF_RenderText_Solid(police, "garder (2)", c);
      dest.x = SCREEN_WIDTH/2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3*2 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);
      SDL_FreeSurface(texte);

      texte = TTF_RenderText_Solid(police, "vendre (3)", c);
      dest.x = SCREEN_WIDTH/3*2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3*2 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);
      SDL_FreeSurface(texte);

      sprintf(string, "score : %i", *points);
      texte = TTF_RenderText_Solid(police, string, c);
      dest.x = SCREEN_WIDTH/3 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);
      SDL_FreeSurface(texte);

      sprintf(string, "argents : %i", *argent);
      texte = TTF_RenderText_Solid(police, string, c);
      dest.x = SCREEN_WIDTH/3*2 - texte->w/2;
      dest.y = SCREEN_HEIGHT/3 - texte->h/2;
      SDL_BlitSurface(texte, NULL, pSurface, &dest);
      SDL_FreeSurface(texte);

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
    while(!inv[i].nombre || inv[i].nombre == objets_gardes){
      i++;
      objets_gardes = 0;
    }
  }while(i < nbObjets);

  TTF_CloseFont(police);

}

int expedition(SDL_Window * screen){
  TTF_Font *police = TTF_OpenFont("./data/DejaVuSans.ttf", 15);
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
  SDL_FreeSurface(map);
  SDL_FreeSurface(flag);
  SDL_FreeSurface(texte[0]);
  SDL_FreeSurface(texte[1]);
  SDL_FreeSurface(texte[2]);
  SDL_FreeSurface(texte[3]);
  TTF_CloseFont(police);
  return i;
}

void afficher_inv(SDL_Window * screen, int x, int y, int w, int h, t_objet inv[nbObjets]){
  TTF_Font *police = TTF_OpenFont("./data/DejaVuSans.ttf", 15);
  SDL_Surface * texte;
  char nb[10];
  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);
  SDL_Color c = {0,0,0};
  SDL_Rect rect;
  SDL_Rect emplacement;
  int i, j;
  rect.x = x;
  rect.y = y;
  rect.h = h;
  rect.w = w;
  SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 80,80,80));
  for(i = 0; i<2; i++){
    for(j = 0; j<10; j++){
      emplacement.x = 20 + j*122 + x;
      emplacement.y = 30 + i*140 + y;
      emplacement.h = 100;
      emplacement.w = 100;
      SDL_FillRect(pSurface, &emplacement, SDL_MapRGB(pSurface->format, 200,200,200));
    }
  }
  int k = 0;
  for(i = 0; i<2; i++){
    for(j = 0; k<nbObjets && j<10; j++){
      emplacement.x = 20 + j*122 + x;
      emplacement.y = 30 + i*140 + y;
      emplacement.h = 100;
      emplacement.w = 100;
      if(inv[k].nombre){
        texte = TTF_RenderText_Solid(police, inv[k].nom, c);
        SDL_BlitSurface(texte, NULL, pSurface, &emplacement);
        sprintf(nb, "x%i", inv[k].nombre);
        SDL_FreeSurface(texte);
        texte = TTF_RenderText_Solid(police, nb, c);
        emplacement.y+=50;
        SDL_BlitSurface(texte, NULL, pSurface, &emplacement);
        SDL_FreeSurface(texte);

      }
      else{
        j--;
      }
      k++;
    }
  }
  //SDL_FreeSurface(texte);
  TTF_CloseFont(police);
}

void commerce(SDL_Window * screen, t_objet inv[nbObjets], int *argent){
  t_objet vendeur[nbObjets];
  load_vendeur(vendeur);
  TTF_Font *police = TTF_OpenFont("./data/DejaVuSans.ttf", 15);
  SDL_Surface * texte;
  char string[20];
  SDL_Color blanc = {200,200,200};
  SDL_Surface* pSurface = NULL;
  pSurface = SDL_GetWindowSurface(screen);
  SDL_Surface * select = NULL;
  select = IMG_Load("./data/select.png");
  SDL_Rect dest;
  int i = 0, j = 0, i_inv = 0, compteurBoucle = 0;
  int test_touche = 0;
  while(!vendeur[i_inv].nombre && i_inv<nbObjets){
    i_inv++;
  }
  do{
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 0, 0, 0));

    afficher_inv(screen, 20, 20, SCREEN_WIDTH -40, SCREEN_HEIGHT/2 -60, vendeur);
    afficher_inv(screen, 20, 400, SCREEN_WIDTH -40, SCREEN_HEIGHT/2 -60, inv);
    dest.x = 40 + i*122;
    dest.y = 140 + j*140;
    SDL_BlitSurface(select, NULL, pSurface, &dest);

    dest.x = SCREEN_WIDTH/8*7;
    dest.y = SCREEN_HEIGHT/2;
    texte = TTF_RenderText_Solid(police, "Terminer --> ECHAP", blanc);
    SDL_BlitSurface(texte, NULL, pSurface, &dest);
    dest.x = SCREEN_WIDTH/2 - texte->w/2;
    dest.y = SCREEN_HEIGHT/2;
    sprintf(string, "ARGENT : %i", *argent);
    SDL_FreeSurface(texte);

    texte = TTF_RenderText_Solid(police, string, blanc);
    SDL_BlitSurface(texte, NULL, pSurface, &dest);
    if(vendeur[i_inv].nombre != 0 && i_inv<nbObjets && !inv_vide(vendeur)){
      dest.x = SCREEN_WIDTH/4 - texte->w/2;
      dest.y = SCREEN_HEIGHT/2;
      sprintf(string, "PRIX : %i", vendeur[i_inv].valeurArgent);
      SDL_FreeSurface(texte);

      texte = TTF_RenderText_Solid(police, string, blanc);
      SDL_BlitSurface(texte, NULL, pSurface, &dest);
      SDL_FreeSurface(texte);

    }

    if(state[SDL_SCANCODE_RIGHT]){
      while(state[SDL_SCANCODE_RIGHT]){SDL_PumpEvents();}
      i++;
      if(i>9){
        i=9;
      }
      else{
        do{
          i_inv++;
        }while(!vendeur[i_inv].nombre);
      }
    }
    if(state[SDL_SCANCODE_LEFT]){
      while(state[SDL_SCANCODE_LEFT]){SDL_PumpEvents();}
      i--;
      if(i<0){
        i=0;
      }
      else{
        do{
          i_inv--;
        }while(!vendeur[i_inv].nombre);
      }
    }
    if(state[SDL_SCANCODE_UP]){
      while(state[SDL_SCANCODE_UP]){SDL_PumpEvents();}
      j--;
      if(j<0){
        j=0;
      }
      else{
        compteurBoucle = 0;
        while(compteurBoucle < 10){
          i_inv--;
          if(vendeur[i_inv].nombre){
            compteurBoucle++;
          }
        }
      }
    }
    if(state[SDL_SCANCODE_DOWN]){
      while(state[SDL_SCANCODE_DOWN]){SDL_PumpEvents();}
      j++;
      if(j>1){
        j=1;
      }
      else{
        compteurBoucle = 0;
        while(compteurBoucle < 10){
          i_inv++;
          if(vendeur[i_inv].nombre){
            compteurBoucle++;
          }
        }
      }
    }
    if(state[SDL_SCANCODE_RETURN]){
      while(state[SDL_SCANCODE_RETURN]){SDL_PumpEvents();}
      if(vendeur[i_inv].valeurArgent <= *argent && vendeur[i_inv].nombre){
        vendeur[i_inv].nombre--;
        *argent -= vendeur[i_inv].valeurArgent;
        inv[i_inv].nombre++;
        if(vendeur[i_inv].nombre == 0){
          do{
            i_inv++;
          }while(!vendeur[i_inv].nombre && i_inv < nbObjets);
        }
      }
    }
    if(state[SDL_SCANCODE_ESCAPE]){
      while(state[SDL_SCANCODE_ESCAPE]){SDL_PumpEvents();}
      test_touche++;
    }

    SDL_UpdateWindowSurface(screen);
  }while(!test_touche);
  printf("test\n");
  SDL_FreeSurface(select);
  TTF_CloseFont(police);
}
