
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "ennemi.h"


/**
  \file ennemi.c
  \brief fonctions des ennemis
  \author Mano Brabant
  \version 0.01
  \date 13 fevrier 2019
*/

Ennemi ennPool[100];

int nbEnnemiPool = 0;

Ennemi ennemis[100];

int nbEnnemi = 0;


/**
    \fn void initEnnemi(Ennemi* ennemi, char fichier[50])
    \brief initialise l'ennemi passé en parametre avec un ficher
    \param ennemi l'ennemi que l'on initialise
    \param fichier le fichier qui contient les information de l'ennemi
*/

void initEnnemi(Ennemi* ennemi, char fichier[50]) {

    ennemi->posX = rand()%1280;
    ennemi->posY = rand()%720;
    ennemi->vitX = 0;
    ennemi->vitY = 0;
    ennemi->orientationAbsolue = 2;
    ennemi->hostilite[0] = 1;
    ennemi->hostilite[1] = 1;
    ennemi->hostilite[2] = 1;
    ennemi->numFrame = 0;


    FILE* f;


    f = fopen(fichier, "r");

    ennemi->NV = 0;
    ennemi->MAXPV = 0;
    ennemi->PV = 0;
    ennemi->FRC = 0;
    ennemi->MGE = 0;
    ennemi->VITATT = 0;
    ennemi->CRIT = 0;
    ennemi->CNTR = 0;
    ennemi->GARDE = 0;
    ennemi->DEFPHY = 0;
    ennemi->DEFMGE = 0;
    ennemi->AGI = 0;
    ennemi->DEXT = 0;
    ennemi->PRTAUTO = 0;
    ennemi->CHANCE = 0;
    ennemi->RES_ETATS[fournaise] = 0;
    ennemi->RES_ETATS[frisson] = 0;
    ennemi->RES_ETATS[poison] = 0;

    ennemi->delaiAuto = ennemi->VITATT;

    if(f) {

        char temp[20];

        char cheminImage[50];

        fscanf(f, "%s", ennemi->nom);

        fscanf(f, "%s", cheminImage);

        while(!feof(f)) {       //on charge les stats �crite dans un fichier

            fscanf(f, "%s : ", temp);

            printf("\n\nJEANNE : %s", temp);

            if(!strcmp(temp,"NV")) {

                    fscanf(f, "%d;", &ennemi->NV);

            } else if(!strcmp(temp,"MAXPV")) {

                    fscanf(f, "%d;", &ennemi->MAXPV);

            } else if(!strcmp(temp,"PV")) {

                    fscanf(f, "%d;", &ennemi->PV);

            } else if(!strcmp(temp,"FRC")) {

                    fscanf(f, "%d;", &ennemi->FRC);

            } else if(!strcmp(temp,"MGE")) {

                    fscanf(f, "%d;", &ennemi->MGE);

            } else if(!strcmp(temp,"VITATT")) {

                    fscanf(f, "%d;", &ennemi->VITATT);

            } else if(!strcmp(temp,"CRIT")) {

                    fscanf(f, "%d;", &ennemi->CRIT);

            } else if(!strcmp(temp,"CNTR")) {

                    fscanf(f, "%d;", &ennemi->CNTR);

            } else if(!strcmp(temp,"GARDE")) {

                    fscanf(f, "%d;", &ennemi->GARDE);

            } else if(!strcmp(temp,"DEFPHY")) {

                    fscanf(f, "%d;", &ennemi->DEFPHY);

            } else if(!strcmp(temp,"DEFMGE")) {

                    fscanf(f, "%d;", &ennemi->DEFMGE);

            } else if(!strcmp(temp,"AGI")) {

                    fscanf(f, "%d;", &ennemi->AGI);

            } else if(!strcmp(temp,"DEXT")) {

                    fscanf(f, "%d;", &ennemi->DEXT);

            } else if(!strcmp(temp,"PRTAUTO")) {

                    fscanf(f, "%d;", &ennemi->PRTAUTO);

            } else if(!strcmp(temp,"CHANCE")) {

                    fscanf(f, "%d;", &ennemi->CHANCE);

            } else if(!strcmp(temp,"RES_FOURNAISE")) {

                    fscanf(f, "%d;", &ennemi->RES_ETATS[fournaise]);

            } else if(!strcmp(temp,"RES_FRISSON")) {

                    fscanf(f, "%d;", &ennemi->RES_ETATS[frisson]);

            } else if(!strcmp(temp,"RES_POISON")) {

                    fscanf(f, "%d;", &ennemi->RES_ETATS[poison]);

            }



        }

        ennemi->ATTMIN=ennemi->FRC;
        ennemi->ATTMAX=ennemi->FRC;
        ennemi->etats[fournaise].valeur = 0;
        ennemi->etats[frisson].valeur = 0;
        ennemi->etats[poison].valeur = 0;
        ennemi->etats[fournaise].delai = 0;
        ennemi->etats[frisson].delai = 0;
        ennemi->etats[poison].delai = 0;

        ennemi->modif[MAXPV] = (float)ennemi->MAXPV;
        ennemi->modif[FRC] = (float)ennemi->FRC;
        ennemi->modif[MGE] = (float)ennemi->MGE;
        ennemi->modif[ATTMIN] = (float)ennemi->ATTMIN;
        ennemi->modif[ATTMAX] = (float)ennemi->ATTMAX;
        ennemi->modif[VITATT] = (float)ennemi->VITATT;
        ennemi->modif[CRIT] = (float)ennemi->CRIT;
        ennemi->modif[CNTR] = (float)ennemi->CNTR;
        ennemi->modif[DBLATT] = (float)ennemi->DBLATT;
        ennemi->modif[GARDE] = (float)ennemi->GARDE;
        ennemi->modif[DEFPHY] = (float)ennemi->DEFPHY;
        ennemi->modif[DEFMGE] = (float)ennemi->DEFMGE;
        ennemi->modif[AGI] = (float)ennemi->AGI;
        ennemi->modif[DEXT] = (float)ennemi->DEXT;
        ennemi->modif[PRTAUTO] = (float)ennemi->PRTAUTO;

        for(int i = MAXPV; i < PRTAUTO; i++) {

          ennemi->nbDelai[i] = 0;

        }

        ennemi->enCombat = 0;

        ennemi->image = IMG_Load("./data/test.png");


        fclose(f);

    }

}


