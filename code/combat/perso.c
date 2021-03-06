
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "perso.h"


/**
  \file perso.c
  \brief Fonctions qui incluent uniquement les personnages
  \author Mano Brabant
*/

Personnage* equipe[3];      //durant un combat l'équipe est composé de trois personnage

int indicePersonnage;

/**
    \fn void initPersonnage(Personnage* perso, char fichier[50])
    \brief initialise le personnage passé en parametre avec un ficher
    \param perso le personnage que l'on initialise
    \param fichier le fichier qui contient les information du personnage
*/

void initPersonnage(Personnage* perso, char fichier[50]) {

  perso->posX = rand()%1280;
  perso->posY = rand()%720;
  perso->vitX = 0;
  perso->vitY = 0;
  perso->numFrame = 0;

  FILE* f;


  f = fopen(fichier, "r");  //fichier dans le quel sont stockées les stats du personnages


  perso->NV = 0;
  perso->EXP = 0;
  perso->MAXPV = 0;
  perso->PV = 0;
  perso->FRC = 0;
  perso->MGE = 0;
  perso->VITATT = 0;
  perso->CRIT = 0;
  perso->CNTR = 0;
  perso->GARDE = 0;
  perso->DEFPHY = 0;
  perso->DEFMGE = 0;
  perso->AGI = 0;
  perso->DEXT = 0;
  perso->PRTAUTO = 0;
  perso->CHANCE = 0;

  perso->cible = 0;
  perso->enChoixCible = 0;



  char temp[20];

  char cheminImage[50];

  fscanf(f, "%s", cheminImage);           //on charge son image
  perso->image = IMG_Load(cheminImage);

  while(!feof(f)) {                       //on charge les stats �crites dans un fichier

    fscanf(f, "%s : ", temp);

    if(!strcmp(temp,"NV")) {

      fscanf(f, "%d;", &perso->NV);

    } else if(!strcmp(temp,"MAXPV")) {

      fscanf(f, "%d;", &perso->MAXPV);

    } else if(!strcmp(temp,"EXP")) {

      fscanf(f, "%d;", &perso->EXP);

    } else if(!strcmp(temp,"PV")) {

      fscanf(f, "%d;", &perso->PV);

    } else if(!strcmp(temp,"FRC")) {

      fscanf(f, "%d;", &perso->FRC);

    } else if(!strcmp(temp,"MGE")) {

      fscanf(f, "%d;", &perso->MGE);

    } else if(!strcmp(temp,"VITATT")) {

      fscanf(f, "%d;", &perso->VITATT);

    } else if(!strcmp(temp,"CRIT")) {

      fscanf(f, "%d;", &perso->CRIT);

    } else if(!strcmp(temp,"CNTR")) {

      fscanf(f, "%d;", &perso->CNTR);

    } else if(!strcmp(temp,"GARDE")) {

      fscanf(f, "%d;", &perso->GARDE);

    } else if(!strcmp(temp,"DEFPHY")) {

      fscanf(f, "%d;", &perso->DEFPHY);

    } else if(!strcmp(temp,"DEFMGE")) {

      fscanf(f, "%d;", &perso->DEFMGE);

    } else if(!strcmp(temp,"AGI")) {

      fscanf(f, "%d;", &perso->AGI);

    } else if(!strcmp(temp,"DEXT")) {

      fscanf(f, "%d;", &perso->DEXT);

    } else if(!strcmp(temp,"PRTAUTO")) {

      fscanf(f, "%d;", &perso->PRTAUTO);

    } else if(!strcmp(temp,"CHANCE")) {

      fscanf(f, "%d;", &perso->CHANCE);

    }

  }

  perso->ATTMIN=perso->FRC;
  perso->ATTMAX=perso->FRC+10;
  perso->delaiAuto=perso->VITATT;
  perso->delaiArt = 0;

  perso->modif[MAXPV] = (float)perso->MAXPV;
  perso->modif[FRC] = (float)perso->FRC;
  perso->modif[MGE] = (float)perso->MGE;
  perso->modif[ATTMIN] = (float)perso->ATTMIN;
  perso->modif[ATTMAX] = (float)perso->ATTMAX;
  perso->modif[VITATT] = (float)perso->VITATT;
  perso->modif[CRIT] = (float)perso->CRIT;
  perso->modif[CNTR] = (float)perso->CNTR;
  perso->modif[DBLATT] = (float)perso->DBLATT;
  perso->modif[GARDE] = (float)perso->GARDE;
  perso->modif[DEFPHY] = (float)perso->DEFPHY;
  perso->modif[DEFMGE] = (float)perso->DEFMGE;
  perso->modif[AGI] = (float)perso->AGI;
  perso->modif[DEXT] = (float)perso->DEXT;
  perso->modif[PRTAUTO] = (float)perso->PRTAUTO;

  for(int i = MAXPV; i <= PRTAUTO; i++) {

    perso->nbDelai[i] = 0;

  }

  perso->enCombat = 0;

  fclose(f);

}






/**
    \fn void delaiModificationPerso()
    \brief décrémente les valeurs de "delaiModif" d'un personnage et inverse leurs effets quand elles sont terminées
*/

void delaiModificationPerso() {

  for(int n = 0; n < 3; n++) {

    equipe[n]->delaiArt--;

    for(int i = 0; i < 15; i++) {

      for(int j = 0; j < equipe[n]->nbDelai[i]; j++) {          //on d�cr�mente toutes les delais des modifications des stats d'un personnage

        equipe[n]->delai[i][j].delai--;

      }

      for(int j = equipe[n]->nbDelai[i]-1; j >= 0; j--) {      //si le delai est inf�rieur � 0 on retire la modification

        if(equipe[n]->delai[i][j].delai < 0) {

          for(int k = j; k < equipe[n]->nbDelai[i]-1; k++) {

            equipe[n]->delai[i][k] =  equipe[n]->delai[i][k+1];

          }

          equipe[n]->modif[i] /= equipe[n]->delai[i][j].valeur;

          equipe[n]->nbDelai[i]--;

        }

      }

    }

  }

}
