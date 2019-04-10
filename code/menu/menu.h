#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/**
  \file menu.h
  \author Benjamin Riviere
*/

#define N 4

/**
  \enum eEtatProg
  \brief Une énumération pour l'état du programme
*/

typedef enum {menu, connecte, lobby, map, combat} eEtatProg;

extern long long unsigned fpsCount;
extern long long unsigned fin;
extern long long unsigned deb;
extern int quit;

extern int coop;
extern int serveur;

extern eEtatProg etatProg;


extern SDL_Event event;
extern SDL_Color blanc;
extern SDL_Color noir;

/**
  \struct affichage
  \brief Une structure qui permet d'avoir le texte et le rectangle ou il apparait au même endroit
*/

typedef struct {SDL_Rect rec; SDL_Surface* txt;} affichage;

void fonctionQuitter();
void fonctionFin();
void afficher(affichage tab[], int, SDL_Surface*, SDL_Window*, TTF_Font *);
void fonctionJeu(SDL_Surface*, SDL_Window*, TTF_Font *);
void fonctionOption(SDL_Surface*, SDL_Window*, TTF_Font *);
void fonctionCoop(SDL_Surface*, SDL_Window*, TTF_Font *);
