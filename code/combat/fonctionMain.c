


/**
  \file fonctionMain.c
  \brief XenoKart Eco Plus
  \author Mano Brabant
  \version 0.01
  \date 13 fevrier 2019
*/

char buffer[512];

int client_socket1, client_socket2, to_server_socket;
int coop;
int serveur;


int recupCurseur;           //variable affect� a DELAI_CURSEUR
int positionCurseur;
int recupCible;
int cible;
int recupCibleEnn;

int etatCombat = 0;             //Si on se bat normalement ou si on est en train de choisir une cible pour un art de soutien

SDL_Rect camera = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};  //camera servira à afficher les sprites en fonction de la position du joueur

SDL_Surface *cooldownArt;
SDL_Surface * sol;
SDL_Surface* pSurface;
SDL_Window* screen;

pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */


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


    SDL_Rect rect ={equipe[ennemi->cible]->posX-camera.x+camera.w-equipe[ennemi->cible]->image->w/2/4, equipe[ennemi->cible]->posY-camera.y+camera.h+equipe[ennemi->cible]->image->h/2/4, equipe[ennemi->cible]->image->w/4, 10};


    SDL_FillRect(pSurface, &rect, SDL_MapRGB(pSurface->format, 255, 0, 0));


}

/**
    \fn void gererTexte(SDL_Surface *pSurface, SDL_Rect camera)
    \brief Affiche les valeur de degats et de soin au dessus des personnages et des ennemi concerné, puis fait disparaitre les texte au bout de quelque instants
    \param pSurface fenetre dans laquelle on va afficher les textes
    \param camera nous permet d'afficher les textes de facon fixe
*/

