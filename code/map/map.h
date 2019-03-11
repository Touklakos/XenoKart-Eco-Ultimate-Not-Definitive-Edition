#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../combat/const.h"

enum typemap{ VOLCAN, JUNGLE, DESERT, TUNDRA, PLAINE, MARAIS, MONTAGNE, ARCHIPEL };

typedef struct case_s{
  case_s *tab[6];
  int val;
}case;

typedef struct map_s{
  case * deb;
  enum typemap type;
  int difficult;
  int taille;
}case;