/**
    \fn int cibleEnnemi(Ennemi *ennemi)
    \brief modifie la valeur cible d'un ennemi passé en parametre avec les valeurs du tableau hostilite
    \param ennemi l'ennemi que l'on modifie
*/


int cibleEnnemis() {

  int max = 0;
  int indice = -1;

  for(int n = 0; n < nbEnnemi; n++) {

    for(int i = 0; i < 3; i++) {

      if(max + 100 < ennemis[n].hostilite[i]) {

        max = ennemis[n].hostilite[i];

        indice = i;

      }

    }

    if(indice >= 0) ennemis[n].cible = indice;

  }

  return 0;

}

/**
    \fn void ennemiPoursuit(Ennemi *ennemi, Personnage *perso)
    \brief si un ennemi n'est pas à portée du personnage qu'il cible il se rapproche de lui
    \param ennemi l'ennemi que l'on modifie
    \param perso personnage poursuivit pas l'ennemi
*/

void ennemiPoursuit() {

  for(int i = 0; i < nbEnnemi; i++) {

    int vecX, vecY;

    vecX = equipe[ennemis[i].cible]->posX - ennemis[i].posX;
    vecY = equipe[ennemis[i].cible]->posY - ennemis[i].posY;

    int dis = distance(equipe[ennemis[i].cible]->posX, equipe[ennemis[i].cible]->posY, ennemis[i].posX, ennemis[i].posY)- equipe[ennemis[i].cible]->image->w/2;

    if(ennemis[i].enCombat && dis >= ennemis[i].PRTAUTO/2) {

      ennemis[i].vitX = vecX*VITDPL/dis;

      ennemis[i].vitY = vecY*VITDPL/dis;

    } else {

      ennemis[i].vitX = 0;

      ennemis[i].vitY = 0;

    }

  }

}

/**
    \fn void deplacementEnnemi(Ennemi* ennemi, Personnage *equipe[])
    \brief deplacement de l'ennemi si celui-ci veux bouger
    \param ennemi l'ennemi que l'on deplace
    \param equipe equipe de personnage que poursuit l'ennemi
*/

void deplacementEnnemi() {

  cibleEnnemis();

  ennemiPoursuit();

  for(int i = 0; i < nbEnnemi; i++) {

    ennemis[i].posX+=ennemis[i].vitX;
    ennemis[i].posY+=ennemis[i].vitY;

  }

}



/**
    \fn void afficherEnnemi(Ennemi *ennemi, SDL_Surface *pSurface, SDL_Rect camera, Personnage *equipe[], int etat)
    \brief on affiche l'ennemi sur l'ecran
    \param ennemi l'ennemi que l'on affiche
    \param pSurface fenetre sur laquelle on affiche l'ennemi
    \param camera camera qui represente le centre de l'ecran
    \param equipe equipe de personnage que poursuit l'ennemi si il est en combat
*/


