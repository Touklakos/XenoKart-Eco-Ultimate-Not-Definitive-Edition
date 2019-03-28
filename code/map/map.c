#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <time.h>

#include "map.h"
#include "../combat/const.h"

int fpsCount = 0;
int deb = 0;
int fin = 0;
int quit = 0;

SDL_Event event;

const int NB_CASE=N*M;

int caseCount = 1;



/**
  \file map.c
  \brief XenoKart Eco Plus
  \author Benjamin Riviere
  \version 0.01
  \date 25 mars 2019
*/

/**
    \fn void fonctionQuitter()
    \brief Cette fonction vérifie si l'utilisateur veut fermer le programme avec la croix
*/

void fonctionQuitter(){

  SDL_PollEvent(&event);

  switch(event.type){
      case SDL_QUIT:
        quit = 1;
        break;
  }
}

/**
    \fn void fonctionFin()
    \brief Cette fonction affiche les statistiques à la fin des boucles dans les fonctions
*/

void fonctionFin(){

  fin = SDL_GetTicks();

  printf("\nfps = %i\n", (fpsCount++)*1000/SDL_GetTicks());
  printf("fin = %i\n", fin/1000);
  int delai = ((1000/FPS)-(fin-deb));

  if(delai > 0){
    SDL_Delay(delai);
  }
}

/**
    \fn void init_mat(case_t)
    \brief Cette fonction initialise les cases de la matrice à 0
    \param mat[N][M] Matrice de la carte
*/

void init_mat(case_t mat[N][M]){

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      mat[i][j].val = 0;
    }
  }
}

/**
    \fn case_valide(case_t mat[N][M])
    \brief Cette fonction permet de vérifier que les coordonnées de la case sont valides
    \param hexcase une case t_case
*/


int case_valide(case_t hexcase){
  return((hexcase.coord.x < 0 && hexcase.coord.x > M) && (hexcase.coord.y < 0 && hexcase.coord.y > N));
}

int coord_valide(int x, int y){
  return((x < 0 && x > M) && (y < 0 && y > N));
}

