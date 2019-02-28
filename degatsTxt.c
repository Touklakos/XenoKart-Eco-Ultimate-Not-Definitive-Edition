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


/**
    \fn void addDegatTxt(degatsTxt *texte, int dmg, int posX, int posY, int type) {
    \brief permet d'ajouter du texte à une certaine position sur l'écran
    \param texte emplacement dans un tableau ou sont stockés tout les texte à afficher
    \param posX position en X du texte à afficher
    \param posY position en Y du texte à afficher
    \param type permet de determiner la couleur du texte

*/


void addDegatTxt(degatsTxt *texte, int dmg, int posX, int posY, int type) {


    texte->degats = dmg;
    texte->posX = posX + rand()%150-75;
    texte->posY = posY;
    texte->vie = 100;   //temps avant que le message soit �ffac�

    int taille = 40;
    int randTaille = 30;

    SDL_Color couleur;

    if(type == esquiveC) {

      sprintf(texte->message, "MISS");

      couleur.r = 200;
      couleur.g = 200;
      couleur.b = 200;

      taille = 40;
      randTaille = 30;

    } else {

      sprintf(texte->message, "%d", texte->degats);

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

        taille = 30;
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


    texte->txt = TTF_RenderText_Solid(police, texte->message, couleur);

    TTF_CloseFont(police);

}


/**
    \fn void afficherDegatsTxt(degatsTxt *texte, SDL_Surface *pSurface, SDL_Rect camera) {
    \brief permet d'afficher du texte sur l'écran
    \param texte tableau où sont stockés tout les textes à afficher
    \param pSurface fenetre dans laquelle on va afficher les textes
    \param camera nous permet d'afficher les textes de facon fixe

*/

void afficherDegatsTxt(degatsTxt *texte, SDL_Surface *pSurface, SDL_Rect camera) {


    SDL_Rect dest;

    dest.x = texte->posX - camera.x+camera.w;
    dest.y = texte->posY+texte->vie - camera.y+camera.h;

    texte->vie-=(texte->vie/10)+1;      //Le texte remonte petit � petit avant de disparaitre

    SDL_BlitSurface(texte->txt, NULL, pSurface, &dest);

}
