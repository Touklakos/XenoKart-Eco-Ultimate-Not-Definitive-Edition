
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "perso.h"


void initPersonnage(Personnage* perso, char fichier[50]) {

    perso->posX = rand()%1280;
    perso->posY = rand()%720;
    perso->vitX = 0;
    perso->vitY = 0;


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

    for(int i = MAXPV; i < PRTAUTO; i++) {

      perso->nbDelai[i] = 0;

    }

    perso->enCombat = 0;

    fclose(f);

}

void deplacementPersonnage(Personnage* perso) {

    perso->posX+=perso->vitX;
    perso->posY+=perso->vitY;

}



void afficherPersonnage(Personnage perso, SDL_Window* screen, SDL_Rect camera) {

    SDL_Rect dest = { perso.posX - perso.image->w/2-camera.x+camera.w, perso.posY - perso.image->h/2-camera.y+camera.h, 0, 0};
    SDL_BlitSurface(perso.image, NULL, SDL_GetWindowSurface(screen), &dest);

}

void delaiModificationPerso(Personnage* perso) {

    for(int i = 0; i < 15; i++) {

        for(int j = 0; j < perso->nbDelai[i]; j++) {          //on d�cr�mente toutes les delais des modifications des stats d'un personnage

                perso->delai[i][j].delai--;

        }

        for(int j = perso->nbDelai[i]-1; j >= 0; j--) {      //si le delai est inf�rieur � 0 on retire la modification

            if(perso->delai[i][j].delai < 0) {

                for(int k = j; k < perso->nbDelai[i]-1; k++) {

                    perso->delai[i][k] =  perso->delai[i][k+1];

                }

                perso->modif[i] /= perso->delai[i][j].valeur;

                perso->nbDelai[i]--;

            }

        }

    }

}


/*Cette fonction v�rifie si un personnage peut utiliser un art de soutien (en fonction du delai depuis sa derni�re utilisation)*/


void utiliseArtBuff(Art* art, Personnage* equipe[3], int indicePersonnage, SDL_Surface *pSurface, degatsTxt dgtsTxt[], int *nbDgtTxt) {

    int j = 0, k = 3, l = -1;

    if(art->CIBLE_ALLIE == groupe) {        //L'art cible tout le groupe

        j = 0;

        k = 3;

    } else if(art->CIBLE_ALLIE == membreGroupe) {  //L'art cible un seul membre du groupe

        j = indicePersonnage;   //même chose que pour "soiMême" (c'est à l'appel de la fonction que l'on demande à l'utilisateur l'indice du personnage ciblé)

        k = j+1;

    } else if(art->CIBLE_ALLIE == allie) {               //L'art cible uniquement les allies du lanceur

        j = 0;

        k = 3;

        l = indicePersonnage; //Dans la boucle on verifie que l'indice du personnage que l'on modifie est different de celui du lanceur

    } else if(art->CIBLE_ALLIE == soiMeme) {             //L'art cible uniquement le lanceur

        j = indicePersonnage; //même chose que pour "membreGroupe" (à l'appel de la fonction le lanceur met son indice de personnage dans "indicePersonnage")

        k = j+1;

    }

    if(art->recup < 0) {

        art->recup = art->delaiRecup[0];

        for(int i = j; i < k; i++) {

          if(art->soin > 0 && equipe[i]->PV < equipe[i]->modif[MAXPV]) {

            int soin = art->soin;

            if(soin > equipe[i]->modif[MAXPV] - equipe[i]->PV) soin = equipe[i]->modif[MAXPV] - equipe[i]->PV;

            if(soin > 0) {

              equipe[i]->PV += soin;

              addDegatTxt(dgtsTxt + (*nbDgtTxt), soin, equipe[i]->posX, equipe[i]->posY-equipe[i]->image->h, soinC);

              (*nbDgtTxt)++;

            }

          }

        }


        for(int z = 0; z < 15; z++) {

            if(art->buff[z].valeur != -1) {

                for(int i = j; i < k; i++) {

                    if(i != l) {

                        equipe[i]->modif[z] *= art->buff[z].valeur;

                        equipe[i]->delai[z][equipe[i]->nbDelai[z]].valeur = art->buff[z].valeur;

                        equipe[i]->delai[z][equipe[i]->nbDelai[z]].delai = art->buff[z].delai;

                        equipe[i]->nbDelai[z]++;

                    }

                }

            }

        }

    }

}