int choixType(case_t hexcase, map_t * map){
  int choix[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

  int valrand, somme = 0;


  choix[map->type] += 35;
  choix[(map->type+11)%12] += 10;
  choix[(map->type+1)%12] += 10;
  choix[10] += 15;


  if(coord_valide(hexcase.coord.x-2, hexcase.coord.y) && map->v[hexcase.coord.x-2][hexcase.coord.y].val != 0) choix[map->v[hexcase.coord.x-2][hexcase.coord.y].type] += 5;
  else choix[map->type] += 5;
  if(coord_valide(hexcase.coord.x-1, hexcase.coord.y+1)&& map->v[hexcase.coord.x-1][hexcase.coord.y+1].val != 0) choix[map->v[hexcase.coord.x-1][hexcase.coord.y+1].type] += 5;
  else choix[map->type] += 5;
  if(coord_valide(hexcase.coord.x+1, hexcase.coord.y+1)&& map->v[hexcase.coord.x+1][hexcase.coord.y+1].val != 0) choix[map->v[hexcase.coord.x+1][hexcase.coord.y+1].type] += 5;
  else choix[map->type] += 5;
  if(coord_valide(hexcase.coord.x+2, hexcase.coord.y)&& map->v[hexcase.coord.x+2][hexcase.coord.y].val != 0) choix[map->v[hexcase.coord.x+2][hexcase.coord.y].type] += 5;
  else choix[map->type] += 5;
  if(coord_valide(hexcase.coord.x+1, hexcase.coord.y-1)&& map->v[hexcase.coord.x+1][hexcase.coord.y-1].val != 0) choix[map->v[hexcase.coord.x+1][hexcase.coord.y-1].type] += 5;
  else choix[map->type] += 5;
  if(coord_valide(hexcase.coord.x-1, hexcase.coord.y-1)&& map->v[hexcase.coord.x-1][hexcase.coord.y-1].val != 0) choix[map->v[hexcase.coord.x-1][hexcase.coord.y-1].type] += 5;
  else choix[map->type] += 5;

  valrand = rand()%100+1;

  for(int i = 0; i < 12; i++){
    somme+= choix[i];
    if(somme >= valrand) return i;
  }
  return choix[map->type];
}


/**
    \fn case_t creerCase(int x, int y)
    \brief Cette fonction permet de générer une case
    \param x Coordonnée X de la case
    \param y Coordonnée Y de la case
*/

case_t creerCase(int x, int y, map_t * map){

  printf("creercase\n");
  case_t hexcase;

  printf("caseCount : %i \n", caseCount);

  hexcase.val = caseCount;

  hexcase.path = 0;

  hexcase.coord.x = x;
  hexcase.coord.y = y;

  hexcase.type = choixType(hexcase, map);
  hexcase.typeCase = 0;

  caseCount++;

  return hexcase;
}

/**
    \fn void creerCases(map_t * map)
    \brief Cette fonction permet de générer toutes les cases de la matrice
    \param map La carte
*/

void creerCases(map_t * map){

  int i=0,j=0;

  srand(time(NULL));

  for(i=0; i<N; i++){
    for(;j<M; j+=2){
      map->v[i][j] = creerCase(i,j,map);
    }
  if((i+1)%2) j=1;
  else j = 0;
  }
}

/**
    \fn map_t * creerMap(enum typemap type)
    \brief Cette fonction permet de créer la carte
    \param type Le type de carte
*/

map_t * creerMap(enum typemap type, case_t * dep, case_t * arr){

  map_t * map = NULL ;
  map = malloc(sizeof(*map));

  init_mat(map->v);

  map->type = type;

  creerCases(map);

  genererDepArr(map,dep,arr);

  return map;
}


void afficherMap(map_t * map, SDL_Surface* pSurface, SDL_Window* screen){


  SDL_Rect test = {0,0,HEX_WIDTH,HEX_HEIGHT};
  SDL_Surface * img = NULL;

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map->v[i][j].val){
        test.x = map->v[i][j].coord.y * (HEX_WIDTH - HEX_HEIGHT/4);
        test.y = map->v[i][j].coord.x * (HEX_HEIGHT - HEX_HEIGHT/2);

        switch(map->v[i][j].type){
          case 0 : img = IMG_Load("code/map/hex/hex_volcan.png"); break;
          case 1 : img = IMG_Load("code/map/hex/hex_montagne.png"); break;
          case 2 : img = IMG_Load("code/map/hex/hex_pic.png"); break;
          case 3 : img = IMG_Load("code/map/hex/hex_desert.png"); break;
          case 4 : img = IMG_Load("code/map/hex/hex_plateau.png"); break;
          case 5 : img = IMG_Load("code/map/hex/hex_plaine.png"); break;
          case 6 : img = IMG_Load("code/map/hex/hex_donjon.png"); break;
          case 7 : img = IMG_Load("code/map/hex/hex_marais.png"); break;
          case 8 : img = IMG_Load("code/map/hex/hex_tundra.png"); break;
          case 9 : img = IMG_Load("code/map/hex/hex_foret.png"); break;
          case 10 : img = IMG_Load("code/map/hex/hex_ocean.png"); break;
          case 11 : img = IMG_Load("code/map/hex/hex_archipel.png"); break;
          default : img = IMG_Load("code/map/hex/hex.png"); break;
        }

        SDL_BlitSurface(img, NULL, pSurface, &test);
      }
    }
  }
  SDL_UpdateWindowSurface(screen);
}

/**
    \fn afficher_matrice(case_t [][])
    \brief Cette fonction permet de vérifier que les coordonnées de la case sont valides
    \param mat[N][M] Matrice de la carte
*/

void afficher_matrice(case_t c[N][M]){

  printf("---------------------------------------------- \n");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      printf("%3i|",c[i][j].val);
    }
    printf("\n");
  }
}

