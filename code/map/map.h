#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

#define N 30
#define M 50
#define tmax 10

enum typemap{ VOLCAN, MONTAGNE, PIC, DESERT, PLATEAU, PLAINE, DONJON, MARAIS, TUNDRA, FORET, OCEAN, ARCHIPEL};

typedef struct coord_s{
  int x;
  int y;
}coord_t;

typedef struct case_s{
  coord_t coord;
  int val;
  enum typemap type;
}case_t;

typedef struct map_s{
  case_t v[N][M];
  enum typemap type;
  int difficult;
  int taille;
}map_t;

void fonctionQuitter();
void fonctionFin();
void init_mat(case_t c[N][M]);
int case_valide(case_t);
case_t creerCase(int, int, map_t *);
void creerCases(map_t *);
map_t * creerMap(enum typemap);
void afficherMap(map_t *, SDL_Surface*, SDL_Window*);
void afficher_matrice(case_t c[N][M]);