void afficherEnnemis(SDL_Surface *pSurface, SDL_Rect camera) {

  for(int i = 0; i < nbEnnemi; i++) {

    if(ennemis[i].enCombat) {

      orientationPersoCombatAbsolue(ennemis[i].cible);

      ennemis[i].orientationAbsolue = (equipe[ennemis[i].cible]->orientationAbsolue + 2)%4;



    }

    if(ennemis[i].vitX != 0 || ennemis[i].vitY != 0) ennemis[i].numFrame = (ennemis[i].numFrame+1)%60;
  //  else ennemi->numFrame = 0;

    SDL_Rect dest = { ennemis[i].posX - ennemis[i].image->w/2/4-camera.x+camera.w, ennemis[i].posY - ennemis[i].image->h/2/4-camera.y+camera.h, 0, 0};
    SDL_Rect img = { ennemis[i].image->w/4*(ennemis[i].numFrame/15), ennemis[i].image->h/4*ennemis[i].orientationAbsolue, ennemis[i].image->w/4, ennemis[i].image->h/4};

    SDL_BlitSurface(ennemis[i].image, &img, pSurface, &dest);

    if(ennemis[i].enCombat) {

      SDL_Rect rect ={ennemis[i].posX - ennemis[i].image->w/2/4-camera.x+camera.w, ennemis[i].posY - ennemis[i].image->h/2/4-camera.y+camera.h, ennemis[i].PV*ennemis[i].image->w/4/ennemis[i].MAXPV, 5};

      SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 255, 0, 0));

    }

  }

}

/**
    \fn void hudEnnemi(Ennemi *ennemi, SDL_Surface *pSurface, SDL_Rect camera)
    \brief on affiche des information sur l'ennemi
    \param ennemi l'ennemi d'ont on afficher les informations
    \param pSurface fenetre sur laquelle on affiche les informations
    \param camera camera qui represente le centre de l'ecran
*/


void hudEnnemi(SDL_Surface *pSurface, SDL_Rect camera) {

  SDL_Surface *HUD = IMG_Load("./data/hud.png");

  SDL_Surface *nom;

  TTF_Font *police = NULL;

  police = TTF_OpenFont("./data/DejaVuSans.ttf", 20);   //taile de police plus ou moins grande

  SDL_Color couleur = {255,255,255};


  for(int i = 0; i < nbEnnemi; i++) {

    SDL_Rect rect = {ennemis[i].posX - camera.x + camera.w - HUD->w/2, ennemis[i].posY - ennemis[i].image->h/2/4-camera.y+camera.h-HUD->h, 0, 0};

    SDL_BlitSurface(HUD, NULL, pSurface, &rect);


    nom = TTF_RenderText_Solid(police, ennemis[i].nom, couleur);

    SDL_Rect rect2 = {ennemis[i].posX - camera.x + camera.w - nom->w/2, ennemis[i].posY - ennemis[i].image->h/2/4-camera.y+camera.h-HUD->h, 0, 0};

    SDL_BlitSurface(nom, NULL, pSurface, &rect2);

  }

  TTF_CloseFont(police);



}

/**
    \fn int orientationPersoCombatAbsolue(Personnage* perso, Ennemi* ennemi)
    \brief on modifie la valeur de orientaionAbsolue d'un personnage passé en parametre (orientation par rapport à l'ecran)
    \param perso personnage que l'on modifie
    \param ennemi l'ennemi que cible le personnage
*/



int orientationPersoCombatAbsolue(int indice) {


    int vecX, vecY;

    vecX = equipe[indice]->posX - ennemis[equipe[indice]->cible].posX;

    vecY = equipe[indice]->posY - ennemis[equipe[indice]->cible].posY;




    if(vecX < 0 && vecY < 0) {

      if((vecX*-1) > (vecY*-1)) equipe[indice]->orientationAbsolue = gauche;
      else  equipe[indice]->orientationAbsolue = haut;

    } else if(vecX < 0 && vecY > 0) {

      if((vecX*-1) > vecY) equipe[indice]->orientationAbsolue = gauche;
      else  equipe[indice]->orientationAbsolue = bas;

    } else if(vecX > 0 && vecY < 0) {

      if(vecX > (vecY*-1)) equipe[indice]->orientationAbsolue = droite;
      else  equipe[indice]->orientationAbsolue = haut;

    } else if(vecX > 0 && vecY > 0) {

      if(vecX > vecY) equipe[indice]->orientationAbsolue = droite;
      else  equipe[indice]->orientationAbsolue = bas;

    }

    return equipe[indice]->orientationAbsolue;

}


/**
    \fn int orientationPersoCombatRelative(Personnage *equipe[], int indicePersonnage, Ennemi* ennemi)
    \brief on modifie la valeur de orientaionRelative d'un personnage passé en parametre (orientation par rapport à l'ennemi)
    \param perso personnage que l'on modifie
    \param ennemi l'ennemi que cible le personnage
*/

int orientationPersoCombatRelative(int indice) {

    int orientationAbs1 = orientationPersoCombatAbsolue(indice);

    equipe[indice]->orientationRelative = (orientationAbs1 - ennemis[equipe[indice]->cible].orientationAbsolue + 2)%4;

    return equipe[indice]->orientationRelative;

}

/**
    \fn int typeCoupPerso(Personnage *perso, Ennemi *ennemi)
    \brief quand un personnage assene un coup, ce coup est modifié, cela peut être un coup critique, le coup peut-être esquivé, gardé, etc...
    \param perso personnage qui assene le coup
    \param ennemi ennemi qui recoit le coup
*/