void afficher_path(case_t c[N][M]){
    printf("afficherpath\n");

  printf("---------------------------------------------- \n");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      printf("%3i|",c[i][j].path);
    }
    printf("\n");
  }
}

void genererDepArr(map_t * map, case_t * dep, case_t * arr){
  int spawn, end;

  spawn = rand()%NB_CASE/2;
  end = rand()%NB_CASE/2;

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map->v[i][j].val == spawn){
        map->v[i][j].typeCase = 1;
        dep = &map->v[i][j];
      }
      else if(map->v[i][j].val == end){
        map->v[i][j].typeCase = 2;
        arr = &map->v[i][j];
      }
    }
  }
}


int pathfinding(map_t * map, case_t * depart, case_t * arrive) {

	ajouter(depart->coord.x);
	ajouter(depart->coord.y);

	int x = depart->coord.x, y = depart->coord.y;

	while((x != arrive->coord.x && y != arrive->coord.y) && !fileVide()) {

		retirer(&x);
		retirer(&y);

		if(coord_valide(x-2,y) && map->v[x-2][y].val != 10 && map->v[x-2][y].path == 0){
			ajouter(x-2);
			ajouter(y);

			map->v[x-2][y].path = map->v[x][y].path+1;
		}

    if(coord_valide(x-1,y+1) && map->v[x-1][y+1].val != 10 && map->v[x-1][y+1].path == 0){
			ajouter(x-1);
			ajouter(y+1);

			map->v[x-1][y+1].path = map->v[x][y].path+1;
		}

    if(coord_valide(x+1,y+1) && map->v[x+1][y+1].val != 10 && map->v[x+1][y+1].path == 0){
			ajouter(x+1);
			ajouter(y+1);

			map->v[x+1][y+1].path = map->v[x][y].path+1;
		}

    if(coord_valide(x+2,y) && map->v[x+2][y].val != 10 && map->v[x+2][y].path == 0){
			ajouter(x+2);
			ajouter(y);

			map->v[x+2][y].path = map->v[x][y].path+1;
		}

    if(coord_valide(x+1,y-1) && map->v[x+1][y-1].val != 10 && map->v[x+1][y-1].path == 0){
			ajouter(x+1);
			ajouter(y-1);

			map->v[x+1][y-1].path = map->v[x][y].path+1;
		}

    if(coord_valide(x-1,y-1) && map->v[x-1][y-1].val != 10 && map->v[x-1][y-1].path == 0){
			ajouter(x-1);
			ajouter(y-1);

			map->v[x-1][y-1].path = map->v[x][y].path+1;
		}
	}
  return map->v[arrive->coord.x][arrive->coord.x].path;
}


/*case_t recherchecase(int i, case_t map[N][M]){

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(map[i][j].val = i) return map[i][j];
    }
  }
}*/

/*void afficher_voisin(case_t hexcase, SDL_Surface* pSurface, SDL_Window* screen){

  SDL_Rect test = {hexcase.x,hexcase.y,50,50};
  SDL_Surface * img = NULL;
  img = IMG_Load("code/map/hexagone.png");

  if(hexcase.voisin[0].val != 0) test.y -= 672;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

  if(hexcase.voisin[1].val != 0) test.x += 0.75*422; test.y -= (sqrt(3)/2) * 422;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

  if(hexcase.voisin[2].val != 0) test.x += 0.75*422; test.y += (sqrt(3)/2) * 422;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

  if(hexcase.voisin[3].val != 0) test.y += 672;
  SDL_BlitSurface(img, NULL, pSurface, &test);
  SDL_UpdateWindowSurface(screen);

}*/

/**
    \fn afficherMap(map_t * map, SDL_Surface* pSurface, SDL_Window* screen)
    \brief Cette fonction permet d'afficher la carte avec la SDL
    \param map La carte
    \param pSurface Surface sur laquel on affiche
    \param screen Ecran sur lequel on afficheMARAIS, TU
*/
