
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "ennemi.h"

void initEnnemi(Ennemi* ennemi, char fichier[50]) {

    ennemi->posX = rand()%1280;
    ennemi->posY = rand()%720;
    ennemi->vitX = 0;
    ennemi->vitY = 0;
    ennemi->orientationAbsolue = 2;
    ennemi->hostilite[0] = 1;
    ennemi->hostilite[1] = 1;
    ennemi->hostilite[2] = 1;


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

        ennemi->image[0] = IMG_Load(cheminImage);
        ennemi->image[1] = IMG_Load("./data/ZanzaGauche.png");
        ennemi->image[2] = IMG_Load("./data/ZanzaDos.png");
        ennemi->image[3] = IMG_Load("./data/ZanzaDroite.png");

        fclose(f);

    }

}


int cibleEnnemi(Ennemi *ennemi) {

  int max = 0;
  int indice = -1;

  for(int i = 0; i < 3; i++) {

    if(max < ennemi->hostilite[i]) {

      max = ennemi->hostilite[i];

      indice = i;

    }

  }

  if(indice == -1) return -1;

  ennemi->cible = indice;

  return 0;

}


void ennemiPoursuit(Ennemi *ennemi, Personnage *perso) {

  int vecX, vecY;

  vecX = perso->posX - ennemi->posX;
  vecY = perso->posY - ennemi->posY;

  int dis = distance(perso->posX, perso->posY, ennemi->posX, ennemi->posY)- perso->image->w/2;

  printf("\nPerso = %d:%d\n", perso->posX, perso->posY);
  printf("\nEnnemi = %d:%d\n", ennemi->posX, ennemi->posY);


  printf("\nIncoming !!! : %d\n", dis);

  if(dis >= ennemi->PRTAUTO) {

    ennemi->vitX = vecX*VITDPL/dis;

    ennemi->vitY = vecY*VITDPL/dis;

  } else {

    ennemi->vitX = 0;

    ennemi->vitY = 0;

  }

  printf("\nEnnemi = %d:%d\n", ennemi->vitX, ennemi->vitY);


}

void deplacementEnnemi(Ennemi* ennemi, Personnage *equipe[]) {

    cibleEnnemi(ennemi);

    ennemiPoursuit(ennemi, equipe[ennemi->cible]);

    ennemi->posX+=ennemi->vitX;
    ennemi->posY+=ennemi->vitY;

}



void afficherEnnemi(Ennemi *ennemi, SDL_Surface *pSurface, SDL_Rect camera, Personnage *equipe[], int etat) {


    if(ennemi->enCombat) {

      cibleEnnemi(ennemi);

      ennemi->orientationAbsolue = (equipe[ennemi->cible]->orientationAbsolue + 2)%4;

    }

    SDL_Rect dest = { ennemi->posX - ennemi->image[ennemi->orientationAbsolue]->w/2-camera.x+camera.w, ennemi->posY - ennemi->image[ennemi->orientationAbsolue]->h/2-camera.y+camera.h, 0, 0};
    SDL_BlitSurface(ennemi->image[ennemi->orientationAbsolue], NULL, pSurface, &dest);

    if(ennemi->enCombat) {

      SDL_Rect rect ={ennemi->posX - ennemi->image[ennemi->orientationAbsolue]->w/2-camera.x+camera.w, ennemi->posY - ennemi->image[ennemi->orientationAbsolue]->h/2-camera.y+camera.h, ennemi->PV*ennemi->image[ennemi->orientationAbsolue]->w/ennemi->MAXPV, 5};

      SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 255, 0, 0));

  }

}


void hudEnnemi(Ennemi *ennemi, SDL_Surface *pSurface, SDL_Rect camera) {

  SDL_Surface *HUD = IMG_Load("./data/hud.png");

  SDL_Rect rect = {ennemi->posX - camera.x + camera.w - HUD->w/2, ennemi->posY - ennemi->image[ennemi->orientationAbsolue]->h/2-camera.y+camera.h-HUD->h, 0, 0};

  SDL_BlitSurface(HUD, NULL, pSurface, &rect);


  SDL_Surface *nom;

  TTF_Font *police = NULL;

  police = TTF_OpenFont("./data/DejaVuSans.ttf", 20);   //taile de police plus ou moins grande

  SDL_Color couleur = {255,255,255};

  nom = TTF_RenderText_Solid(police, ennemi->nom, couleur);

  SDL_Rect rect2 = {ennemi->posX - camera.x + camera.w - nom->w/2, ennemi->posY - ennemi->image[ennemi->orientationAbsolue]->h/2-camera.y+camera.h-HUD->h, 0, 0};

  SDL_BlitSurface(nom, NULL, pSurface, &rect2);

  TTF_CloseFont(police);


}


