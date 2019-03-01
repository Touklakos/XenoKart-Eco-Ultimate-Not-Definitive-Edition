
#include "enum.h"


/*Texte qui s'affichera au dessus des ennemis et des personnage indicant le nombre de d�gats re�u*/

typedef struct {

    char message[10];
    int degats;
    int posX, posY;
    int vie;
    SDL_Surface* txt;


} degatsTxt;

void addDegatTxt(degatsTxt *texte, int dmg, int posX, int posY, int type);
void afficherDegatsTxt(degatsTxt *texte, SDL_Surface *pSurface, SDL_Rect camera);
