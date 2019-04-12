#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

/**
  \file map.h
  \brief Fichier header pour la carte
  \author Benjamin Riviere
*/

extern long long unsigned fpsCount;
extern long long unsigned deb;
extern long long unsigned fin;

extern SDL_Rect camera;  //camera servira à afficher les sprites en fonction de la position du joueur


extern SDL_Event event;

extern const int NB_CASE;

extern int caseCount;

/**
  \enum typemap
  \brief Une énumération pour les différents type de carte
*/

enum typemap{ VOLCAN, MONTAGNE, PIC, DESERT, PLATEAU, PLAINE, DONJON, MARAIS, TUNDRA, FORET, OCEAN, ARCHIPEL};

/**
  \enum typecase
  \brief Une énumération pour les différents type de case
*/

enum typecase{ BASE, SPAWN, FIN};

/**
  \struct coord_t
  \brief Une structure qui contient des coordonnées X et Y
*/

typedef struct coord_s{
  int x;
  int y;
}coord_t;

/**
  \struct case_t
  \brief Cette structure contient les valeurs d'une case
*/

typedef struct case_s{
  coord_t coord;
  int val;
  int path;
  enum typemap type;
  enum typecase subtype;
}case_t;

/**
  \struct map_t
  \brief Cette structure contient les valeurs d'une carte
*/

typedef struct map_s{
  case_t v[MAP_HEIGHT][MAP_WIDTH];
  enum typemap type;
  int difficult;
}map_t;

/**
  \struct element
  \brief Cette structure permet d'utiliser la file
*/

typedef struct element {
	case_t hexcase;
	struct element* suiv;
	struct element* prec;
} tElement;



void initFile();
int fileVide();
void ajouter(case_t v);
void retirer(case_t *v);
void fonctionQuitter();
void fonctionFin();
void init_mat(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
int case_valide(case_t);
int coord_valide(int, int);
int choixType(case_t, map_t *);
case_t creerCase(int, int, map_t *);
void creerCases(map_t *);
map_t * creerMap(enum typemap);
void afficherMap(map_t *, SDL_Surface*, SDL_Rect camera);
void afficher_matrice(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
void afficher_path(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
void afficher_typecase(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
void genererDepArr(map_t *);
case_t debut(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
case_t arrive(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
case_t chercherCase(case_t mat[MAP_HEIGHT][MAP_WIDTH], int);
void pathfinding(map_t *);
int valeurPath(map_t *);
void afficherMapMieux(map_t * map, SDL_Rect camera, SDL_Surface* pSurface);
void afficher_perso_map(SDL_Surface * perso, int x, int y, SDL_Rect camera, SDL_Window* screen);
void centrage(SDL_Rect * camera, case_t map[N][M]);
void deplacement(SDL_Event e, SDL_Rect * camera, int mouseX, int mouseY, case_t map[N][M], case_t * pos);
