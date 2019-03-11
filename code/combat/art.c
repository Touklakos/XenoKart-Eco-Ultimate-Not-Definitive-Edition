
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "art.h"

int initArt(Art *art, char fichier[50]) {

    art->recup = 0;
    art->delaiRecupAct = 1;


    char stats[50];

    sprintf(stats,"%sArt%d.txt", fichier, art->idArt+1);        //Chemin du fichier (./data/(nom du personnage)Art/Art(id))

    for(int i = 0; i < 4; i++) {

      art->DMGMIN[i] = 0;
      art->DMGMAX[i] = 0;
      art->PRTART[i] = 2000;
      art->etats[i][fournaise] = 0;
      art->etats[i][frisson] = 0;
      art->etats[i][poison] = 0;

    }

    art->soin = 0;

    art->delaiRecupAct = 0;

    for(int i = MAXPV; i <= PRTAUTO; i++){

      art->buff[i].valeur = -1;
      art->buff[i].delai = 0;
      for(int j = 0; j < 4; j++) {

        art->debuff[j][i].valeur = -1;
        art->debuff[j][i].delai = 0;

      }

    }

    FILE* f;

    f = fopen(stats, "r");

    char temp[20];

    int orientation = -1;

    while(!feof(f)) {                           //on prend les valeurs �crite dans un fichier

            fscanf(f, "%s : ", temp);

            if(!strcmp(temp,"TYPE")) {

                    fscanf(f, "%d;", &art->TYPE);

            } else if(!strcmp(temp,"BUT")) {

                    fscanf(f, "%d;", &art->BUT);

            } else if(!strcmp(temp,"cibleAllie")) {

                    fscanf(f, "%d;", &art->CIBLE_ALLIE);

            } else if(!strcmp(temp,"orientation")) {

                    fscanf(f, "%d;", &orientation);

            } else if(!strcmp(temp,"DMGMIN")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->DMGMIN[i] = tempp;

                }

             } else {

                fscanf(f, "%d;", &art->DMGMIN[orientation]);

              }


            } else if(!strcmp(temp,"DMGMAX")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->DMGMAX[i] = tempp;

                }

               } else {

                fscanf(f, "%d;", &art->DMGMAX[orientation]);

              }

            } else if(!strcmp(temp,"delaiRecup")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->delaiRecup[i] = tempp;

                }

               } else {

                fscanf(f, "%d;", &art->delaiRecup[orientation]);

              }

            } else if(!strcmp(temp,"PRTART")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->PRTART[i] = tempp;

                }

               } else {

                fscanf(f, "%d;", &art->PRTART[orientation]);

              }

            } else if(!strcmp(temp,"fournaise")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->etats[i][fournaise] = tempp;

                }

               } else {

                fscanf(f, "%d;", &art->etats[orientation][fournaise]);

              }

            } else if(!strcmp(temp,"frisson")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->etats[i][frisson] = tempp;

                }

               } else {

                fscanf(f, "%d;", &art->etats[orientation][frisson]);

              }

            } else if(!strcmp(temp,"poison")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->etats[i][poison] = tempp;

                }

               } else {

                fscanf(f, "%d;", &art->etats[orientation][poison]);

              }

            } else if(!strcmp(temp,"buffMAXPV")) {

                    fscanf(f, "%f;", &art->buff[MAXPV].valeur);

            } else if(!strcmp(temp,"delaiBuffMAXPV")) {

                    fscanf(f, "%d;", &art->buff[MAXPV].delai);

            } else if(!strcmp(temp,"buffFRC")) {

                    fscanf(f, "%f;", &art->buff[FRC].valeur);

            } else if(!strcmp(temp,"delaiBuffFRC")) {

                    fscanf(f, "%d;", &art->buff[FRC].delai);

            } else if(!strcmp(temp,"buffMGE")) {

                    fscanf(f, "%f;", &art->buff[MGE].valeur);

            } else if(!strcmp(temp,"delaiBuffMGE")) {

                    fscanf(f, "%d;", &art->buff[MGE].delai);

            } else if(!strcmp(temp,"buffATTMIN")) {

                    fscanf(f, "%f;", &art->buff[ATTMIN].valeur);

            } else if(!strcmp(temp,"delaiBuffATTMIN")) {

                    fscanf(f, "%d;", &art->buff[ATTMIN].delai);

            } else if(!strcmp(temp,"buffATTMAX")) {

                    fscanf(f, "%f;", &art->buff[ATTMAX].valeur);

            } else if(!strcmp(temp,"delaiBuffATTMAX")) {

                    fscanf(f, "%d;", &art->buff[ATTMAX].delai);

            } else if(!strcmp(temp,"buffVITATT")) {

                    fscanf(f, "%f;", &art->buff[VITATT].valeur);

            } else if(!strcmp(temp,"delaiBuffVITATT")) {

                    fscanf(f, "%d;", &art->buff[VITATT].delai);

            } else if(!strcmp(temp,"buffCRIT")) {

                    fscanf(f, "%f;", &art->buff[CRIT].valeur);

            } else if(!strcmp(temp,"delaiBuffCRIT")) {

                    fscanf(f, "%d;", &art->buff[CRIT].delai);

            } else if(!strcmp(temp,"buffCNTR")) {

                    fscanf(f, "%f;", &art->buff[CNTR].valeur);

            } else if(!strcmp(temp,"delaiBuffCNTR")) {

                    fscanf(f, "%d;", &art->buff[CNTR].delai);

            } else if(!strcmp(temp,"buffDBLATT")) {

                    fscanf(f, "%f;", &art->buff[DBLATT].valeur);

            } else if(!strcmp(temp,"delaiBuffDBLATT")) {

                    fscanf(f, "%d;", &art->buff[DBLATT].delai);

            } else if(!strcmp(temp,"buffGARDE")) {

                    fscanf(f, "%f;", &art->buff[GARDE].valeur);

            } else if(!strcmp(temp,"delaiBuffGARDE")) {

                    fscanf(f, "%d;", &art->buff[GARDE].delai);

            } else if(!strcmp(temp,"buffDEFPHY")) {

                    fscanf(f, "%f;", &art->buff[DEFPHY].valeur);

            } else if(!strcmp(temp,"delaiBuffDEFPHY")) {

                    fscanf(f, "%d;", &art->buff[DEFPHY].delai);

            } else if(!strcmp(temp,"buffDEFMGE")) {

                    fscanf(f, "%f;", &art->buff[DEFMGE].valeur);

            } else if(!strcmp(temp,"delaiBuffDEFMGE")) {

                    fscanf(f, "%d;", &art->buff[DEFMGE].delai);

            } else if(!strcmp(temp,"buffAGI")) {

                    fscanf(f, "%f;", &art->buff[AGI].valeur);

            } else if(!strcmp(temp,"delaiBuffAGI")) {

                    fscanf(f, "%d;", &art->buff[AGI].delai);

            } else if(!strcmp(temp,"buffDEXT")) {

                    fscanf(f, "%f;", &art->buff[DEXT].valeur);

            } else if(!strcmp(temp,"delaiBuffDEXT")) {

                    fscanf(f, "%d;", &art->buff[DEXT].delai);

            } else if(!strcmp(temp,"buffPRTAUTO")) {

                    fscanf(f, "%f;", &art->buff[PRTAUTO].valeur);

            } else if(!strcmp(temp,"delaiBuffPRTAUTO")) {

                    fscanf(f, "%d;", &art->buff[PRTAUTO].delai);

            } else if(!strcmp(temp,"Soin")) {

                    fscanf(f, "%d;", &art->soin);

            } else if(!strcmp(temp,"debuffMAXPV")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][MAXPV].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][MAXPV].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffMAXPV")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][MAXPV].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][MAXPV].delai);

                }

            } else if(!strcmp(temp,"debuffFRC")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][FRC].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][FRC].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffFRC")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][FRC].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][FRC].delai);

                }

            } else if(!strcmp(temp,"debuffMGE")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][MGE].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][MGE].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffMGE")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][MGE].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][MGE].delai);

                }

            } else if(!strcmp(temp,"debuffATTMIN")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][ATTMIN].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][ATTMIN].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffATTMIN")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][ATTMIN].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][ATTMIN].delai);

                }

            } else if(!strcmp(temp,"debuffATTMAX")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][ATTMAX].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][ATTMAX].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffATTMAX")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][ATTMAX].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][ATTMAX].delai);

                }

            } else if(!strcmp(temp,"debuffVITATT")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][VITATT].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][VITATT].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffVITATT")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][VITATT].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][VITATT].delai);

                }

            } else if(!strcmp(temp,"debuffCRIT")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][CRIT].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][CRIT].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffCRIT")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][CRIT].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][CRIT].delai);

                }

            } else if(!strcmp(temp,"debuffCNTR")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][CNTR].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][CNTR].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffCNTR")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][CNTR].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][CNTR].delai);

                }

            } else if(!strcmp(temp,"debuffDBLATT")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DBLATT].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][DBLATT].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffDBLATT")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DBLATT].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][DBLATT].delai);

                }

            } else if(!strcmp(temp,"debuffGARDE")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][GARDE].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][GARDE].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffGARDE")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][GARDE].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][GARDE].delai);

                }

            } else if(!strcmp(temp,"debuffDEFPHY")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DEFPHY].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][DEFPHY].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffDEFPHY")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DEFPHY].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][DEFPHY].delai);

                }

            } else if(!strcmp(temp,"debuffDEFMGE")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DEFMGE].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][DEFMGE].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffDEFMGE")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DEFMGE].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][DEFMGE].delai);

                }

            } else if(!strcmp(temp,"debuffAGI")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][AGI].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][AGI].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffAGI")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][AGI].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][AGI].delai);

                }

            } else if(!strcmp(temp,"debuffDEXT")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DEXT].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][DEXT].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffDEXT")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][DEXT].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][DEXT].delai);

                }

            } else if(!strcmp(temp,"debuffPRTAUTO")) {

              if(orientation == -1) {

                float tempp;

                fscanf(f, "%f;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][PRTAUTO].valeur = tempp;

                }

                } else {

                  fscanf(f, "%f;", &art->debuff[orientation][PRTAUTO].valeur);

                }

            } else if(!strcmp(temp,"delaiDebuffPRTAUTO")) {

              if(orientation == -1) {

                int tempp;

                fscanf(f, "%d;", &tempp);

                for(int i = 0; i < 4; i++) {

                  art->debuff[i][PRTAUTO].delai = tempp;

                }

                } else {

                  fscanf(f, "%d;", &art->debuff[orientation][PRTAUTO].delai);

                }

            }


        }

    char img[50];

    sprintf(img,"%sart%d.png", fichier, art->idArt+1);      //chemin de l'image de l'art

    art->image = IMG_Load(img);

    fclose(f);

    return 0;

}

/*Cette fonction sert � afficher les icones des arts du personnage que l'on controle en bas de l'�cran*/

void afficherArt(Art *art[], SDL_Surface *pSurface, SDL_Surface *cooldownArt) {

    for(int i = 0; i < 8; i++) {

        SDL_Rect dest = { i*(SCREEN_WIDTH/10)+64, SCREEN_HEIGHT-100, 0, 0};
        SDL_BlitSurface(art[i]->image, NULL, pSurface, &dest);
        if(art[i]->recup > 0) {

          int taille = (int) cooldownArt->h*art[i]->recup/art[i]->delaiRecupAct;
          SDL_Rect cooldown = { 0, 0, cooldownArt->w, taille};
          SDL_BlitSurface(cooldownArt, &cooldown, pSurface, &dest);

        }

    }

}

void recuperationArt(Art *art) {

    art->recup--;       //d�cr�mentation de la variable "recup" (quand celle-ci est inf�rieur � 0 on peut utiliser l'art)

}
