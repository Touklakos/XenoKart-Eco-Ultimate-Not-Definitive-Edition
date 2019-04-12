#include "perso.h"


/**
  \file deplacement.h
  \brief primitive d'interpretation des entrées claviers et structure pour le clavier
  \author Mano Brabant
*/


/**
    \struct doublet
    \brief Structure pour le clavier
*/
typedef struct {

  int enfonce;
  int relache;

} doublet;

extern doublet clavier[1000];


void deplacementManette(SDL_GameController* controller, int indiceJoueur, Personnage* equipe[]);
void deplacementClavier(int indiceJoueur, Personnage* equipe[], doublet clavier[]);
