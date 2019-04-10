#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "degatsTxt.h"


/**
  \file degatsTxt.c
  \brief texte des degats qui serront afficher à l'ecran
  \author Mano Brabant
  \version 0.01
  \date 13 fevrier 2019
*/



degatsTxt dgtsTxt[500];         //tableau des textes affichés � l'�cran

int nbDgtTxt = 0;               //nombre de texte de d�gats affich� � l'�cran



/**
    \fn void addDegatTxt(degatsTxt *texte, int dmg, int posX, int posY, int type) {
    \brief permet d'ajouter du texte à une certaine position sur l'écran
    \param texte emplacement dans un tableau ou sont stockés tout les texte à afficher
    \param posX position en X du texte à afficher
    \param posY position en Y du texte à afficher
    \param type permet de determiner la couleur du texte
*/



void addDegatTxt(int dmg, int posX, int posY, int type) {


    dgtsTxt[nbDgtTxt].degats = dmg;
    dgtsTxt[nbDgtTxt].posX = posX + rand()%150-75;
    dgtsTxt[nbDgtTxt].posY = posY;
    dgtsTxt[nbDgtTxt].vie = 100;   //temps avant que le message soit �ffac�

    int taille = 40;
    int randTaille = 30;

    SDL_Color couleur;

    if(type == esquiveC) {

      sprintf(dgtsTxt[nbDgtTxt].message, "MISS");

      couleur.r = 200;
      couleur.g = 200;
      couleur.b = 200;

      taille = 40;
      randTaille = 30;

    } else {

      sprintf(dgtsTxt[nbDgtTxt].message, "%d", dgtsTxt[nbDgtTxt].degats);

      if(type == critiqueC) {

        couleur.r = 255;
        couleur.g = 128;
        couleur.b = 0;

        taille = 90;
        randTaille = 10;

      } else if(type == gardeC) {

        couleur.r = 100;
        couleur.g = 100;
        couleur.b = 100;

        taille = 50;
        randTaille = 20;

      } else if(type == soinC) {

        couleur.r = 0;
        couleur.g = 255;
        couleur.b = 0;

        taille = 60;
        randTaille = 10;

      } else if(type == fournaiseC) {

        couleur.r = 255;
        couleur.g = 0;
        couleur.b = 0;

        taille = 30;
        randTaille = 1;

      } else if(type == frissonC) {

        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 255;

        taille = 30;
        randTaille = 1;

      } else if(type == poisonC) {

        couleur.r = 255;
        couleur.g = 0;
        couleur.b = 255;

        taille = 30;
        randTaille = 1;

      } else if(type == normalC) {

        couleur.r = 0;
        couleur.g = 0;
        couleur.b = 0;

        taille = 40;
        randTaille = 30;

      }

    }

    TTF_Font *police = NULL;

    police = TTF_OpenFont("./data/DejaVuSans.ttf", (rand()%randTaille)+taille);   //taile de police plus ou moins grande


    dgtsTxt[nbDgtTxt].txt = TTF_RenderText_Solid(police, dgtsTxt[nbDgtTxt].message, couleur);

    nbDgtTxt++;

    TTF_CloseFont(police);

}


/**
    \fn void afficherDegatsTxt(SDL_Surface *pSurface, SDL_Rect camera) {
    \brief permet d'afficher du texte sur l'écran
    \param pSurface fenetre dans laquelle on va afficher les textes
    \param camera nous permet d'afficher les textes de facon fixe
*/

void afficherDegatsTxt(SDL_Surface *pSurface, SDL_Rect camera) {

  for(int i = 0; i < nbDgtTxt; i++) {

    SDL_Rect dest;

    dest.x = dgtsTxt[i].posX - camera.x+camera.w;
    dest.y = dgtsTxt[i].posY+dgtsTxt[i].vie - camera.y+camera.h;

    dgtsTxt[i].vie-=(dgtsTxt[i].vie/10)+1;      //Le texte remonte petit � petit avant de disparaitre

    SDL_BlitSurface(dgtsTxt[i].txt, NULL, pSurface, &dest);

  }

}
