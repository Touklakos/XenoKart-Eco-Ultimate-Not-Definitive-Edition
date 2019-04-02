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

tElement *tete;
tElement *queue;


/**
  \file map.c
  \brief XenoKart Eco Plus
  \author Benjamin Riviere
  \version 0.01
  \date 25 mars 2019
*/

void initFile() {
	tete = NULL;
	queue = NULL;
}

int fileVide() {
	return tete == NULL;
}

void ajouter(case_t c) {
	tElement *nouv;
	nouv = malloc(sizeof(tElement));
	nouv->hexcase = c;
	nouv->suiv = NULL;
	if(fileVide()) {
		tete = nouv;
	} else {
		queue->suiv = nouv;
	}
	queue = nouv;
}

void retirer(case_t *c) {
	tElement *premier;
	if(!fileVide()) {
		premier = tete;
		*c = premier->hexcase;
		tete = premier->suiv;
		free(premier);
	}
}

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
  return((hexcase.coord.x >= 0 && hexcase.coord.x < M) && (hexcase.coord.y >= 0 && hexcase.coord.y < N));
}

int coord_valide(int x, int y){
  return((x >= 0 && x < M) && (y >= 0 && y < N));
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
  hexcase.typeCase = BASE;

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

map_t * creerMap(enum typemap type){

  map_t * map = NULL ;
  map = malloc(sizeof(*map));

  init_mat(map->v);

  map->type = type;

  creerCases(map);
  genererDepArr(map);
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
      if(c[i][j].val){
        printf("%3i|",c[i][j].val);
      }
      else printf("  X|");
    }
    printf("\n");
  }
}

void afficher_path(case_t c[N][M]){
  printf("---------------------------------------------- \n");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(c[i][j].val){
        printf("%3i|",c[i][j].path);
      }
      else printf("  X|");
    }
    printf("\n");
  }
}

void afficher_typecase(case_t c[N][M]){
  printf("---------------------------------------------- \n");

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(c[i][j].val){
        printf("%3i|",c[i][j].typeCase);
      }
      else printf("  X|");
    }
    printf("\n");
  }
}

void genererDepArr(map_t * map){
  map->v[0][0].typeCase = 1;
  map->v[6][2].typeCase = 2;
}

case_t debut(case_t c[N][M]){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(c[i][j].typeCase==SPAWN) return c[i][j];
    }
  }
  return c[0][0];
}

case_t arrive(case_t c[N][M]){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(c[i][j].typeCase==FIN) return c[i][j];
    }
  }
  return c[N-1][M-1];
}


int pathfinding(map_t * map){

  case_t case_depart = debut(map->v);
  case_t case_arrive = arrive(map->v);

  case_t hexcase;

	ajouter(case_depart);

	int x = case_depart.coord.x, y = case_depart.coord.y;

	while((x != case_arrive.coord.x && y != case_arrive.coord.y) && !fileVide()) {

		retirer(&hexcase);

		if(coord_valide(hexcase.coord.x-2,hexcase.coord.y) && map->v[hexcase.coord.x-2][hexcase.coord.y].type != OCEAN && !map->v[hexcase.coord.x-2][hexcase.coord.y].path){
			ajouter(map->v[hexcase.coord.x-2][hexcase.coord.y]);

			map->v[hexcase.coord.x-2][hexcase.coord.y].path = map->v[hexcase.coord.x][hexcase.coord.y].path+1;
		}
    if(coord_valide(hexcase.coord.x-1,hexcase.coord.y+1) && map->v[hexcase.coord.x-1][hexcase.coord.y+1].type != OCEAN && !map->v[hexcase.coord.x-1][hexcase.coord.y+1].path){
			ajouter(map->v[hexcase.coord.x-1][hexcase.coord.y+1]);

			map->v[hexcase.coord.x-1][hexcase.coord.y+1].path = map->v[hexcase.coord.x][hexcase.coord.y].path+1;
		}
    if(coord_valide(hexcase.coord.x+1,hexcase.coord.y+1) && map->v[hexcase.coord.x+1][hexcase.coord.y+1].type != OCEAN && !map->v[hexcase.coord.x+1][hexcase.coord.y+1].path){
			ajouter(map->v[hexcase.coord.x+1][hexcase.coord.y+1]);

			map->v[hexcase.coord.x+1][hexcase.coord.y+1].path = map->v[hexcase.coord.x][hexcase.coord.y].path+1;
		}
    if(coord_valide(hexcase.coord.x+2,hexcase.coord.y) && map->v[hexcase.coord.x+2][hexcase.coord.y].type != OCEAN && !map->v[hexcase.coord.x+2][hexcase.coord.y].path){
			ajouter(map->v[hexcase.coord.x+2][hexcase.coord.y]);

			map->v[hexcase.coord.x+2][hexcase.coord.y].path = map->v[hexcase.coord.x][hexcase.coord.y].path+1;
		}
    if(coord_valide(hexcase.coord.x+1,hexcase.coord.y-1) && map->v[hexcase.coord.x+1][hexcase.coord.y-1].type != OCEAN && !map->v[hexcase.coord.x+1][hexcase.coord.y-1].path){
      ajouter(map->v[hexcase.coord.x+1][hexcase.coord.y-1]);

      map->v[hexcase.coord.x+1][hexcase.coord.y-1].path = map->v[hexcase.coord.x][hexcase.coord.y].path+1;
    }
    if(coord_valide(hexcase.coord.x-1,hexcase.coord.y-1) && map->v[hexcase.coord.x-1][hexcase.coord.y-1].type != OCEAN && !map->v[hexcase.coord.x-1][hexcase.coord.y-1].path){
      ajouter(map->v[hexcase.coord.x-1][hexcase.coord.y-1]);

      map->v[hexcase.coord.x-1][hexcase.coord.y-1].path = map->v[hexcase.coord.x][hexcase.coord.y].path+1;
    }
	}
  return map->v[case_arrive.coord.x][case_arrive.coord.x].path;
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
