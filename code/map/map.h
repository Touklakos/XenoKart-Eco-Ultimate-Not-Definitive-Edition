#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

#define N 30
#define M 30
#define tmax 10

enum typemap{ VOLCAN, JUNGLE, DESERT, TUNDRA, PLAINE, MARAIS, MONTAGNE, ARCHIPEL, PLATEAU };

typedef struct case_s{
  struct case_s *voisin[6];
  int val;
  int x,y;
}case_t;

typedef struct map_s{
  case_t v[N][M];
  enum typemap type;
  int difficult;
  int taille;
}map_t;

int file[tmax];
int tete = 0, queue = tmax-1, nb=0;

void ajouter(int c){
  if(nb < tmax){
    if(queue == tmax-1) queue = 0;
    else queue++;
    file[queue] = c;
    nb++;
  }
}

void retirer(int * c){
  if(nb > 0){
    *c = file[tete];
    nb--;
    if(tete == tmax-1) tete = 0;
    else tete++;
  }
}