int typeCoupPerso(int indice) {

  int precision = -ennemis[equipe[indice]->cible].modif[AGI] + equipe[indice]->modif[DEXT] + 100;

  if(precision > 95) precision = 95;

  if(precision < 5) precision = 5;

  if(rand()%100 > precision) {

    return esquiveC;

  } else if(rand()%100 <= equipe[indice]->modif[CRIT]) {

    return critiqueC;

  } else if(rand()%100 <= ennemis[equipe[indice]->cible].modif[GARDE]) {

    return gardeC;

  }

  return normalC;

}


/**
    \fn int typeCoupEnnemi(Ennemi *ennemi, Personnage *perso)
    \brief quand un ennemi assene un coup, ce coup est modifié, cela peut être un coup critique, le coup peut-être esquivé, gardé, etc...
    \param ennemi ennemi qui assene le coup
    \param perso personnage qui recoit le coup
*/

int typeCoupEnnemi(int indice) {

  int precision = -equipe[ennemis[indice].cible]->modif[AGI] + ennemis[indice].modif[DEXT] + 100;

  if(precision > 95) precision = 95;

  if(precision < 5) precision = 5;

  if(rand()%100 > precision) {

    return esquiveC;

  } else if(rand()%100 <= ennemis[indice].modif[CRIT]) {

    return critiqueC;

  } else if(rand()%100 <= equipe[ennemis[indice].cible]->modif[GARDE]) {

    return gardeC;

  }

  return normalC;

}



/**
    \fn int ennemiAutoAttaque(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief l'ennemi assene une auto attaque à un personnage
    \param equipe equipe de personnage
    \param ennemi ennemi qui assene le coup
    \param indice indice du personnage ciblé
    \param dgtsTxt tableau des texte affichés à l'écran
    \param nbDgtTxt nombre de parametre affichés à l'écran
*/


int ennemiAutoAttaque(int indice) {

    int difference = ennemis[indice].modif[ATTMAX] - ennemis[indice].modif[ATTMIN];
    int random;
    if(difference != 0) {
        random = rand()%difference;     //l'attaque inflige des d�gats compris entre les variables modifATTMIN et modifATTMAX
    } else {
        random = 0;
    }

    eCoup type = typeCoupEnnemi(indice);

    int degats = ennemis[indice].modif[ATTMIN] + random;

    if(type == critiqueC) {

        degats *= 1.5;

    } else if(type == esquiveC) {

        degats = 0;

    } else if(type == gardeC) {

        degats *= 0.5;

    }

    degats = degats*(100-equipe[ennemis[indice].cible]->modif[DEFPHY])/100;       //les d�gats sont r�duit par la d�fence de l'ennemi

    equipe[ennemis[indice].cible]->PV -= degats;
    if(equipe[ennemis[indice].cible]->PV <= 0) ennemis[indice].hostilite[ennemis[indice].cible] = 0;
    else {

      ennemis[indice].hostilite[ennemis[indice].cible] -= degats;

      if(ennemis[indice].hostilite[ennemis[indice].cible] < 0) ennemis[indice].hostilite[ennemis[indice].cible] = 0;

    }
    ennemis[indice].delaiAuto=ennemis[indice].modif[VITATT];

    addDegatTxt(degats, equipe[ennemis[indice].cible]->posX, equipe[ennemis[indice].cible]->posY-equipe[ennemis[indice].cible]->image->h, type);

    return degats;

}


/**
    \fn int attaqueAllie(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief cette fonction verifie si un ennemi peut lancer un auto-attaque sur un personnage (verification de la distance et du delai depuis la derniere frappe)
    \param equipe equipe de personnage
    \param ennemi ennemi qui assene le coup
    \param indice indice du personnage ciblé
    \param dgtsTxt tableau des texte affichés à l'écran
    \param nbDgtTxt nombre de parametre affichés à l'écran
*/

int attaqueAllie(Personnage* equipe[]) {

  for(int i = 0; i < nbEnnemi; i++) {

    if(ennemis[i].PV > 0 && ennemis[i].enCombat) {

      ennemis[i].delaiAuto--;

      if(distance(equipe[ennemis[i].cible]->posX, equipe[ennemis[i].cible]->posY, ennemis[i].posX, ennemis[i].posY) - equipe[ennemis[i].cible]->image->w/2 < ennemis[i].PRTAUTO && ennemis[i].delaiAuto < 0) {

          ennemiAutoAttaque(i);

      }

    }

  }

  return -1;

}


/*Cette fonction calcule les d�gats qu'un personnage inflige � un ennemi avec une auto attaque*/


/**
    \fn int persoAutoAttaque(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief un personnage assene une auto attaque à un ennemi
    \param equipe equipe de personnage
    \param ennemi ennemi qui recoit le coup
    \param indice indice du personnage qui attaque
    \param dgtsTxt tableau des texte affichés à l'écran
    \param nbDgtTxt nombre de parametre affichés à l'écran
*/


