#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"
#include "../file.h"

#define N 30
#define M 50
#define tmax 10

extern int fpsCount;
extern int deb;
extern int fin;
extern int quit;

extern SDL_Event event;

extern const int NB_CASE;

extern int caseCount;

enum typemap{ VOLCAN, MONTAGNE, PIC, DESERT, PLATEAU, PLAINE, DONJON, MARAIS, TUNDRA, FORET, OCEAN, ARCHIPEL};
enum typecase{ BASIQUE, SPAWN, FIN};

typedef struct coord_s{
  int x;
  int y;
}coord_t;

typedef struct case_s{
  coord_t coord;
  int val;
  int path;
  enum typemap type;
  enum typecase typeCase;
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
map_t * creerMap(enum typemap, case_t *, case_t *);
void afficherMap(map_t *, SDL_Surface*, SDL_Window*);
void afficher_matrice(case_t c[N][M]);
