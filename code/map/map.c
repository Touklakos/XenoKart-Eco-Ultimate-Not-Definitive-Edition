#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "map.h"
#include "../combat/const.h"

int caseCount = 0;

case_t * creerCase(){
  case_t * hexcase = NULL ;
  hexcase = malloc(sizeof(*hexcase));

  return hexcase;
}



map_t * creerMap(enum typemap type){
  map_t * map = NULL ;
  map = malloc(sizeof(*map));


  return map;
}


int main(){


}