int persoAutoAttaque(int indice) {

    int difference = equipe[indice]->modif[ATTMAX] - equipe[indice]->modif[ATTMIN];

    int min;

    if(difference < 0) min = equipe[indice]->modif[ATTMAX];
    else min = equipe[indice]->modif[ATTMIN];

    int random;
    if(difference > 0) {
        random = rand()%difference;     //l'attaque inflige des d�gats compris entre les variables modifATTMIN et modifATTMAX
    } else {
        random = 0;
    }

    eCoup type = typeCoupPerso(indice);

    int degats = min + random;

    if(type == critiqueC) {

        degats *= 1.5;

    } else if(type == esquiveC) {

        degats = 0;

    } else if(type == gardeC) {

        degats *= 0.5;

    }

    degats = degats*(100-ennemis[equipe[indice]->cible].DEFPHY)/100;       //les d�gats sont r�duit par la d�fence de l'ennemi

    ennemis[equipe[indice]->cible].PV -= degats;
    ennemis[equipe[indice]->cible].hostilite[indice] += degats*2;
    equipe[indice]->delaiAuto=(int)equipe[indice]->modif[VITATT];

    addDegatTxt(degats, ennemis[equipe[indice]->cible].posX, ennemis[equipe[indice]->cible].posY-ennemis[equipe[indice]->cible].image->h/4, type);

    ennemis[equipe[indice]->cible].enCombat = 1;

    return degats;

}


/*Cette fonction v�rifie si un personnage peut attaquer un ennemi (en fonction du delai depuis sa derni�re attaque et de sa distance)*/

/**
    \fn int attaqueEnnemi(Personnage* equipe[], Ennemi ennemis[], int indice, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief cette fonction verifie si un personnage peut lancer un auto-attaque sur un ennemi (verification de la distance et du delai depuis la derniere frappe)
    \param equipe equipe de personnage
    \param ennemi ennemi qui recoit le coup
    \param dgtsTxt tableau des texte affichés à l'écran
    \param nbDgtTxt nombre de parametre affichés à l'écran
*/

int attaqueEnnemi(Personnage* equipe[]) {

  for(int i = 0; i < 3; i++) {

    if(equipe[i]->PV > 0) {

      if(equipe[i]->delaiArt < 0) {

        equipe[i]->delaiAuto--;

        orientationPersoCombatRelative(i);

        if(distance(equipe[i]->posX, equipe[i]->posY, ennemis[equipe[i]->cible].posX, ennemis[equipe[i]->cible].posY) - ennemis[equipe[i]->cible].image->w/2/4 < equipe[i]->PRTAUTO && equipe[i]->delaiAuto < 0) {

            persoAutoAttaque(i);

        }

      }

    }

  }

  return 0;

}


/*Cette fonction calcule les d�gats qu'un personnage inflige � un ennemi en utilisant un de ses arts offensif*/

/**
    \fn int lanceArt(Art *art, Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief un personnage utilise un art sur un ennemi
    \param art art que le personnage utilise
    \param equipe equipe de personnage
    \param ennemi ennemi qui recoit le coup
    \param indice indice du personnage qui utilise l'art
    \param dgtsTxt tableau des texte affichés à l'écran
    \param nbDgtTxt nombre de parametre affichés à l'écran
*/