void gererTexte(SDL_Surface *pSurface, SDL_Rect camera) {

	int i;

  afficherDegatsTxt(pSurface, camera);


    	for(i = 0; i < nbDgtTxt; i++) {


	        if(dgtsTxt[i].vie < 10) {

		          SDL_FreeSurface(dgtsTxt[i].txt);

            	int m;

            	for(m = i; m < nbDgtTxt-1; m++) {

                	dgtsTxt[m] = dgtsTxt[m+1];

            	}

              nbDgtTxt--;

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



/**
    \fn int gererEnnemis(Ennemi ennemis[], int *nbEnnemi, Personnage *equipe[], int *etat)
    \brief Permet de vérifier si les ennemis en combat sont toujours vivants
    \param ennemis liste de tout les ennemis
    \param nbEnnemi nombre d'ennemis encore vivants
    \param equipe tableau des personnages jouable
*/



int gererEnnemis(Ennemi ennemis[], int *nbEnnemi, Personnage *equipe[]) {

  for(int i = 0; i < *nbEnnemi; i++) {

    if(ennemis[i].PV <= 0) {

      for(int j = i; j < *nbEnnemi-1; j++) {

        ennemis[j] = ennemis[j+1];

      }

      (*nbEnnemi)--;






      int combat = 0;

      int indice = 0;

      for(int i = 0; i < *nbEnnemi && !combat; i++) {

        if(ennemis[i].enCombat) {

          combat = 1;

          indice = i;

        }

      }

      if(!combat) {

          for(int i = 0; i < 3; i++) {

            equipe[i]->enCombat = 0;

            equipe[i]->cible = 0;

          }


      } else {

        for(int i = 0; i < 3; i++) {

          equipe[i]->cible = indice;

        }

      }

    }

  }

  return *nbEnnemi;

}


/**
    \fn void victoire(SDL_Window *screen, Ennemi ennemis[], int *nbEnnemi)
    \brief quand il n'y a plus d'ennemis on affiche un texte "Victoire !!!" à l'écran, puis on rajoute de nouveau ennemis
    \param screen fenetre sur laquelle on affiche le message
    \param ennemis tableau des ennemis que l'on va ajouter
    \param nbEnnemi nombre d'ennemis (egal à 0) au debut de la fonction, (egal au nombre d'ennemis ajouter à la fin)
*/

void victoire(SDL_Window *screen, Ennemi ennemis[], int *nbEnnemi) {

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


/*
  int nbNouvEnn = 1;


  for(int i = 0; i < nbNouvEnn; i++) {

    int temp = rand()%nbEnnemiPool;

    ennemis[(*nbEnnemi)++] = ennPool[temp];

  }

*/
}




/**
    \fn int testTouche(doublet clavier)
    \brief cette fonction permet de verifier qu'un touche vient d'etre enfoncé
    \param clavier touche que l'on verifie
    \return TRUE ou FALSE
*/



int testTouche(doublet clavier) {

  return clavier.enfonce && clavier.relache;

}


/*
void fin(int sig){
	printf("fin du serveur");
}
*/
int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }

    return 1;
}


void view_ip()
{
  char s[256];
  struct hostent *host;
  struct in_addr **adr;
  if (!gethostname(s, 256))
    if ((host = gethostbyname(s)) != NULL)
      for (adr = (struct in_addr **)host->h_addr_list; *adr; adr++)
          printf("IP : %s\n", inet_ntoa(**adr));
}


void quitter(int to_server_socket){
	printf("[client] envoi message QUITTER au serveur\n");
	send(to_server_socket,QUITTER,7,0);
}





/**
    \fn void * recoit(void *sock)
    \brief cette fonction permet de recevoir les messages des clients ou du serveur et de les gerer
    \param sock socket du client ou du serveur
*/


void * recoit(void *sock) {

  SDL_Delay(1000);

  char data[100];

  int *socket1 = sock;

  while(1) {





    recv(*socket1, data, sizeof(data), 0);

    pthread_mutex_lock(&mutex); /* On verrouille le mutex */

    pthread_cond_wait (&condition, &mutex); /* On attend que la condition soit remplie */

    fprintf(stderr, "Secondaire : %s\n", data);


    int posX;
    int posY;
    int cible;
    int degats;
    int typeCoup;
    int positionCurseur;
    int indicePersonnage;
    char type;

    switch (data[0]) {

      case 'p':
        sscanf(data, "%c;%d;%d;%d", &type, &indicePersonnage, &posX, &posY);
        equipe[indicePersonnage]->posX = posX;
        equipe[indicePersonnage]->posY = posY;
        if(serveur) {

          char data[100];

          sprintf(data, "p;%d;%d;%d", indicePersonnage, equipe[indicePersonnage]->posX, equipe[indicePersonnage]->posY);

          fprintf(stderr, "Principale : %s\n", data);

          if(indicePersonnage == 2) send(client_socket1, data, sizeof(data), 0);
          else send(client_socket2, data, sizeof(data), 0);

        }

        break;

      case 'a':
        sscanf(data, "%c;%d;%d", &type, &positionCurseur, &indicePersonnage);
        utiliseArt(positionCurseur, indicePersonnage);
        break;

      case 'z':
        sscanf(data, "%c;%d;%d;%d", &type, &positionCurseur, &indicePersonnage, &degats);
        lanceArt(positionCurseur, indicePersonnage, degats);
        break;

      case 'b':
        sscanf(data, "%c;%d;%d;%d", &type, &positionCurseur, &indicePersonnage, &cible);
        utiliseArtBuff(positionCurseur, indicePersonnage, cible);
        break;

      case 'c':
        sscanf(data, "%c;%d;%d;%d", &type, &indicePersonnage, &degats, &typeCoup);
        persoAutoAttaque(indicePersonnage, degats, typeCoup);
        break;

      case 'e':
        sscanf(data, "%c;%d;%d;%d", &type, &indicePersonnage, &degats, &typeCoup);
        ennemiAutoAttaque(indicePersonnage, degats, typeCoup);
        break;

      case 'y':
        sscanf(data, "%c;%d;%d", &type, &indicePersonnage, &cible);
        equipe[indicePersonnage]->cible = cible;

        if(serveur) {

          char data[100];

          sprintf(data, "y;%d;%d", indicePersonnage, cible);

          fprintf(stderr, "Principale : %s\n", data);

          send(client_socket1, data, sizeof(data), 0);

          send(client_socket2, data, sizeof(data), 0);

        }
        break;

    }

    strcpy(data, "");

    pthread_mutex_unlock(&mutex); /* On déverrouille le mutex */


  }

}


/**
    \fn void autoAttaque()
    \brief cette fonction appelle d'autre fonction pour permettre aux personnages et aux ennemis d'utiliser des auto-attaque
*/


void autoAttaque() {

  if(coop) {

    if(serveur) {

      attaqueAllie();

      attaqueEnnemi();  //les personnages attaques l'ennemi qu'ils ciblent

    }

  } else {

    attaqueAllie();

    attaqueEnnemi();  //les personnages attaques l'ennemi qu'ils ciblent

  }

}


/**
    \fn void ordreNouvCible()
    \brief cette fonction appelle d'autre fonction pour permettre d'ordoner aux autre personnages d'attaquer un ennemis ciblé
*/

void ordreNouvCible() {


  if(clavier[SDL_SCANCODE_3].enfonce) { //Si on appuie sur la gachette droite on donner des ordres au personnage le plus � droite ou bien le controller

    if(testTouche(clavier[SDL_SCANCODE_R])) {  //si on appuie sur R on dit au personnage d'attaquer une cible

      equipe[(indicePersonnage+1)%3]->cible = equipe[indicePersonnage]->cible;

    }

  }

  if(clavier[SDL_SCANCODE_1].enfonce) {  //m�me chose pour la gachette gauche

    if(testTouche(clavier[SDL_SCANCODE_R])) {  //si on appuie sur R on dit au personnage d'aataquer une cible

      equipe[(indicePersonnage+2)%3]->cible = equipe[indicePersonnage]->cible;

    }

  }

}


/**
    \fn void choixArt()
    \brief cette fonction permet de changer la position du curseur de choix des "arts"
*/

void choixArt() {

  if(recupCurseur-- < 0) {

    if(clavier[SDL_SCANCODE_RIGHT].enfonce) {     //deplacement du curseur dans un sens

      positionCurseur = (positionCurseur+1)%8;

      recupCurseur = DELAI_CURSEUR;

    } else if(clavier[SDL_SCANCODE_LEFT].enfonce) { //et dans l'autre

      positionCurseur--;

      if(positionCurseur < 0) positionCurseur = 7;

      recupCurseur = DELAI_CURSEUR;

    }

  }

}


/**
    \fn void utilisationArt()
    \brief cette fonction permet d'utiliser "l'art" sur lequel est positionne notre curseur
*/

void utilisationArt() {

  if(testTouche(clavier[SDL_SCANCODE_E]) && !clavier[SDL_SCANCODE_1].enfonce && !clavier[SDL_SCANCODE_3].enfonce) { //si on appuie sur A sans appuiyer sur les gachette on utilise l'art sur lequel est positionn� notre curseur

    if(equipe[indicePersonnage]->delaiArt < 0) {

      if(ArtJeu[indicePersonnage][positionCurseur]->BUT == attaque) {

        if(coop) {

          if(serveur) {

            utiliseArt(positionCurseur, indicePersonnage);

          } else {

            char data[100];

            sprintf(data, "a;%d;%d", positionCurseur, indicePersonnage);

            fprintf(stderr, "Principale : %s\n", data);

            send(to_server_socket, data, sizeof(data), 0);

          }

        } else {

          utiliseArt(positionCurseur, indicePersonnage);

        }


      } else if(ArtJeu[indicePersonnage][positionCurseur]->BUT == soutien) {

        if(ArtJeu[indicePersonnage][positionCurseur]->CIBLE_ALLIE == membreGroupe && ArtJeu[indicePersonnage][positionCurseur]->recup < 0) {

          etatCombat = 1;

        } else {

          if(coop) {

            if(serveur) {

              utiliseArtBuff(positionCurseur, indicePersonnage, 0);

            } else {

              char data[100];

              sprintf(data, "b;%d;%d;%d", positionCurseur, indicePersonnage, 0);

              fprintf(stderr, "Principale : %s\n", data);

              send(to_server_socket, data, sizeof(data), 0);

            }

          } else {

            utiliseArtBuff(positionCurseur, indicePersonnage, 0);

          }

        }

      }

    }

  }

}



/**
    \fn void choixCibleArt()
    \brief cette fonction permet de choisir une cible (parmis nos allies) quand "l'art" que l'on utilise en requiere une
*/


void choixCibleArt() {

  if(recupCible-- < 0) {

    if(clavier[SDL_SCANCODE_DOWN].enfonce) {

      cible += 1;
      cible %= 3;

      recupCible = DELAI_CIBLE;

    } else if(clavier[SDL_SCANCODE_UP].enfonce) {

      cible -= 1;
      if(cible < 0) cible = 2;

      recupCible = DELAI_CIBLE;

    }

    if(testTouche(clavier[SDL_SCANCODE_E])) {

      if(coop) {

        if(serveur) {

          utiliseArtBuff(positionCurseur, indicePersonnage, cible);

        } else {

          char data[100];

          sprintf(data, "b;%d;%d;%d", positionCurseur, indicePersonnage, cible);

          fprintf(stderr, "Principale : %s\n", data);

          send(to_server_socket, data, sizeof(data), 0);

        }

      } else {

        utiliseArtBuff(positionCurseur, indicePersonnage, cible);

      }

      etatCombat = 0;

    }

  }

}


/**
    \fn void choixCibleEnnemi()
    \brief cette fonction permet changer de cible parmis tout les ennemis presents
*/


void choixCibleEnnemi() {

  if(recupCibleEnn-- < 0) {

    if(clavier[SDL_SCANCODE_I].enfonce) {

      equipe[indicePersonnage]->cible++;

      equipe[indicePersonnage]->cible %= nbEnnemi;

      equipe[indicePersonnage]->enChoixCible = 1;

      recupCibleEnn = DELAI_CIBLE_ENN;

      if(coop) {

        char data[100];

        sprintf(data, "y;%d;%d", indicePersonnage, equipe[indicePersonnage]->cible);

        fprintf(stderr, "Principale : %s\n", data);

        if(serveur) {

          send(client_socket1, data, sizeof(data), 0);

          send(client_socket2, data, sizeof(data), 0);

        } else {

          send(to_server_socket, data, sizeof(data), 0);

        }

      }

    }


    if(clavier[SDL_SCANCODE_P].enfonce) {

      equipe[indicePersonnage]->cible--;

      if(equipe[indicePersonnage]->cible < 0) equipe[indicePersonnage]->cible = nbEnnemi-1;

      equipe[indicePersonnage]->enChoixCible = 1;

      recupCibleEnn = DELAI_CIBLE_ENN;

      if(coop) {

        char data[100];

        sprintf(data, "y;%d;%d", indicePersonnage, equipe[indicePersonnage]->cible);

        fprintf(stderr, "Principale : %s\n", data);

        if(serveur) {

          send(client_socket1, data, sizeof(data), 0);

          send(client_socket2, data, sizeof(data), 0);

        } else {

          send(to_server_socket, data, sizeof(data), 0);

        }

      }

    }

  }

}



/**
    \fn void echangePerso()
    \brief cette fonction appelle d'autres fonction pour permettre de changer de personnage
*/


void echangePerso() {

  if(clavier[SDL_SCANCODE_3].enfonce) { //Si on appuie sur la gachette droite on donner des ordres au personnage le plus � droite ou bien le controller

    if(testTouche(clavier[SDL_SCANCODE_E])) {  //si on appuie sur E on controle le personnage

      controlePerso(equipe, &indicePersonnage, droite);

    }

  }

  if(clavier[SDL_SCANCODE_1].enfonce) {  //m�me chose pour la gachette gauche

    if(testTouche(clavier[SDL_SCANCODE_E])) {

      controlePerso(equipe, &indicePersonnage, gauche);

    }

  }

}


/**
    \fn void ordreAttaque()
    \brief cette fonction donne l'ordre à tout les personnage d'attaquer une cible
*/

void ordreAttaque() {

  if(testTouche(clavier[SDL_SCANCODE_SPACE])) {

    for(int j = 0; j < 3; j++) {

      equipe[j]->cible = equipe[indicePersonnage]->cible;

      equipe[j]->enCombat = 1;

      equipe[j]->enChoixCible = 0;

    }

  }

}


/**
    \fn void mortalKombat()
    \brief cette fonction appelle toutes les fonctions necessaire pour que le systeme de combat fonctionne
*/


void mortalKombat() {


  autoAttaque();

  //////////////////////////////////////FONCTIONS D'INPUTS POUR LE COMBAT////////////////////////////////////////////


  switch(etatCombat) {

    case 0:       //deplacement, choix et activations des arts, controle des personnages

      if(!coop) ordreNouvCible();
      choixArt();
      utilisationArt();
      break;

    case 1:         //choix de la cible d'un art de soutien

      choixCibleArt();
      break;

  }


  choixCibleEnnemi();


  if(!coop) {

    ordreAttaque();
    echangePerso();

  }

  //////////////////////////////////////FONCTIONS D'INPUTS DE DEPLACEMENT////////////////////////////////////////////



  deplacementClavier(indicePersonnage, equipe, clavier);



  //////////////////////////////////////FONCTIONS DE DECREMENTATION DES ETATS////////////////////////////////////////////



  etatEnnemi();



  recuperationArt();      //d�cr�mentations des arts des personnages


  delaiModificationPerso();           //d�crementations des modifications des personnages


  delaiModificationEnnemi();


    //////////////////////////////////////FONCTIONS DE DEPLACEMENT////////////////////////////////////////////


  if(!coop) {

    persoPoursuit(indicePersonnage);

  }



  deplacementPersonnage(equipe);

  if(equipe[indicePersonnage]->vitX != 0 || equipe[indicePersonnage]->vitY != 0) {

    if(coop) {

      char data[100];

      sprintf(data, "p;%d;%d;%d", indicePersonnage, equipe[indicePersonnage]->posX, equipe[indicePersonnage]->posY);

      fprintf(stderr, "Principale : %s\n", data);

      if(serveur) {

        send(client_socket1, data, sizeof(data), 0);

        send(client_socket2, data, sizeof(data), 0);

      } else {

        send(to_server_socket, data, sizeof(data), 0);

      }

    }

  }

  deplacementEnnemi(equipe);

}



/**
    \fn void connexion()
    \brief cette fonction permet au client de se connecter au serveur et au serveur d'attendre la connexion des ses clients
*/


void connexion() {

  int ma_socket;
  struct sockaddr_in mon_address, client_address1, client_address2;
  unsigned int mon_address_longueur;

  struct sockaddr_in serveur_addr;
  struct hostent *serveur_info;
  long hostAddr;



  if(serveur) {

    bzero(&mon_address,sizeof(mon_address));
    mon_address.sin_port = htons(30000);
    mon_address.sin_family = AF_INET;
    mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

    char *hostname = "localhost";
      char ip[100];

      hostname_to_ip(hostname , ip);
    fprintf(stderr, "%s resolved to %s" , hostname , ip);
    view_ip();

    /* creation de socket */
    if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== -1) {
      printf("Impossible de créer la socket\n");
      exit(0);
    }

    /* bind serveur - socket */
    bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));
    /* ecoute sur la socket */
    listen(ma_socket,5);
    /* accept la connexion */
    mon_address_longueur = sizeof(client_address1);

      /* on attend que le client se connecte */
    client_socket1 = accept(ma_socket,(struct sockaddr *)&client_address1, &mon_address_longueur);

    client_socket2 = accept(ma_socket,(struct sockaddr *)&client_address2, &mon_address_longueur);
    char data[100];

    sprintf(data, "%d", (indicePersonnage+1%3));

    fprintf(stderr, "Principale : %s\n", data);

    send(client_socket1, data, sizeof(data), 0);

    sprintf(data, "%d", (indicePersonnage+2%3));

    fprintf(stderr, "Principale : %s\n", data);

    send(client_socket2, data, sizeof(data), 0);


  } else {


  	bzero(&serveur_addr,sizeof(serveur_addr));
  	hostAddr = inet_addr(SERVEURNAME);
  	if ( (long)hostAddr != (long)-1 ){
  		bcopy(&hostAddr,&serveur_addr.sin_addr,sizeof(hostAddr));
  	} else {
  		serveur_info = gethostbyname(SERVEURNAME);
  	  	if (serveur_info == NULL) {
  			printf("Impossible de récupérer les infos du serveur\n");
  			exit(0);
  	  	}
  	  	bcopy(serveur_info->h_addr,&serveur_addr.sin_addr,serveur_info->h_length);
  	}
  	serveur_addr.sin_port = htons(30000);
  	serveur_addr.sin_family = AF_INET;

  	if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0) {
  		printf("Impossible de créer la socket client\n");
  	  	exit(0);
  	}

  	if(connect( to_server_socket, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr)) < 0 ) {
  		printf("Impossible de se connecter au serveur\n");
  	  	exit(0);
  	}

    char data[100];

    recv(to_server_socket, data, sizeof(data), 0);

    sscanf(data, "%d", &indicePersonnage);

  }


  pthread_t monThreadCompteur1, monThreadCompteur2;


  if(serveur) {

    pthread_create (&monThreadCompteur1, NULL, recoit, &client_socket1);

    pthread_create (&monThreadCompteur2, NULL, recoit, &client_socket2);

  } else {

    pthread_create (&monThreadCompteur1, NULL, recoit, &to_server_socket);

  }


}

