#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <time.h>

#include "map.h"
#include "../combat/const.h"

/**
  \file map.c
  \brief Fichier qui contient les fonctions pour la carte
  \author Benjamin Riviere
*/

long long unsigned fpsCount;
long long unsigned deb;
long long unsigned fin;

const int NB_CASE = (MAP_WIDTH*MAP_HEIGHT)/2;

SDL_Event event;

int caseCount = 1;

tElement *tete;
tElement *queue;

/**
    \fn void initFile()
    \brief Cette fonction initialise la file
*/

void initFile() {
	tete = NULL;
	queue = NULL;
}

/**
    \fn int fileVide()
    \brief Cette fonction renvoie si la file est vide
*/

int fileVide() {
	return tete == NULL;
}

/**
    \fn void ajouter(case_t hexcase)
    \brief Cette fonction ajoute la valeur en parametre dans la file
    \param hexcase Une case
*/

void ajouter(case_t hexcase) {
	tElement *nouv;
	nouv = malloc(sizeof(tElement));
	nouv->hexcase = hexcase;
	nouv->suiv = NULL;
	if(fileVide()) {
		tete = nouv;
	} else {
		queue->suiv = nouv;
	}
	queue = nouv;
}

/**
    \fn void retirer(case_t *mat)
    \brief Cette fonction retire la valeur de la file dans le parametre
		\param v Un pointeur sur une case
*/

void retirer(case_t *v) {
	tElement *premier;
	if(!fileVide()) {
		premier = tete;
		*v = premier->hexcase;
		tete = premier->suiv;
		free(premier);
	}
}


/**
    \fn void init_mat(case_t mat[MAP_HEIGHT][MAP_WIDTH])
    \brief Cette fonction initialise les cases de la matrice à 0
    \param mat[MAP_HEIGHT][MAP_WIDTH] Matrice de la carte
*/

void init_mat(case_t mat[MAP_HEIGHT][MAP_WIDTH]){

  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      mat[i][j].val = 0;
    }
  }
}

/**
    \fn case_valide(case_t hexcase)
    \brief Cette fonction permet de vérifier que les coordonnées de la case sont valides
    \param hexcase Une case
*/

int case_valide(case_t hexcase){
  return((hexcase.coord.x >= 0 && hexcase.coord.x < MAP_WIDTH) && (hexcase.coord.y >= 0 && hexcase.coord.y < MAP_HEIGHT));
}

/**
    \fn int coord_valide(int x, int y)
    \brief Cette fonction permet de vérifier que les coordonnées sont valides
    \param x L'entier qui représente la Coordonnée x
	  \param y L'entier qui représente la Coordonnée y
*/

int coord_valide(int x, int y){
  return((x >= 0 && x < MAP_WIDTH) && (y >= 0 && y < MAP_HEIGHT));
}

/**
    \fn int choixType(case_t hexcase, map_t * map)
    \brief Cette fonction permet de choisir aléatoirement un type pour une case
    \param hexcase Une case
	  \param map La carte
*/

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
    \fn case_t creerCase(int x, int y, map_t * map)
    \brief Cette fonction permet de générer une case
    \param x Coordonnée X de la case
    \param y Coordonnée Y de la case
    \param map La carte
*/

case_t creerCase(int x, int y, map_t * map){

  case_t hexcase;

  printf("caseCount : %i\n", caseCount);

  hexcase.val = caseCount;

  hexcase.path = 0;

  hexcase.coord.x = x;
  hexcase.coord.y = y;

  hexcase.type = choixType(hexcase, map);
	if(rand()%10 != 0) hexcase.subtype = BASE;
	else hexcase.subtype = ENNEMI;

  caseCount++;

  return hexcase;
}

/**
    \fn void creerCases(map_t * map)
    \brief Cette fonction permet de générer toutes les cases de la carte
    \param map La carte
*/

void creerCases(map_t * map){

  int i=0,j=0;

  srand(time(NULL));

  for(i=0; i<MAP_HEIGHT; i++){
    for(;j<MAP_WIDTH; j+=2){
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

	map->v[0][0].type = OCEAN;

  return map;
}

/**
    \fn void afficherMap(map_t * map, SDL_Surface* pSurface, SDL_Window* screen)
    \brief Cette fonction permet d'afficher la carte avec la SDL
    \param map La carte
    \param pSurface Surface sur laquel on affiche
    \param screen Ecran sur lequel on affiche
*/

void afficherMap(map_t * map, SDL_Surface* pSurface, SDL_Rect camera){


  SDL_Rect test = {0,0,HEX_WIDTH,HEX_HEIGHT};
  SDL_Surface * img[13];
	SDL_Surface * imgsubtype[4];

	img[0] = IMG_Load("code/map/hex/hex_volcan.png");
	img[1] = IMG_Load("code/map/hex/hex_montagne.png");
	img[2] = IMG_Load("code/map/hex/hex_pic.png");
	img[3] = IMG_Load("code/map/hex/hex_desert.png");
	img[4] = IMG_Load("code/map/hex/hex_plateau.png");
	img[5] = IMG_Load("code/map/hex/hex_plaine.png");
	img[6] = IMG_Load("code/map/hex/hex_donjon.png");
	img[7] = IMG_Load("code/map/hex/hex_marais.png");
	img[8] = IMG_Load("code/map/hex/hex_tundra.png");
	img[9] = IMG_Load("code/map/hex/hex_foret.png");
	img[10] = IMG_Load("code/map/hex/hex_ocean.png");
	img[11] = IMG_Load("code/map/hex/hex_archipel.png");
	img[12] = IMG_Load("code/map/hex/hex.png");

	imgsubtype[0] = NULL;
	imgsubtype[1] = IMG_Load("code/map/hex/ennemi.png");
	imgsubtype[2] = IMG_Load("code/map/hex/spawn.png");
	imgsubtype[3] = IMG_Load("code/map/hex/end.png");

  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(map->v[i][j].val){
				test.x = map->v[i][j].coord.x * (HEX_WIDTH - HEX_WIDTH/4-0.5) -camera.x + camera.w;
        test.y = map->v[i][j].coord.y * (HEX_HEIGHT - HEX_HEIGHT/2) -camera.y + camera.h;

        SDL_BlitSurface(img[map->v[i][j].type], NULL, pSurface, &test);
				SDL_BlitSurface(imgsubtype[map->v[i][j].subtype], NULL, pSurface, &test);

      }
    }
  }
	for(int i = 0; i < 13; i++) {

		SDL_FreeSurface(img[i]);

	}

	for(int i = 0; i < 4; i++) {

		SDL_FreeSurface(imgsubtype[i]);

	}
}