int lanceArt(int indiceArt, int indicePersonnage) {

    orientationPersoCombatRelative(indicePersonnage);

    int difference = ArtJeu[indicePersonnage][indiceArt]->DMGMAX[equipe[indicePersonnage]->orientationRelative] - ArtJeu[indicePersonnage][indiceArt]->DMGMIN[equipe[indicePersonnage]->orientationRelative];
    int random;
    if(difference != 0) {
        random = rand()%difference;
    } else {
        random = 0;
    }

    int degats = ArtJeu[indicePersonnage][indiceArt]->DMGMIN[equipe[indicePersonnage]->orientationRelative] + random;

    if(ArtJeu[indicePersonnage][indiceArt]->TYPE == physique) degats = degats*(100-ennemis[equipe[indicePersonnage]->cible].DEFPHY)/100;

    else if(ArtJeu[indicePersonnage][indiceArt]->TYPE == ether) degats = degats*(100-ennemis[equipe[indicePersonnage]->cible].DEFMGE)/100;

    for(int i = 0; i < 15; i++) {

      if(ArtJeu[indicePersonnage][indiceArt]->debuff[equipe[indicePersonnage]->orientationRelative][i].valeur > -1) {

        ennemis[equipe[indicePersonnage]->cible].modif[i] *= ArtJeu[indicePersonnage][indiceArt]->debuff[equipe[indicePersonnage]->orientationRelative][i].valeur;

        ennemis[equipe[indicePersonnage]->cible].delai[i][ennemis[equipe[indicePersonnage]->cible].nbDelai[i]].valeur = ArtJeu[indicePersonnage][indiceArt]->debuff[equipe[indicePersonnage]->orientationRelative][i].valeur;

        ennemis[equipe[indicePersonnage]->cible].delai[i][ennemis[equipe[indicePersonnage]->cible].nbDelai[i]].delai = ArtJeu[indicePersonnage][indiceArt]->debuff[equipe[indicePersonnage]->orientationRelative][i].delai;

        ennemis[equipe[indicePersonnage]->cible].nbDelai[i]++;

      }

    }



    ennemis[equipe[indicePersonnage]->cible].PV -= degats;
    ennemis[equipe[indicePersonnage]->cible].hostilite[indicePersonnage] += degats*2;
    ArtJeu[indicePersonnage][indiceArt]->recup = ArtJeu[indicePersonnage][indiceArt]->delaiRecup[equipe[indicePersonnage]->orientationRelative];
    ArtJeu[indicePersonnage][indiceArt]->delaiRecupAct = ArtJeu[indicePersonnage][indiceArt]->delaiRecup[equipe[indicePersonnage]->orientationRelative];
    equipe[indicePersonnage]->delaiArt = ArtJeu[indicePersonnage][indiceArt]->delaiAnimation;

    ennemis[equipe[indicePersonnage]->cible].etats[fournaise].valeur += ArtJeu[indicePersonnage][indiceArt]->etats[equipe[indicePersonnage]->orientationRelative][fournaise];
    ennemis[equipe[indicePersonnage]->cible].hostilite[indicePersonnage] += ArtJeu[indicePersonnage][indiceArt]->etats[equipe[indicePersonnage]->orientationRelative][fournaise]*ennemis[equipe[indicePersonnage]->cible].RES_ETATS[fournaise]/100*3;
    ennemis[equipe[indicePersonnage]->cible].etats[frisson].valeur += ArtJeu[indicePersonnage][indiceArt]->etats[equipe[indicePersonnage]->orientationRelative][frisson];
    ennemis[equipe[indicePersonnage]->cible].hostilite[indicePersonnage] += ArtJeu[indicePersonnage][indiceArt]->etats[equipe[indicePersonnage]->orientationRelative][frisson]*ennemis[equipe[indicePersonnage]->cible].RES_ETATS[frisson]/100*3;
    ennemis[equipe[indicePersonnage]->cible].etats[poison].valeur += ArtJeu[indicePersonnage][indiceArt]->etats[equipe[indicePersonnage]->orientationRelative][poison];
    ennemis[equipe[indicePersonnage]->cible].hostilite[indicePersonnage] += ArtJeu[indicePersonnage][indiceArt]->etats[equipe[indicePersonnage]->orientationRelative][poison]*ennemis[equipe[indicePersonnage]->cible].RES_ETATS[poison]/100*3;

    for(int i = 0; i < 3; i++) {

        if(ennemis[equipe[indicePersonnage]->cible].etats[i].valeur == ArtJeu[indicePersonnage][indiceArt]->etats[equipe[indicePersonnage]->orientationRelative][i]) ennemis[equipe[indicePersonnage]->cible].etats[i].delai = 60;

    }

    addDegatTxt(degats, ennemis[equipe[indicePersonnage]->cible].posX, ennemis[equipe[indicePersonnage]->cible].posY-ennemis[equipe[indicePersonnage]->cible].image->h/4, normalC);

    ennemis[equipe[indicePersonnage]->cible].enCombat = 1;

    return degats;

}


/*Cette focntion v�rifie si un personnage peut utiliser un art offensif sur un ennemi (en fonction du delai depuis sa derni�re utilisation et de sa distance)*/

/**
    \fn int attaqueEnnemi(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief Cette fonction vérifie si un personnage peut utiliser un art offensif sur un ennemi (en fonction du delai depuis sa derniére utilisation et de sa distance)
    \param art art que le personnage utilise
    \param equipe equipe de personnage
    \param ennemi ennemi qui recoit le coup
    \param indice indice du personnage qui attaque
    \param dgtsTxt tableau des texte affichés à l'écran
    \param nbDgtTxt nombre de parametre affichés à l'écran
*/

int utiliseArt(int indiceArt, int indicePersonnage) {

  if(equipe[indicePersonnage]->PV > 0) {

    orientationPersoCombatRelative(indicePersonnage);

    fprintf(stderr, "%d : %d : %d : %d\n", equipe[indicePersonnage]->posX, equipe[indicePersonnage]->posY, ennemis[equipe[indicePersonnage]->cible].posX, ennemis[equipe[indicePersonnage]->cible].posY);

    if(distance(equipe[indicePersonnage]->posX, equipe[indicePersonnage]->posY, ennemis[equipe[indicePersonnage]->cible].posX, ennemis[equipe[indicePersonnage]->cible].posY) - ennemis[equipe[indicePersonnage]->cible].image->w/2/4 < ArtJeu[indicePersonnage][indiceArt]->PRTART[equipe[indicePersonnage]->orientationRelative] && ArtJeu[indicePersonnage][indiceArt]->recup < 0) {

        return lanceArt(indiceArt, indicePersonnage);

    }

  }

  return -1;

}