int orientationPersoCombatAbsolue(Personnage* perso, Ennemi* ennemi) {


    int vecX, vecY;

    vecX = perso->posX - ennemi->posX;

    vecY = perso->posY - ennemi->posY;



    if(vecX < 0 && vecY < 0) {

      if((vecX*-1) > (vecY*-1)) perso->orientationAbsolue = gauche;
      else  perso->orientationAbsolue = haut;

    } else if(vecX < 0 && vecY > 0) {

      if((vecX*-1) > vecY) perso->orientationAbsolue = gauche;
      else  perso->orientationAbsolue = bas;

    } else if(vecX > 0 && vecY < 0) {

      if(vecX > (vecY*-1)) perso->orientationAbsolue = droite;
      else  perso->orientationAbsolue = haut;

    } else if(vecX > 0 && vecY > 0) {

      if(vecX > vecY) perso->orientationAbsolue = droite;
      else  perso->orientationAbsolue = bas;

    }

    return perso->orientationAbsolue;

}



int orientationPersoCombatRelative(Personnage *equipe[], int indicePersonnage, Ennemi* ennemi) {


    int orientationAbs1 = orientationPersoCombatAbsolue(equipe[indicePersonnage], ennemi);

    equipe[indicePersonnage]->orientationRelative = (orientationAbs1 - ennemi->orientationAbsolue + 2)%4;

    return equipe[indicePersonnage]->orientationRelative;

}


int typeCoupPerso(Personnage *perso, Ennemi *ennemi) {

  int precision = -ennemi->modif[AGI] + perso->modif[DEXT] + 100;

  if(precision > 95) precision = 95;

  if(precision < 5) precision = 5;

  if(rand()%100 > precision) {

    return esquiveC;

  } else if(rand()%100 <= perso->modif[CRIT]) {

    return critiqueC;

  } else if(rand()%100 <= ennemi->modif[GARDE]) {

    return gardeC;

  }

  return normalC;

}


int typeCoupEnnemi(Ennemi *ennemi, Personnage *perso) {

  int precision = -perso->modif[AGI] + ennemi->modif[DEXT] + 100;

  if(precision > 95) precision = 95;

  if(precision < 5) precision = 5;

  if(rand()%100 > precision) {

    return esquiveC;

  } else if(rand()%100 <= ennemi->modif[CRIT]) {

    return critiqueC;

  } else if(rand()%100 <= perso->modif[GARDE]) {

    return gardeC;

  }

  return normalC;

}




int ennemiAutoAttaque(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt) {

    int difference = ennemi->modif[ATTMAX] - ennemi->modif[ATTMIN];
    int random;
    if(difference != 0) {
        random = rand()%difference;     //l'attaque inflige des d�gats compris entre les variables modifATTMIN et modifATTMAX
    } else {
        random = 0;
    }

    eCoup type = typeCoupEnnemi(ennemi, equipe[indice]);

    int degats = ennemi->modif[ATTMIN] + random;

    if(type == critiqueC) {

        degats *= 1.5;

    } else if(type == esquiveC) {

        degats = 0;

    } else if(type == gardeC) {

        degats *= 0.5;

    }

    degats = degats*(100-equipe[indice]->modif[DEFPHY])/100;       //les d�gats sont r�duit par la d�fence de l'ennemi

    equipe[indice]->PV -= degats;
    if(equipe[indice]->PV <= 0) ennemi->hostilite[indice] = 0;
    else {

      ennemi->hostilite[indice] -= degats;

      if(ennemi->hostilite[indice] < 0) ennemi->hostilite[indice] = 0;

    }
    ennemi->delaiAuto=ennemi->modif[VITATT];

    addDegatTxt(dgtsTxt + (*nbDgtTxt), degats, equipe[indice]->posX, equipe[indice]->posY-equipe[indice]->image->h, type);

    (*nbDgtTxt)++;

    return degats;

}



int attaqueAllie(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt) {

  if(ennemi->PV > 0) {

    ennemi->delaiAuto--;

    if(distance(equipe[indice]->posX, equipe[indice]->posY, ennemi->posX, ennemi->posY) - equipe[indice]->image->w/2 < ennemi->PRTAUTO && ennemi->delaiAuto < 0) {

        return ennemiAutoAttaque(equipe, ennemi, indice, dgtsTxt, nbDgtTxt);

    }

  }

  return -1;

}