/**
    \fn void afficherCombat(SDL_Surface *pSurface)
    \brief cette fonction permet d'afficher touts les sprites necessaire au combat
    \param pSurface fenetre sur laquelle on affiche les sprites
*/

void afficherCombat(SDL_Surface *pSurface) {


  //////////////////////////////////////FONCTIONS DE CAMERA////////////////////////////////////////////

  if(equipe[indicePersonnage]->enChoixCible)  {

    SuiviCameraCombat(&camera, equipe[indicePersonnage], &ennemis[equipe[indicePersonnage]->cible]);

  } else if (equipe[indicePersonnage]->enCombat) {

    SuiviCameraCombat(&camera, equipe[indicePersonnage], &ennemis[equipe[indicePersonnage]->cible]);

  } else {

    SuiviCameraExploration(&camera, equipe[indicePersonnage]);

  }


  //////////////////////////////////////FONCTIONS D'AFFICHAGE////////////////////////////////////////////

  background(sol, pSurface, camera);

  for(int n = 0; n < nbEnnemi; n++) {

    if(ennemis[n].enCombat) {

      afficherHostilite(pSurface, &ennemis[n], equipe, camera);

    }

  }


  afficherPersonnages(pSurface, camera);

  afficherEnnemis(pSurface, camera);

  afficherArt(indicePersonnage, pSurface, cooldownArt);

  afficherCurseur(positionCurseur, pSurface);

  afficherHUD(equipe, pSurface);


  hudEnnemi(pSurface, camera);


  if(etatCombat == 1) afficherCible(cible, pSurface);


}


