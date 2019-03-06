
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "ennemi.h"

/**
  \file incroyable.c
  \brief XenoKart Eco Plus
  \author Mano Brabant
  \version 0.01
  \date 13 fevrier 2019
*/


/**
    \fn void afficherCible(int cible, SDL_Surface* pSurface)
    \brief Affiche dans une fenetre la cible que l'on est en train de choisir
    \param cible cible pour savoir ou se situe la cible
    \param pSurface fenetre dans laquelle on va afficher la cible
*/

void afficherCible(int cible, SDL_Surface* pSurface) {

    SDL_Rect rect ={10, (cible+1)*100, 150, 5};

    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 255, 0, 0));

    rect.y += 45;
    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 0, 255, 0));

    rect.y -= 45;
    rect.h = 50;
    rect.w = 5;

    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 0, 0, 255));

    rect.x += 145;
    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 0, 0, 0));

}


/**
    \fn void afficherHUD(Personnage *equipe[], SDL_Surface* pSurface)
    \brief Affiche dans une fenetre les points de vie et les points de vie maximum de nos personnages
    \param equipe l'equipe de personnage à afficher
    \param pSurface fenetre dans laquelle on va afficher les points de vie de l'equipe
*/

void afficherHUD(Personnage *equipe[], SDL_Surface* pSurface) {

    SDL_Rect dest;

    dest.x = 10;

    for(int i = 0; i < 3; i++) {

        dest.y = (i+1)*100;

        char message[20];

        SDL_Surface* txt;

        sprintf(message, "%d/%.0f", equipe[i]->PV, equipe[i]->modif[MAXPV]);

        TTF_Font *police = NULL;

        police = TTF_OpenFont("./data/DejaVuSans.ttf", 35);

        SDL_Color couleur = {0,0,0};

        txt = TTF_RenderText_Solid(police, message, couleur);

        SDL_BlitSurface(txt, NULL, pSurface, &dest);

        TTF_CloseFont(police);

        SDL_FreeSurface(txt);

    }

}


/**
    \fn void afficherCible(int a, SDL_Surface* pSurface)
    \brief Affiche dans une fenetre le curseur qui indique l'art que l'on est en train de choisir
    \param a indice pour savoir ou se situe l'art
    \param pSurface fenetre dans laquelle on va afficher la cible
*/

void afficherCurseur(int a, SDL_Surface* pSurface) {

    SDL_Rect rect ={a*128+64, 720-100, 5, 50};

    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 255, 0, 0));

    rect.x += 45;
    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 0, 255, 0));

    rect.x -= 45;
    rect.h = 5;
    rect.w = 50;
    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 0, 0, 255));

    rect.y += 45;
    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 0, 0, 0));

}


/**
    \fn void SuiviCamera(SDL_Rect *camera, Personnage *perso, Ennemi *enn)
    \brief permet de mettre à jour les valeur de camera en fonction du personnage qu'on utilise et de l'ennemi qu'il cible
    \param camera le parametre à modifier
    \param perso personnage que l'on utilise
    \param enn ennemi que l'on cible
*/

void SuiviCameraCombat(SDL_Rect *camera, Personnage *perso, Ennemi *enn) {

    camera->x = (perso->posX+enn->posX)/2;
    camera->y = (perso->posY+enn->posY)/2;

}


void SuiviCameraExploration(SDL_Rect *camera, Personnage *perso) {

    camera->x = perso->posX;
    camera->y = perso->posY;

}


/**
    \fn void background(SDL_Surface *sol, SDL_Window *screen, SDL_Rect camera)
    \brief Affiche le sol du jeu
    \param sol l'image qui recouvre le sol
    \param pSurface fenetre dans laquelle on va afficher le sol
    \param camera nous permet d'afficher le sol de facon fixe
*/

void background(SDL_Surface *sol, SDL_Surface *pSurface, SDL_Rect camera) {

  int i;

  int j;

    for(i = -SCREEN_WIDTH; i < SCREEN_WIDTH*2; i+=sol->w) {

        for(j = -SCREEN_HEIGHT; j < SCREEN_HEIGHT*2; j+=sol->h) {

            SDL_Rect dest = { i-camera.x+camera.w, j-camera.y+camera.h, 0, 0};
            SDL_BlitSurface(sol, NULL, pSurface, &dest);

        }

    }

}