/**
    \fn int etatEnnemi(Ennemi *ennemi, int type, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief cette fonction vérifie l'état d'un ennemi (si il brule, si il est empoisonné etc...)
    \param ennemi ennemi que l'on modifie
    \param type type d'etat (fournaise, frisson, poison, ect...)
    \param dgtsTxt tableau des texte affichés à l'écran
    \param nbDgtTxt nombre de parametre affichés à l'écran
*/

int etatEnnemi() {


  for(int i = 0; i < nbEnnemi; i++) {

    for(int t = 0; t < 3; t++) {


      if(ennemis[i].etats[t].delai < 0) {

        ennemis[i].etats[t].valeur -= ennemis[i].etats[t].valeur*ennemis[i].RES_ETATS[t]/100;

        if(ennemis[i].etats[t].valeur < 100) {

          ennemis[i].etats[t].valeur = 0;

        } else {

          ennemis[i].PV -= ennemis[i].etats[t].valeur;

          int ret = ennemis[i].etats[t].valeur;

          ennemis[i].etats[t].delai = 120;

          eCoup typeC;

          if(t == fournaise) {

            typeC = fournaiseC;

          } else if(t == frisson) {

            typeC = frissonC;

          } else if(t == poison) {

            typeC = poisonC;

          }

          addDegatTxt(ret, ennemis[i].posX, ennemis[i].posY-ennemis[i].image->h/4, typeC);

        }

      }

    }

  }

  return -1;

}

/*Si les delais sont �gaux alors on les modifies l�g�rement pour que l'affichage des d�gats soit lisible*/

/**
    \fn void delaiEtat(Ennemi *ennemi)
    \brief cette fonction modifie les delai des etat d'un ennemi pour que les degats ne soit pas affiché en même temps, pour plus de lisibilité
    \param ennemi ennemi que l'on modifie
*/

void delaiEtatEnnemis() {

  for(int i = 0; i < nbEnnemi; i++) {

    if(ennemis[i].etats[fournaise].delai == ennemis[i].etats[frisson].delai) ennemis[i].etats[frisson].delai -= 10;
    if(ennemis[i].etats[fournaise].delai == ennemis[i].etats[poison].delai) ennemis[i].etats[poison].delai -= 10;
    if(ennemis[i].etats[frisson].delai == ennemis[i].etats[poison].delai) ennemis[i].etats[poison].delai -= 10;

    ennemis[i].etats[fournaise].delai--;
    ennemis[i].etats[frisson].delai--;
    ennemis[i].etats[poison].delai--;

  }


}

/**
    \fn void delaiModificationEnnemi(Ennemi *ennemi)
    \brief décrémente les valeurs de "delaiModif" d'un ennemi et inverse leurs effets quand elles sont terminées
    \param ennemi ennemi que l'on modifie
*/

void delaiModificationEnnemi() {

  for(int n = 0; n < nbEnnemi; n++) {

    for(int i = 0; i < 15; i++) {

      for(int j = 0; j < ennemis[n].nbDelai[i]; j++) {          //on d�cr�mente toutes les delais des modifications des stats d'un personnage

        ennemis[n].delai[i][j].delai--;

      }

      for(int j = ennemis[n].nbDelai[i]-1; j >= 0; j--) {      //si le delai est inf�rieur � 0 on retire la modification

        if(ennemis[n].delai[i][j].delai < 0) {

          for(int k = j; k < ennemis[n].nbDelai[i]-1; k++) {

            ennemis[n].delai[i][k] =  ennemis[n].delai[i][k+1];

          }

          ennemis[n].modif[i] /= ennemis[n].delai[i][j].valeur;

          ennemis[n].nbDelai[i]--;

        }

      }

    }

  }

}


/**
    \fn void persoPoursuit(Personnage *perso, Ennemi *ennemi)
    \brief les personnage qui ne sont pas controlé par le joueur se dirige automatiquement vers l'ennemi qu'ils ciblent
    \param perso personnage qui poursuit l'ennemi
    \param ennemi ennemi qui est poursuivis
*/


void persoPoursuit(int indicePersonnage) {

  for(int i = 0; i < 3; i++) {

    if(i != indicePersonnage && equipe[i]->enCombat) {

      int vecX, vecY;

      vecX = ennemis[equipe[i]->cible].posX - equipe[i]->posX;
      vecY = ennemis[equipe[i]->cible].posY - equipe[i]->posY;

      int dis = distance(equipe[i]->posX, equipe[i]->posY, ennemis[equipe[i]->cible].posX, ennemis[equipe[i]->cible].posY)- equipe[i]->image->w/2;

      if(dis >= equipe[i]->PRTAUTO) {

        equipe[i]->vitX = vecX*VITDPL/dis;

        equipe[i]->vitY = vecY*VITDPL/dis;

      } else {

        equipe[i]->vitX = 0;

        equipe[i]->vitY = 0;

      }

    }

  }

}


