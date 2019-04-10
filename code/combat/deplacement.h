#include "perso.h"

/**
    \struct doublet "Structure pour le clavier"
*/
typedef struct {

  int enfonce;
  int relache;

} doublet;

extern doublet clavier[1000];


void deplacementManette(SDL_GameController* controller, int indiceJoueur, Personnage* equipe[]);
void deplacementClavier(int indiceJoueur, Personnage* equipe[], doublet clavier[]);
