#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

extern int fpsCount;
extern int deb;
extern int fin;
extern int quit;

extern SDL_Event event;

extern const int NB_CASE;

extern int caseCount;

enum typemap{ VOLCAN, MONTAGNE, PIC, DESERT, PLATEAU, PLAINE, DONJON, MARAIS, TUNDRA, FORET, OCEAN, ARCHIPEL};
enum typecase{ BASE, SPAWN, FIN};

typedef struct coord_s{
  int x;
  int y;
}coord_t;

typedef struct case_s{
  coord_t coord;
  int val;
  int path;
  enum typemap type;
  enum typecase subtype;
}case_t;

typedef struct map_s{
  case_t v[MAP_HEIGHT][MAP_WIDTH];
  enum typemap type;
  int difficult;
}map_t;

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
void init_mat(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
int case_valide(case_t);
int coord_valide(int, int);
int choixType(case_t, map_t *);
case_t creerCase(int, int, map_t *);
void creerCases(map_t *);
map_t * creerMap(enum typemap);
void afficherMap(map_t *, SDL_Surface*, SDL_Window*);
void afficher_matrice(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
void afficher_path(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
void afficher_typecase(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
void genererDepArr(map_t *);
case_t debut(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
case_t arrive(case_t mat[MAP_HEIGHT][MAP_WIDTH]);
void pathfinding(map_t *);
int valeurPath(map_t *);
