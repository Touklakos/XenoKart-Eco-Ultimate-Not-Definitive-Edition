
#include "enum.h"


/*Texte qui s'affichera au dessus des ennemis et des personnage indicant le nombre de d�gats re�u*/

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
