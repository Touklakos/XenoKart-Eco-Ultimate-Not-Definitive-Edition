#include "perso.h"


typedef struct {

  int enfonce;
  int relache;

} doublet;

void deplacementManette(SDL_GameController* controller, int indiceJoueur, Personnage* equipe[]);
void deplacementClavier(int indiceJoueur, Personnage* equipe[], doublet clavier[]);