/**
    \fn void deplacementPersonnage(Personnage* equipe[], int indicePersonnage, Ennemi ennemis[])
    \brief deplacement des personnages
    \param equipe equipe des personnages
*/


void deplacementPersonnage() {

  for(int i = 0; i < 3; i++) {


    if(equipe[i]->delaiArt >= 0) {

      equipe[i]->vitX = 0;
      equipe[i]->vitY = 0;

    }

      equipe[i]->posX+=equipe[i]->vitX;
      equipe[i]->posY+=equipe[i]->vitY;


  }

}


/*Cette fonction v�rifie si un personnage peut utiliser un art de soutien (en fonction du delai depuis sa derni�re utilisation)*/



/**
    \fn void utiliseArtBuff(Art* art, Personnage* equipe[], int indicePersonnage, SDL_Surface *pSurface, degatsTxt dgtsTxt[], int *nbDgtTxt)
    \brief Cette fonction vérifie si un personnage peut utiliser un art de soutien (en fonction du delai depuis sa dernière utilisation)
    \param art art quel le personnage utilise
    \param equipe equipe qui profite des bonus
    \param indicePersonnage indice du personnage qui utilise l'art
    \param pSurface fenetre sur laquelle on affiche les information de l'art (si il soigne on affiche la valeur de soin en vert au dessus des personnages soignés
    \param dgtsTxt tableau des textes affiché sur l'écran
    \param nbDgtTxt nombre de degats affiché sur l'écran
*/

void utiliseArtBuff(int indiceArt, int indicePersonnage, int cible) {

    int j = 0, k = 3, l = -1;

    if(ArtJeu[indicePersonnage][indiceArt]->CIBLE_ALLIE == groupe) {        //L'art cible tout le groupe

        j = 0;

        k = 3;

    } else if(ArtJeu[indicePersonnage][indiceArt]->CIBLE_ALLIE == membreGroupe) {  //L'art cible un seul membre du groupe

        j = cible;   //même chose que pour "soiMême" (c'est à l'appel de la fonction que l'on demande à l'utilisateur l'indice du personnage ciblé)

        k = j+1;

    } else if(ArtJeu[indicePersonnage][indiceArt]->CIBLE_ALLIE == allie) {               //L'art cible uniquement les allies du lanceur

        j = 0;

        k = 3;

        l = indicePersonnage; //Dans la boucle on verifie que l'indice du personnage que l'on modifie est different de celui du lanceur

    } else if(ArtJeu[indicePersonnage][indiceArt]->CIBLE_ALLIE == soiMeme) {             //L'art cible uniquement le lanceur

        j = indicePersonnage; //même chose que pour "membreGroupe" (à l'appel de la fonction le lanceur met son indice de personnage dans "indicePersonnage")

        k = j+1;

    }

    if(ArtJeu[indicePersonnage][indiceArt]->recup < 0) {

        ArtJeu[indicePersonnage][indiceArt]->recup = ArtJeu[indicePersonnage][indiceArt]->delaiRecup[0];
        ArtJeu[indicePersonnage][indiceArt]->delaiRecupAct = ArtJeu[indicePersonnage][indiceArt]->delaiRecup[0];

        equipe[indicePersonnage]->delaiArt = ArtJeu[indicePersonnage][indiceArt]->delaiAnimation;



        for(int i = j; i < k; i++) {

          if(ArtJeu[indicePersonnage][indiceArt]->soin > 0 && equipe[i]->PV < equipe[i]->modif[MAXPV]) {

            int soin = ArtJeu[indicePersonnage][indiceArt]->soin;

            if(soin > equipe[i]->modif[MAXPV] - equipe[i]->PV) soin = equipe[i]->modif[MAXPV] - equipe[i]->PV;

            if(soin > 0) {

              equipe[i]->PV += soin;

              addDegatTxt(soin, equipe[i]->posX, equipe[i]->posY-equipe[i]->image->h, soinC);

            }

          }

        }


        for(int z = 0; z < 15; z++) {

            if(ArtJeu[indicePersonnage][indiceArt]->buff[z].valeur != -1) {

                for(int i = j; i < k; i++) {

                    if(i != l) {

                        equipe[i]->modif[z] *= ArtJeu[indicePersonnage][indiceArt]->buff[z].valeur;

                        equipe[i]->delai[z][equipe[i]->nbDelai[z]].valeur = ArtJeu[indicePersonnage][indiceArt]->buff[z].valeur;

                        equipe[i]->delai[z][equipe[i]->nbDelai[z]].delai = ArtJeu[indicePersonnage][indiceArt]->buff[z].delai;

                        equipe[i]->nbDelai[z]++;

                    }

                }

            }

        }

    }

}
