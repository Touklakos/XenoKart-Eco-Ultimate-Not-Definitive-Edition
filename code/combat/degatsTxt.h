
#include "enum.h"

/**
  \file degatsTxt.h
  \brief primitive et structure textes qui seront affiché à l'ecran
  \author Mano Brabant
*/



/**
    \struct degatsTxt
    \brief Texte qui s'affichera au dessus des ennemis et des personnage indiquant le nombre de dégats reçu
*/

typedef struct {

    char message[10];
    int degats;
    int posX, posY;
    int vie;
    SDL_Surface* txt;


} degatsTxt;



extern degatsTxt dgtsTxt[500];         //tableau des textes affichés � l'�cran

extern int nbDgtTxt;               //nombre de texte de d�gats affich� � l'�cran


void addDegatTxt(int dmg, int posX, int posY, int type);
void afficherDegatsTxt(SDL_Surface *pSurface, SDL_Rect camera);