/**
    \fn void afficherHostilite(SDL_Surface *pSurface, Ennemi *ennemi, Personnage *equipe[], SDL_Rect camera)
    \brief Affiche quel personnage semble le plus menacant pour un ennemi
    \param ennemi qui nous permet de savoir qui il trouve le plus menacant
    \param equipe equipe de personnage qui menace l'ennemi
    \param pSurface fenetre dans laquelle on va afficher l'hostilite
    \param camera nous permet d'afficher l'hostilite de facon fixe
*/

void afficherHostilite(SDL_Surface *pSurface, Ennemi *ennemi, Personnage *equipe[], SDL_Rect camera) {


    int indice = cibleEnnemi(ennemi);

    SDL_Rect rect ={equipe[indice]->posX-camera.x+camera.w-equipe[indice]->image->w/2, equipe[indice]->posY-camera.y+camera.h+equipe[indice]->image->h/2, equipe[indice]->image->w, 10};


    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 255, 0, 0));


}

/**
    \fn void gererTexte(degatsTxt *tab, int *nbMembre, SDL_Surface *pSurface, SDL_Rect camera)
    \brief Affiche les valeur de degats et de soin au dessus des personnages et des ennemi concerné, puis fait disparaitre les texte au bout de quelque instants
    \param tab le tableau de texte
    \param nbMembre le nombre de texte afficher à l'ecran
    \param pSurface fenetre dans laquelle on va afficher les textes
    \param camera nous permet d'afficher les textes de facon fixe
*/

void gererTexte(degatsTxt *tab, int *nbMembre, SDL_Surface *pSurface, SDL_Rect camera) {

	int i;

    	for(i = 0; i < (*nbMembre); i++) {

        	if(tab[i].vie > 10) {

			        afficherDegatsTxt(tab+i, pSurface, camera);

	        } else {

		          SDL_FreeSurface(tab[i].txt);

            	int m;

            	for(m = i; m < (*nbMembre)-1; m++) {

                	tab[m] = tab[m+1];

            	}

              (*nbMembre)--;

          }

    }

}

/**
    \fn int controlePerso(Personnage *equipe[], int *indicePersonnage, int cote)
    \brief permet de prendre le controle d'un personnage de l'equipe
    \param equipe tableau des personnages dont-on peut prendre le controle
    \param indicePersonnage indique le personnage que l'on controle actuellement
    \param cote nous permet de decider de quel personnages on va prendre controle
*/

int controlePerso(Personnage *equipe[], int *indicePersonnage, int cote) {

  equipe[*indicePersonnage]->vitX=0;
  equipe[*indicePersonnage]->vitY=0;

  if(cote == droite) {

    if(equipe[((*indicePersonnage)+1)%3]->posX > equipe[((*indicePersonnage)+2)%3]->posX) *indicePersonnage += 1;

    else *indicePersonnage += 2;

  } else {

    if(equipe[((*indicePersonnage)+1)%3]->posX < equipe[((*indicePersonnage)+2)%3]->posX) *indicePersonnage += 1;

    else *indicePersonnage += 2;

  }

  *indicePersonnage %= 3;

  return *indicePersonnage;

}





int gererEnnemis(Ennemi ennemis[], int *nbEnnemi) {

  for(int i = 0; i < *nbEnnemi; i++) {

    if(ennemis[i].PV <= 0) {

      for(int j = i; j < *nbEnnemi-1; j++) {

        ennemis[j] = ennemis[j+1];

      }

      (*nbEnnemi)--;

    }

  }

  return *nbEnnemi;

}