/**
    \fn void freeAll()
    \brief cette fonction permet de liberer la memoire que l'on a alloue au cours du programme quand on quitte celui-ci
*/

void freeAll() {

  for(int i = 0; i < 3; i++) {

    SDL_FreeSurface(equipe[i]->image);

    for(int j = 0; j < 9; j++) {

      SDL_FreeSurface(ArtJeu[i][j]->image);

    }

    free(equipe[i]);

  }

  for(int i = 0; i < nbEnnemiPool; i++) {

    SDL_FreeSurface(ennPool[i].image);

  }

  SDL_FreeSurface(sol);

  SDL_FreeSurface(cooldownArt);

  SDL_DestroyWindow(screen);

  IMG_Quit();

  TTF_Quit();

  SDL_Quit();



}




/**
    \fn void initJeu()
    \brief cette fonction permet d'allouer la memoire d'ont on a besoin au debut du programme
*/

void initJeu() {


  equipe[0] = malloc(sizeof(Personnage));
  equipe[1] = malloc(sizeof(Personnage));
  equipe[2] = malloc(sizeof(Personnage));



  initPersonnage(equipe[0], "./data/Guts.txt");   //initialisation des personnages selon des fichiers txt
  initPersonnage(equipe[1], "./data/Dio.txt");
  initPersonnage(equipe[2], "./data/Jojo.txt");


  sol = IMG_Load("./data/Sable.png");



  for(int i = 0; i < 9; i++) {

      char fichier[50];
      sprintf(fichier, "./data/JojoArt/");

      equipe[2]->ArtPool[i].idArt = i;
      initArt(&equipe[2]->ArtPool[i], fichier);     //initialisation des arts des personnages

  }

  for(int i = 0; i < 9; i++) {

      char fichier[50];
      sprintf(fichier, "./data/DioArt/");

      equipe[1]->ArtPool[i].idArt = i;
      initArt(&equipe[1]->ArtPool[i], fichier);

  }

  for(int i = 0; i < 9; i++) {

      char fichier[50];
      sprintf(fichier, "./data/GutsArt/");

      equipe[0]->ArtPool[i].idArt = i;
      initArt(&equipe[0]->ArtPool[i], fichier);

  }

  cooldownArt = IMG_Load("./data/cooldownArt.png");


  ArtJeu[0][0] = &equipe[0]->ArtPool[3];        //affectation des art d'un personnage
  ArtJeu[0][1] = &equipe[0]->ArtPool[4];
  ArtJeu[0][2] = &equipe[0]->ArtPool[5];
  ArtJeu[0][3] = &equipe[0]->ArtPool[6];
  ArtJeu[0][4] = &equipe[0]->ArtPool[7];
  ArtJeu[0][5] = &equipe[0]->ArtPool[0];
  ArtJeu[0][6] = &equipe[0]->ArtPool[1];
  ArtJeu[0][7] = &equipe[0]->ArtPool[2];

  ArtJeu[1][0] = &equipe[1]->ArtPool[0];
  ArtJeu[1][1] = &equipe[1]->ArtPool[1];
  ArtJeu[1][2] = &equipe[1]->ArtPool[2];
  ArtJeu[1][3] = &equipe[1]->ArtPool[3];
  ArtJeu[1][4] = &equipe[1]->ArtPool[4];
  ArtJeu[1][5] = &equipe[1]->ArtPool[5];
  ArtJeu[1][6] = &equipe[1]->ArtPool[6];
  ArtJeu[1][7] = &equipe[1]->ArtPool[8];

  ArtJeu[2][0] = &equipe[2]->ArtPool[0];
  ArtJeu[2][1] = &equipe[2]->ArtPool[1];
  ArtJeu[2][2] = &equipe[2]->ArtPool[2];
  ArtJeu[2][3] = &equipe[2]->ArtPool[3];
  ArtJeu[2][4] = &equipe[2]->ArtPool[4];
  ArtJeu[2][5] = &equipe[2]->ArtPool[5];
  ArtJeu[2][6] = &equipe[2]->ArtPool[6];
  ArtJeu[2][7] = &equipe[2]->ArtPool[7];

  initEnnemi(&ennPool[nbEnnemiPool++], "./data/Zanza.txt");

  initEnnemi(&ennPool[nbEnnemiPool++], "./data/Dickson.txt");


  ennemis[nbEnnemi] = ennPool[nbEnnemi];

  nbEnnemi++;

  ennemis[nbEnnemi] = ennPool[nbEnnemi];

  nbEnnemi++;


  recupCibleEnn = 0;           //variable affect� a DELAI_CIBLE_ENN

  positionCurseur = 0;

  recupCurseur = 0;           //variable affect� a DELAI_CURSEUR

  cible = 0;                  //indique quel personnage on cible avec un art de soutien

  recupCible = 0;             //variable qui permet de naviguer entre les cibles

}