/*Cette fonction calcule les d�gats qu'un personnage inflige � un ennemi avec une auto attaque*/

int persoAutoAttaque(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt) {

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

    eCoup type = typeCoupPerso(equipe[indice], ennemi);

    int degats = min + random;

    if(type == critiqueC) {

        degats *= 1.5;

    } else if(type == esquiveC) {

        degats = 0;

    } else if(type == gardeC) {

        degats *= 0.5;

    }

    degats = degats*(100-ennemi->DEFPHY)/100;       //les d�gats sont r�duit par la d�fence de l'ennemi

    ennemi->PV -= degats;
    ennemi->hostilite[indice] += degats*2;
    equipe[indice]->delaiAuto=(int)equipe[indice]->modif[VITATT];

    addDegatTxt(dgtsTxt + (*nbDgtTxt), degats, ennemi->posX, ennemi->posY-ennemi->image[0]->h, type);

    (*nbDgtTxt)++;

    ennemi->enCombat = 1;

    return degats;

}


/*Cette fonction v�rifie si un personnage peut attaquer un ennemi (en fonction du delai depuis sa derni�re attaque et de sa distance)*/


int attaqueEnnemi(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt) {

  if(equipe[indice]->PV > 0) {

    equipe[indice]->delaiAuto--;

    orientationPersoCombatRelative(equipe, indice, ennemi);

    if(distance(equipe[indice]->posX, equipe[indice]->posY, ennemi->posX, ennemi->posY) - ennemi->image[0]->w/2 < equipe[indice]->PRTAUTO && equipe[indice]->delaiAuto < 0) {

        return persoAutoAttaque(equipe, ennemi, indice, dgtsTxt, nbDgtTxt);

    }

  }

  return -1;

}


/*Cette fonction calcule les d�gats qu'un personnage inflige � un ennemi en utilisant un de ses arts offensif*/

int lanceArt(Art *art, Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt) {

    orientationPersoCombatRelative(equipe, indice, ennemi);

    int difference = art->DMGMAX[equipe[indice]->orientationRelative] - art->DMGMIN[equipe[indice]->orientationRelative];
    int random;
    if(difference != 0) {
        random = rand()%difference;
    } else {
        random = 0;
    }

    int degats = art->DMGMIN[equipe[indice]->orientationRelative] + random;

    if(art->TYPE == physique) degats = degats*(100-ennemi->DEFPHY)/100;

    else if(art->TYPE == ether) degats = degats*(100-ennemi->DEFMGE)/100;

    for(int i = 0; i < 15; i++) {

      if(art->debuff[equipe[indice]->orientationRelative][i].valeur > -1) {

        ennemi->modif[i] *= art->debuff[equipe[indice]->orientationRelative][i].valeur;

        ennemi->delai[i][ennemi->nbDelai[i]].valeur = art->debuff[equipe[indice]->orientationRelative][i].valeur;

        ennemi->delai[i][ennemi->nbDelai[i]].delai = art->debuff[equipe[indice]->orientationRelative][i].delai;

        ennemi->nbDelai[i]++;

      }

    }



    ennemi->PV -= degats;
    ennemi->hostilite[indice] += degats*2;
    art->recup = art->delaiRecup[equipe[indice]->orientationRelative];
    ennemi->etats[fournaise].valeur += art->etats[equipe[indice]->orientationRelative][fournaise];
    ennemi->hostilite[indice] += art->etats[equipe[indice]->orientationRelative][fournaise]*ennemi->RES_ETATS[fournaise]/100;
    ennemi->etats[frisson].valeur += art->etats[equipe[indice]->orientationRelative][frisson];
    ennemi->hostilite[indice] += art->etats[equipe[indice]->orientationRelative][frisson]*ennemi->RES_ETATS[frisson]/100;
    ennemi->etats[poison].valeur += art->etats[equipe[indice]->orientationRelative][poison];
    ennemi->hostilite[indice] += art->etats[equipe[indice]->orientationRelative][poison]*ennemi->RES_ETATS[poison]/100;

    for(int i = 0; i < 3; i++) {

        if(ennemi->etats[i].valeur == art->etats[equipe[indice]->orientationRelative][i]) ennemi->etats[i].delai = 60;

    }

    addDegatTxt(dgtsTxt + (*nbDgtTxt), degats, ennemi->posX, ennemi->posY-ennemi->image[0]->h, normalC);

    (*nbDgtTxt)++;

    ennemi->enCombat = 1;

    return degats;

}


