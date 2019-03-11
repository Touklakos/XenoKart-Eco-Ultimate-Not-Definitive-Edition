#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

enum typemap{ VOLCAN, JUNGLE, DESERT, TUNDRA, PLAINE, MARAIS, MONTAGNE, ARCHIPEL, PLATEAU };

typedef struct case_s{
  struct case_s *tab[6];
  int val;
}case_t;

typedef struct map_s{
  case_t * deb;
  enum typemap type;
  int difficult;
  int taille;
}map_t;
