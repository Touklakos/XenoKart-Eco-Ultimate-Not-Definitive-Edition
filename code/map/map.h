#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

#define N 30
#define M 30
#define tmax 10

enum typemap{ VOLCAN, JUNGLE, DESERT, TUNDRA, PLAINE, MARAIS, MONTAGNE, ARCHIPEL, PLATEAU };

typedef struct coord_s{
  int x;
  int y;
}coord_t;

typedef struct case_s{
  coord_t coord;
  int val;
}case_t;

typedef struct map_s{
  case_t v[N][M];
  enum typemap type;
  int difficult;
  int taille;
}map_t;