/*Cette focntion v�rifie si un personnage peut utiliser un art offensif sur un ennemi (en fonction du delai depuis sa derni�re utilisation et de sa distance)*/

int utiliseArt(Art* art, Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt) {

  if(equipe[indice]->PV > 0) {

    orientationPersoCombatRelative(equipe, indice, ennemi);

    if(distance(equipe[indice]->posX, equipe[indice]->posY, ennemi->posX, ennemi->posY) - ennemi->image[0]->w/2 < art->PRTART[equipe[indice]->orientationRelative] && art->recup < 0) {

        return lanceArt(art, equipe, ennemi, indice, dgtsTxt, nbDgtTxt);

    }

  }

  return -1;

}


int etatEnnemi(Ennemi *ennemi, int type, degatsTxt dgtsTxt[], int *nbDgtTxt) {

    if(ennemi->etats[type].delai < 0) {

        ennemi->etats[type].valeur -= ennemi->etats[type].valeur*ennemi->RES_ETATS[type]/100;

        if(ennemi->etats[type].valeur < 100) {

            ennemi->etats[type].valeur = 0;
            return -1;

        }

        ennemi->PV -= ennemi->etats[type].valeur;

        int ret = ennemi->etats[type].valeur;

        ennemi->etats[type].delai = 120;

        eCoup typeC;

        if(type == fournaise) {

          typeC = fournaiseC;

        } else if(type == frisson) {

          typeC = frissonC;

        } else if(type == poison) {

          typeC = poisonC;


        }

        addDegatTxt(dgtsTxt + (*nbDgtTxt), ret, ennemi->posX, ennemi->posY-ennemi->image[0]->h, typeC);

        (*nbDgtTxt)++;

        return ret;

    }

    return -1;

}

/*Si les delais sont �gaux alors on les modifies l�g�rement pour que l'affichage des d�gats soit lisible*/

void delaiEtat(Ennemi *ennemi) {

    if(ennemi->etats[fournaise].delai == ennemi->etats[frisson].delai) ennemi->etats[frisson].delai -= 10;
    if(ennemi->etats[fournaise].delai == ennemi->etats[poison].delai) ennemi->etats[poison].delai -= 10;
    if(ennemi->etats[frisson].delai == ennemi->etats[poison].delai) ennemi->etats[poison].delai -= 10;

    ennemi->etats[fournaise].delai--;
    ennemi->etats[frisson].delai--;
    ennemi->etats[poison].delai--;


}


void delaiModificationEnnemi(Ennemi* ennemi) {

    for(int i = 0; i < 15; i++) {

        for(int j = 0; j < ennemi->nbDelai[i]; j++) {          //on d�cr�mente toutes les delais des modifications des stats d'un personnage

                ennemi->delai[i][j].delai--;

        }

        for(int j = ennemi->nbDelai[i]-1; j >= 0; j--) {      //si le delai est inf�rieur � 0 on retire la modification

            if(ennemi->delai[i][j].delai < 0) {

                for(int k = j; k < ennemi->nbDelai[i]-1; k++) {

                    ennemi->delai[i][k] =  ennemi->delai[i][k+1];

                }

                ennemi->modif[i] /= ennemi->delai[i][j].valeur;

                ennemi->nbDelai[i]--;

            }

        }

    }

}

void persoPoursuit(Personnage *perso, Ennemi *ennemi) {


  int vecX, vecY;

  vecX = ennemi->posX - perso->posX;
  vecY = ennemi->posY - perso->posY;

  int dis = distance(perso->posX, perso->posY, ennemi->posX, ennemi->posY)- perso->image->w/2;

  if(dis >= perso->PRTAUTO) {

    perso->vitX = vecX*VITDPL/dis;

    perso->vitY = vecY*VITDPL/dis;

  } else {

    perso->vitX = 0;

    perso->vitY = 0;

  }

  printf("\nPersoVit = %d:%d\n", perso->vitX, perso->vitY);

}


void deplacementPersonnage(Personnage* equipe[], int indicePersonnage, Ennemi ennemis[]) {

  for(int i = 0; i < 3; i++) {

    if(i != indicePersonnage && equipe[i]->enCombat) {

      persoPoursuit(equipe[i], ennemis+(equipe[i]->cible));

    }

    equipe[i]->posX+=equipe[i]->vitX;
    equipe[i]->posY+=equipe[i]->vitY;

  }

}