void victoire(SDL_Window *screen, Ennemi ennemis[], int *nbEnnemi, Ennemi ennPool[], int nbEnnemiPool) {

  SDL_Rect dest = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2,0,0};

  char message[20];

  SDL_Surface* txt;

  sprintf(message, "Victoire !!!");

  TTF_Font *police = NULL;

  police = TTF_OpenFont("./data/DejaVuSans.ttf", 35);

  SDL_Color couleur = {0,0,0};

  txt = TTF_RenderText_Solid(police, message, couleur);

  SDL_BlitSurface(txt, NULL, SDL_GetWindowSurface(screen), &dest);

  TTF_CloseFont(police);

  SDL_FreeSurface(txt);

  SDL_UpdateWindowSurface(screen);


  int nbNouvEnn;

  scanf("%d", &nbNouvEnn);

  for(int i = 0; i < nbNouvEnn; i++) {

    int temp = rand()%nbEnnemiPool;

    ennemis[(*nbEnnemi)++] = ennPool[temp];

  }


}




int main(int argc, char** argv)
{

    srand(time(NULL));


    SDL_Rect camera = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};  //camera servira à afficher les sprites en fonction de la position du joueur

    ///////Initialisation de SDL/////////

    SDL_Init(SDL_INIT_EVERYTHING);

    TTF_Init();

    IMG_Init(IMG_INIT_PNG);


    /////////////////////////////////////

    //////Création de la fenetre où s'affichera le jeu//////

    SDL_Window* screen = SDL_CreateWindow("XenoKart ECO PLUS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    //////Initailisation de la police d'écriture//////

    TTF_Font *police = NULL;

    police = TTF_OpenFont("./data/DejaVuSans.ttf", 30);






    SDL_Surface* pSurface = NULL;

    pSurface = SDL_GetWindowSurface(screen);

    SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255));


    ///Initialisation d'un controller (si on en possède un)

    SDL_Joystick *joy;

    // Initialize the joystick subsystem
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);

    SDL_GameController* controller;

    // Check for joystick
    if (SDL_NumJoysticks() > 0) {

        // Open joystick
        joy = SDL_JoystickOpen(0);

        if (joy) {

          printf("Opened Joystick 0\n");
          printf("Name: %s\n", SDL_JoystickNameForIndex(0));
          printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
          printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
          printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
          controller = SDL_GameControllerOpen(0);

        } else {

          printf("Couldn't open Joystick 0\n");

        }

        printf("%d\n", SDL_NumJoysticks());
        printf("%s\n", SDL_JoystickName(joy));

      }






      Personnage* equipe[3];      //durant un combat l'équipe est composé de trois personnage
      Personnage Jojo;
      Personnage Dio;
      Personnage Guts;

      equipe[0] = &Guts;
      equipe[1] = &Dio;
      equipe[2] = &Jojo;

      initPersonnage(&Guts, "./data/Guts.txt");   //initialisation des personnages selon des fichiers txt
      initPersonnage(&Dio, "./data/Dio.txt");
      initPersonnage(&Jojo, "./data/Jojo.txt");


      SDL_Surface * sol;

      sol = IMG_Load("./data/Sable.png");


      Art *ArtJeu[3][8];

      int i;
      for(i = 0; i < 9; i++) {

          char fichier[50];
          sprintf(fichier, "./data/JojoArt/");

          Jojo.ArtPool[i].idArt = i;
          initArt(&Jojo.ArtPool[i], fichier);     //initialisation des arts des personnages

      }

      for(i = 0; i < 9; i++) {

          char fichier[50];
          sprintf(fichier, "./data/DioArt/");

          Dio.ArtPool[i].idArt = i;
          initArt(&Dio.ArtPool[i], fichier);

      }

      for(i = 0; i < 9; i++) {

          char fichier[50];
          sprintf(fichier, "./data/GutsArt/");

          Guts.ArtPool[i].idArt = i;
          initArt(&Guts.ArtPool[i], fichier);

      }


      ArtJeu[0][0] = &Guts.ArtPool[3];        //affectation des art d'un personnage
      ArtJeu[0][1] = &Guts.ArtPool[4];
      ArtJeu[0][2] = &Guts.ArtPool[5];
      ArtJeu[0][3] = &Guts.ArtPool[6];
      ArtJeu[0][4] = &Guts.ArtPool[7];
      ArtJeu[0][5] = &Guts.ArtPool[0];
      ArtJeu[0][6] = &Guts.ArtPool[1];
      ArtJeu[0][7] = &Guts.ArtPool[2];

      ArtJeu[1][0] = &Dio.ArtPool[0];
      ArtJeu[1][1] = &Dio.ArtPool[1];
      ArtJeu[1][2] = &Dio.ArtPool[2];
      ArtJeu[1][3] = &Dio.ArtPool[3];
      ArtJeu[1][4] = &Dio.ArtPool[4];
      ArtJeu[1][5] = &Dio.ArtPool[5];
      ArtJeu[1][6] = &Dio.ArtPool[6];
      ArtJeu[1][7] = &Dio.ArtPool[8];

      ArtJeu[2][0] = &Jojo.ArtPool[0];
      ArtJeu[2][1] = &Jojo.ArtPool[1];
      ArtJeu[2][2] = &Jojo.ArtPool[2];
      ArtJeu[2][3] = &Jojo.ArtPool[3];
      ArtJeu[2][4] = &Jojo.ArtPool[4];
      ArtJeu[2][5] = &Jojo.ArtPool[5];
      ArtJeu[2][6] = &Jojo.ArtPool[6];
      ArtJeu[2][7] = &Jojo.ArtPool[7];

      Ennemi Zanza;

      Ennemi Dickson;

      initEnnemi(&Zanza, "./data/Zanza.txt");

      initEnnemi(&Dickson, "./data/Dickson.txt");

      Ennemi ennPool[100];

      ennPool[0] = Zanza;

      ennPool[1] = Dickson;

      int nbEnnemiPool = 2;



      Ennemi ennemis[100];

      ennemis[0] = Zanza;

      ennemis[1] = Dickson;

      int nbEnnemi = 0;


      SDL_Event event;

      int quit = 0;               //quitte le programme si on appui sur la croix rouge

      int indicePersonnage = 0;       //variable qui indique quel personnage on est entrain de controller

      int relacheGachetteGauche = 0;  //variables qui permettent d'empecher l'utilisateur de rester appuy� sur un bouton

      int relacheGachetteDroite = 0;

      int relacheA = 0;

      int relacheSPACE = 0;

      int recupCibleEnn = 0;           //variable affect� a DELAI_CIBLE_ENN


      int positionCurseur = 5;

      int recupCurseur = 0;           //variable affect� a DELAI_CURSEUR

      degatsTxt dgtsTxt[500];         //tableau des textes affichés � l'�cran

      int nbDgtTxt = 0;               //nombre de texte de d�gats affich� � l'�cran

      int etat = 1;                   //hors combat = 0; en combat = 1;

      int etatCombat = 0;             //Si on se bat normalement ou si on est en train de choisir une cible pour un art de soutien

      int cible = 0;                  //indique quel personnage on cible avec un art de soutien

      int recupCible = 0;             //variable qui permet de naviguer entre les cibles

      int indice = 0;                 //indique le personnage le plus hositile pour un monstre


      long long unsigned debut, fin, fpsCount = 0;




        while(!quit) {

            debut = SDL_GetTicks();

            SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255)); //on nettoye l'�cran en affichant un grand rectangle blanc


            SDL_PollEvent(&event);

            if(joy) {

              /*switch(etatCombat) {

                case 0:

                  if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) && relacheGachetteDroite == 0) { //Si on appuie sur la gachette droite on donner des ordres au personnage le plus � droite ou bien le controller

                    if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {  //si on appuie sur A on controle le personnage

                      equipe[indicePersonnage]->vitX=0;
                      equipe[indicePersonnage]->vitY=0;

                      relacheGachetteDroite = 1;
                      relacheA = 1;

                      if(equipe[(indicePersonnage+1)%3]->posX > equipe[(indicePersonnage+2)%3]->posX)indicePersonnage += 1;

                        else indicePersonnage += 2;

                      }

                    } else if(!SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)) relacheGachetteDroite = 0;


                    if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) && relacheGachetteGauche == 0) {  //m�me chose pour la gachette gauche

                      if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {

                        equipe[indicePersonnage]->vitX=0;
                        equipe[indicePersonnage]->vitY=0;

                        relacheGachetteGauche = 1;
                        relacheA = 1;

                        if(equipe[(indicePersonnage+1)%3]->posX < equipe[(indicePersonnage+2)%3]->posX)indicePersonnage += 1;

                        else indicePersonnage += 2;


                      }

                    } else if(!SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT)) relacheGachetteGauche = 0;

                    if(!SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) relacheA = 0;


                    indicePersonnage %= 3;
for(int i = 0; i < 3; i++) {

                etatEnnemi(&Zanza, i, dgtsTxt, &nbDgtTxt);

            }
                    if(recupCurseur-- < 0) {

                      if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) > 10000  || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {     //deplacement du curseur dans un sens

                        positionCurseur = (positionCurseur+1)%8;

                        recupCurseur = DELAI_CURSEUR;

                      } else if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) < -10000 || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) { //et dans l'autre

                        positionCurseur--;

                        if(positionCurseur < 0) positionCurseur = 7;

                        recupCurseur = DELAI_CURSEUR;

                      }

                    }

                    if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) && relacheGachetteDroite == 0 && relacheGachetteGauche == 0 && relacheA == 0) { //si on appuie sur A sans appuiyer sur les gachette on utilise l'art sur lequel est positionn� notre curseur


                      relacheA = 1;

                      if(ArtJeu[indicePersonnage][positionCurseur]->BUT == attaque) {

                        utiliseArt(ArtJeu[indicePersonnage][positionCurseur], equipe, cibleEnn[equipe[indicePersonnage]->cible] ,indicePersonnage, dgtsTxt, &nbDgtTxt);

                      } else if(ArtJeu[indicePersonnage][positionCurseur]->BUT == soutien) {

                        if(ArtJeu[indicePersonnage][positionCurseur]->CIBLE_ALLIE == membreGroupe && ArtJeu[indicePersonnage][positionCurseur]->recup < 0) {

                          etatCombat = 1;

                        } else {

                        utiliseArtBuff(ArtJeu[indicePersonnage][positionCurseur], equipe, indicePersonnage, pSurface, dgtsTxt, &nbDgtTxt);

                        }

                      }

                    }

                    break;

                case 1:

                  if(recupCible-- < 0) {

                        if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) > 10000 || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) {

                            cible += 1;
                            cible %= 3;

                            recupCible = DELAI_CIBLE;

                        } else if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY) < -10000 || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {

                            cible -= 1;
                            if(cible < 0) cible = 2;

                            recupCible = DELAI_CIBLE;

                        }

                        if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) && relacheA == 0) {

                            relacheA = 1;

                            utiliseArtBuff(ArtJeu[indicePersonnage][positionCurseur], equipe, cible, pSurface, dgtsTxt, &nbDgtTxt);

                            etatCombat = 0;

                        } else if(!SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) relacheA = 0;

                    }

                    break;

                }

              */} else {

                SDL_PumpEvents();
                const Uint8 *state = SDL_GetKeyboardState(NULL);      //Vérification de quelles sont les touche qui sont enfoncé sur le clavier

                switch(etat) {

                  case 0:

                    for(int i = 0; i < nbEnnemi; i++) {

                      if(ennemis[i].enCombat) {

                        indice = cibleEnnemi(&ennemis[i]);

                        attaqueAllie(equipe, &ennemis[i], indice, dgtsTxt, &nbDgtTxt);

                      }

                    }

                    for(i = 0; i < 3; i++) {        //v�rifications des auto-attaques

                      attaqueEnnemi(equipe, &ennemis[equipe[i]->cible], i, dgtsTxt, &nbDgtTxt);

                    }

                    switch(etatCombat) {

                      case 0:

                        if(state[SDL_SCANCODE_3] && relacheGachetteDroite == 0) { //Si on appuie sur la gachette droite on donner des ordres au personnage le plus � droite ou bien le controller

                          if(state[SDL_SCANCODE_E]) {  //si on appuie sur E on controle le personnage

                            controlePerso(equipe, &indicePersonnage, droite);

                            relacheGachetteDroite = 1;
                            relacheA = 1;

                          }


                        } else if(!state[SDL_SCANCODE_3]) relacheGachetteDroite = 0;


                          if(state[SDL_SCANCODE_1] && relacheGachetteGauche == 0) {  //m�me chose pour la gachette gauche

                            if(state[SDL_SCANCODE_E]) {

                              controlePerso(equipe, &indicePersonnage, gauche);

                              relacheGachetteGauche = 1;
                              relacheA = 1;

                            }

                          } else if(!state[SDL_SCANCODE_1]) relacheGachetteGauche = 0;

                          if(!state[SDL_SCANCODE_E]) relacheA = 0;



                          if(recupCurseur-- < 0) {

                            if(state[SDL_SCANCODE_RIGHT]) {     //deplacement du curseur dans un sens

                              positionCurseur = (positionCurseur+1)%8;

                              recupCurseur = DELAI_CURSEUR;

                            } else if(state[SDL_SCANCODE_LEFT]) { //et dans l'autre

                              positionCurseur--;

                              if(positionCurseur < 0) positionCurseur = 7;

                              recupCurseur = DELAI_CURSEUR;

                            }

                          }

                          if(state[SDL_SCANCODE_E] && relacheGachetteDroite == 0 && relacheGachetteGauche == 0 && relacheA == 0) { //si on appuie sur A sans appuiyer sur les gachette on utilise l'art sur lequel est positionn� notre curseur


                            relacheA = 1;

                            if(ArtJeu[indicePersonnage][positionCurseur]->BUT == attaque) {

                              utiliseArt(ArtJeu[indicePersonnage][positionCurseur], equipe, &ennemis[equipe[indicePersonnage]->cible] ,indicePersonnage, dgtsTxt, &nbDgtTxt);

                            } else if(ArtJeu[indicePersonnage][positionCurseur]->BUT == soutien) {

                              if(ArtJeu[indicePersonnage][positionCurseur]->CIBLE_ALLIE == membreGroupe && ArtJeu[indicePersonnage][positionCurseur]->recup < 0) {

                                etatCombat = 1;

                              } else {

                                utiliseArtBuff(ArtJeu[indicePersonnage][positionCurseur], equipe, indicePersonnage, pSurface, dgtsTxt, &nbDgtTxt);

                              }

                            }

                          }

                          break;

                          case 1:

                            if(recupCible-- < 0) {

                              if(state[SDL_SCANCODE_DOWN]) {

                                cible += 1;
                                cible %= 3;

                                recupCible = DELAI_CIBLE;

                              } else if(state[SDL_SCANCODE_UP]) {

                                cible -= 1;
                                if(cible < 0) cible = 2;

                                recupCible = DELAI_CIBLE;

                              }

                              if(state[SDL_SCANCODE_E] && relacheA == 0) {

                                relacheA = 1;

                                utiliseArtBuff(ArtJeu[indicePersonnage][positionCurseur], equipe, cible, pSurface, dgtsTxt, &nbDgtTxt);

                                etatCombat = 0;

                              } else if(!state[SDL_SCANCODE_E]) relacheA = 0;

                            }

                            break;

                          }

                        //  break;

                        case 1:

                          if(recupCibleEnn-- < 0) {

                            if(state[SDL_SCANCODE_I]) {

                              equipe[indicePersonnage]->cible++;

                              equipe[indicePersonnage]->cible %= nbEnnemi;

                              equipe[indicePersonnage]->enChoixCible = 1;

                              recupCibleEnn = DELAI_CIBLE_ENN;

                            }



                            if(state[SDL_SCANCODE_P]) {

                              equipe[indicePersonnage]->cible--;

                              if(equipe[indicePersonnage]->cible < 0) equipe[indicePersonnage]->cible = nbEnnemi-1;

                              equipe[indicePersonnage]->enChoixCible = 1;

                              recupCibleEnn = DELAI_CIBLE_ENN;

                            }

                          }


                          if(state[SDL_SCANCODE_SPACE] && relacheSPACE == 0) {

                            relacheSPACE = 1;

                            for(int i = 0; i < 3; i++) {

                              equipe[i]->enCombat = 1;

                              equipe[i]->enChoixCible = 0;

                            }

                            etat = 0;

                          } else if(!state[SDL_SCANCODE_SPACE]) relacheSPACE = 0;

                          break;


                      }

              }



            if(joy) {

              deplacementManette(controller, indicePersonnage, equipe);

            } else {

              deplacementClavier(indicePersonnage, equipe);

            }

            if(equipe[indicePersonnage]->enCombat) {

              orientationPersoCombatRelative(equipe, indicePersonnage, &ennemis[equipe[indicePersonnage]->cible]);

            }

            for(int n = 0; n < nbEnnemi; n++) {

              for(int i = 0; i < 3; i++) {

                  etatEnnemi(&ennemis[n], i, dgtsTxt, &nbDgtTxt);

              }

              delaiEtat(&ennemis[n]);

            }



            for(i = 0; i < 3; i++) {

                for(int j = 0; j < 8; j++) {

                    recuperationArt(ArtJeu[i][j]);      //d�cr�mentations des arts des personnages

                }

                delaiModificationPerso(equipe[i]);           //d�crementations des modifications des personnages

            }

            for(int n = 0; n < nbEnnemi; n++) {

              delaiModificationEnnemi(&ennemis[n]);

            }

            for(i = 0; i < 3; i++) {

                deplacementPersonnage(equipe[i]);

            }

            for(int i = 0; i < nbEnnemi; i++) {

              if(ennemis[i].enCombat) {

                deplacementEnnemi(ennemis+i, equipe);

              }

            }

            if(equipe[indicePersonnage]->enChoixCible)  {

              SuiviCameraCombat(&camera, equipe[indicePersonnage], &ennemis[equipe[indicePersonnage]->cible]);

            } else if (equipe[indicePersonnage]->enCombat) {

              SuiviCameraCombat(&camera, equipe[indicePersonnage], &ennemis[equipe[indicePersonnage]->cible]);

            } else {

              SuiviCameraExploration(&camera, equipe[indicePersonnage]);

            }

            background(sol, pSurface, camera);

            for(int n = 0; n < nbEnnemi; n++) {

              if(ennemis[n].enCombat) {

                afficherHostilite(pSurface, &ennemis[n], equipe, camera);

              }

            }

            for(i = 0; i < 3; i++) {

                afficherPersonnage(*equipe[i], screen, camera);

            }


            for(int n = 0; n < nbEnnemi; n++) {

              afficherEnnemi(&ennemis[n], pSurface, camera, equipe, etat);

            }


            afficherArt(ArtJeu[indicePersonnage], pSurface);

            afficherCurseur(positionCurseur, pSurface);

            afficherHUD(equipe, pSurface);

            if(etatCombat == 1) afficherCible(cible, pSurface);

            gererTexte(dgtsTxt, &nbDgtTxt, pSurface, camera);

            gererEnnemis(ennemis, &nbEnnemi);

            if(!nbEnnemi) {

              for(int i = 0; i < 3; i++) {

                equipe[i]->enCombat = 0;

              }

              etat = 1;

            }

            printf("\nils sont moult : %p\n", &ennemis[0]);

            printf("\nils sont moult : %p\n", &ennemis[1]);

            printf("\nils sont moult : %d\n", equipe[indicePersonnage]->cible);

            while(nbEnnemi == 0) {

              victoire(screen, ennemis, &nbEnnemi, ennPool, nbEnnemiPool);

            }


            SDL_UpdateWindowSurface(screen);

            switch(event.type) {

                case SDL_QUIT:
                    quit = 1;
                    break;

            /*    switch(event.window.event) {

                    case SDL_WINDOWEVENT_EXPOSED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SHOWN:

                    break;

                }*/

            }

            fin = SDL_GetTicks();

            printf("\nfps = %lld\n", (fpsCount++)*1000/SDL_GetTicks());

            printf("fpsCount = %lld\n", fpsCount);

            printf("fin = %lld\n", fin);

            int delai = ((1000/FPS)-(fin-debut));

            if(delai > 0) {

                SDL_Delay(delai);

            }

        }

        // Close if opened
        if (SDL_JoystickGetAttached(joy)) {

            SDL_JoystickClose(joy);

        }


    TTF_CloseFont(police);

    IMG_Quit();

    TTF_Quit();

    SDL_Quit();

    return 0;

}