/**
    \fn void afficher_matrice(case_t mat[MAP_HEIGHT][MAP_WIDTH])
    \brief Cette fonction permet d'afficher les valeurs des cases dans la matrice
    \param mat[MAP_HEIGHT][MAP_WIDTH] Matrice de la carte
*/

void afficher_matrice(case_t mat[MAP_HEIGHT][MAP_WIDTH]){
  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(mat[i][j].val){
        printf("%3i|",mat[i][j].val);
      }
      else printf("  X|");
    }
    printf("\n");
  }
}

/**
    \fn void afficher_matrice(case_t mat[MAP_HEIGHT][MAP_WIDTH])
    \brief Cette fonction permet d'afficher les valeurs de pathfinding des cases dans la matrice
    \param mat[MAP_HEIGHT][MAP_WIDTH] Matrice de la carte
*/

void afficher_path(case_t mat[MAP_HEIGHT][MAP_WIDTH]){
  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(mat[i][j].val){
        printf("%3i|",mat[i][j].path);
      }
      else printf("  X|");
    }
    printf("\n");
  }
}

/**
    \fn void afficher_matrice(case_t mat[MAP_HEIGHT][MAP_WIDTH])
    \brief Cette fonction permet d'afficher les valeurs de sous_types des cases dans la matrice
    \param mat[MAP_HEIGHT][MAP_WIDTH] Matrice de la carte
*/

void afficher_subtype(case_t mat[MAP_HEIGHT][MAP_WIDTH]){
  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(mat[i][j].val){
        printf("%3i|",mat[i][j].subtype);
      }
      else printf("  X|");
    }
    printf("\n");
  }
}

/**
    \fn void genererDepArr(map_t * map)
    \brief Cette fonction permet de generer une case de départ et une case d'arrivé sur la carte
    \param map La carte
*/

void genererDepArr(map_t * map){

	srand(time(NULL));
	int varand;
	case_t hexcase;

  map->v[0][0].subtype = SPAWN;

	do{
		varand = rand()%NB_CASE;
		printf("varand : %i \n",varand);
		hexcase = chercherCase(map->v,varand);
		printf("hexcase x : %i \n",hexcase.coord.x);
		printf("hexcase y : %i \n",hexcase.coord.y);
		map->v[hexcase.coord.x][hexcase.coord.y].subtype = FIN;
	}while(hexcase.type == OCEAN);
}

/**
    \fn case_t debut(case_t mat[MAP_HEIGHT][MAP_WIDTH])
    \brief Cette fonction renvoie la case de depart
    \param map La carte
*/

case_t debut(case_t mat[MAP_HEIGHT][MAP_WIDTH]){
  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(mat[i][j].subtype==SPAWN) return mat[i][j];
    }
  }
  return mat[0][0];
}

/**
    \fn case_t arrive(case_t mat[MAP_HEIGHT][MAP_WIDTH])
    \brief Cette fonction renvoie la case de depart
    \param map La carte
*/

case_t arrive(case_t mat[MAP_HEIGHT][MAP_WIDTH]){
  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(mat[i][j].subtype==FIN) return mat[i][j];
    }
  }
  return mat[MAP_HEIGHT-1][MAP_WIDTH-1];
}

/**
    \fn case_t chercherCase(case_t mat[MAP_HEIGHT][MAP_WIDTH], int v)
    \brief Cette fonction renvoie la case qui à la valeur v
    \param mat[MAP_HEIGHT][MAP_WIDTH] Matrice de la carte
		\param v Une valeur int
*/

case_t chercherCase(case_t mat[MAP_HEIGHT][MAP_WIDTH], int v){
  for(int i = 0; i < MAP_HEIGHT; i++){
    for(int j = 0; j < MAP_WIDTH; j++){
      if(mat[i][j].val==v) return mat[i][j];
    }
  }
  return mat[0][0];
}

/**
    \fn void pathfinding(map_t * map)
    \brief Cette fonction permet de faire le pathfinding sur la carte
    \param map La carte
*/

void pathfinding(map_t * map){

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
}

/**
    \fn int valeurPath(map_t * map)
    \brief Cette fonction renvoie la distance entre la case de départ et d'arrivé
    \param map La carte
*/

int valeurPath(map_t * map){
	return arrive(map->v).path;
}
