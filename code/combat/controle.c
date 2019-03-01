#include "controle.h"


void controlleManette(Personnage *equipe[], int *indicePersonnage, int *positionCurseur, int *recupCurseur, int *relacheA, int *relacheGachetteDroite, int *relacheGachetteGauche) {


  switch(etat) {

    case 0:

      if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) && *relacheGachetteDroite == 0) { //Si on appuie sur la gachette droite on donner des ordres au personnage le plus � droite ou bien le controller

        if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {  //si on appuie sur A on controle le personnage

          equipe[*indicePersonnage]->vitX=0;
          equipe[*indicePersonnage]->vitY=0;

          *relacheGachetteDroite = 1;
          *relacheA = 1;

          if(equipe[((*indicePersonnage)+1)%3]->posX > equipe[((*indicePersonnage)+2)%3]->posX) *indicePersonnage += 1;

            else *indicePersonnage += 2;

          }

        } else if(!SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT)) *relacheGachetteDroite = 0;


        if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) && *relacheGachetteGauche == 0) {  //m�me chose pour la gachette gauche

          if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {

            equipe[*indicePersonnage]->vitX=0;
            equipe[*indicePersonnage]->vitY=0;

            *relacheGachetteGauche = 1;
            *relacheA = 1;

            if(equipe[((*indicePersonnage)+1)%3]->posX < equipe[((*indicePersonnage)+2)%3]->posX) *indicePersonnage += 1;

            else *indicePersonnage += 2;


          }

        } else if(!SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT)) *relacheGachetteGauche = 0;

        if(!SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) *relacheA = 0;


        *indicePersonnage %= 3;

        if((*recupCurseur)-- < 0) {

          if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) > 10000  || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {     //deplacement du curseur dans un sens

            *positionCurseur = ((*positionCurseur)+1)%8;

            *recupCurseur = DELAI_CURSEUR;

          } else if(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX) < -10000 || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) { //et dans l'autre

            (*positionCurseur)--;

            if(*positionCurseur < 0) *positionCurseur = 7;

            *recupCurseur = DELAI_CURSEUR;

          }

        }

        if(SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) && relacheGachetteDroite == 0 && relacheGachetteGauche == 0 && relacheA == 0) { //si on appuie sur A sans appuiyer sur les gachette on utilise l'art sur lequel est positionn� notre curseur


          relacheA = 1;

          if(ArtJeu[*indicePersonnage][*positionCurseur]->BUT == attaque) {

            int res = utiliseArt(ArtJeu[indicePersonnage][positionCurseur], equipe, Zanza ,*indicePersonnage);

            if(res != -1) {

              SDL_Color couleur = {0,0,0};

              addDegatTxt(&dgtsTxt[nbDgtTxt], res, Zanza.posX, Zanza.posY-Zanza.image->h, &couleur);

              nbDgtTxt++;

            }

          } else if(ArtJeu[indicePersonnage][positionCurseur]->BUT == soutien) {

            if(ArtJeu[indicePersonnage][positionCurseur]->CIBLE_ALLIE == membreGroupe && ArtJeu[indicePersonnage][positionCurseur]->recup < 0) {

              etat = 1;

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

                etat = 0;

            } else if(!SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) relacheA = 0;

        }

        break;

    }
}
