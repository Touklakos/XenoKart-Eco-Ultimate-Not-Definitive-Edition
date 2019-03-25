
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>


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

char buffer[512];

int client_socket1, client_socket2, to_server_socket;
int coop;
int serveur;


int etatCombat = 0;             //Si on se bat normalement ou si on est en train de choisir une cible pour un art de soutien


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
    \fn void gererTexte(degatsTxt *tab, int *nbMembre, SDL_Surface *pSurface, SDL_Rect camera)
    \brief Affiche les valeur de degats et de soin au dessus des personnages et des ennemi concerné, puis fait disparaitre les texte au bout de quelque instants
    \param tab le tableau de texte
    \param nbMembre le nombre de texte afficher à l'ecran
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
    \param etat etat en cours (en exploration, en combat)
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


  int nbNouvEnn = 1;

  //scanf("%d", &nbNouvEnn);

  for(int i = 0; i < nbNouvEnn; i++) {

    int temp = rand()%nbEnnemiPool;

    ennemis[(*nbEnnemi)++] = ennPool[temp];

  }


}






int testTouche(doublet clavier) {

  return clavier.enfonce && clavier.relache;

}



void fin(int sig){
	printf("fin du serveur");
}

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






void * recoit(void *sock) {

  SDL_Delay(1000);

  char data[100];

  int *socket1 = sock;

  while(1) {


    recv(*socket1, data, sizeof(data), 0);

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
        break;

      case 'a':
        sscanf(data, "%c;%d;%d", &type, &positionCurseur, &indicePersonnage);
        utiliseArt(positionCurseur, indicePersonnage);
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
        sscanf(data, "%c;%d;%d", &type, &indicePersonnage, &degats, &typeCoup);
        ennemiAutoAttaque(indicePersonnage, degats, typeCoup);
        break;

      case 'y':
        sscanf(data, "%c;%d;%d", &type, &indicePersonnage, &cible);
        equipe[indicePersonnage]->cible = cible;
        break;

    }

    strcpy(data, "");

  }

}




int main(int argc, char** argv)
{

  coop = 1;
  serveur = 0;
  if(argc == 2)
    serveur = 1;



  int ma_socket;
  struct sockaddr_in mon_address, client_address1, client_address2;
  unsigned int mon_address_longueur, lg1, lg2;

  struct sockaddr_in serveur_addr;
  struct hostent *serveur_info;
  long hostAddr;

    if(coop) {

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


      //  client_socket2 = accept(ma_socket,(struct sockaddr *)&client_address2, &mon_address_longueur);

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





      }

  }


//	pthread_t monThreadCompteur;

  if(coop) {

    if(serveur) {

      pthread_create (&monThreadCompteur, NULL, recoit, &client_socket1);

    } else {

      pthread_create (&monThreadCompteur, NULL, recoit, &to_server_socket);

    }

  }


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




    Personnage Guts;
    Personnage Dio;
    Personnage Jojo;

    equipe[0] = &Guts;
    equipe[1] = &Dio;
    equipe[2] = &Jojo;



    initPersonnage(&Guts, "./data/Guts.txt");   //initialisation des personnages selon des fichiers txt
    initPersonnage(&Dio, "./data/Dio.txt");
    initPersonnage(&Jojo, "./data/Jojo.txt");

    SDL_Surface * sol;

    sol = IMG_Load("./data/Sable.png");



    for(int i = 0; i < 9; i++) {

        char fichier[50];
        sprintf(fichier, "./data/JojoArt/");

        Jojo.ArtPool[i].idArt = i;
        initArt(&Jojo.ArtPool[i], fichier);     //initialisation des arts des personnages

    }

    for(int i = 0; i < 9; i++) {

        char fichier[50];
        sprintf(fichier, "./data/DioArt/");

        Dio.ArtPool[i].idArt = i;
        initArt(&Dio.ArtPool[i], fichier);

    }

    for(int i = 0; i < 9; i++) {

        char fichier[50];
        sprintf(fichier, "./data/GutsArt/");

        Guts.ArtPool[i].idArt = i;
        initArt(&Guts.ArtPool[i], fichier);

    }

    SDL_Surface *cooldownArt = IMG_Load("./data/cooldownArt.png");


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

    /*Ennemi Zanza;

    Ennemi Dickson;*/

    initEnnemi(&ennPool[nbEnnemiPool++], "./data/Zanza.txt");

    initEnnemi(&ennPool[nbEnnemiPool++], "./data/Dickson.txt");





    ennemis[nbEnnemi] = ennPool[nbEnnemi];

    nbEnnemi++;

    ennemis[nbEnnemi] = ennPool[nbEnnemi];

    nbEnnemi++;

    SDL_Event event;

    int quit = 0;               //quitte le programme si on appui sur la croix rouge

    int indicePersonnage = 0;       //variable qui indique quel personnage on est entrain de controller

    if(serveur) indicePersonnage = 1;

    int recupCibleEnn = 0;           //variable affect� a DELAI_CIBLE_ENN

    int positionCurseur = 0;

    int recupCurseur = 0;           //variable affect� a DELAI_CURSEUR

    int cible = 0;                  //indique quel personnage on cible avec un art de soutien

    int recupCible = 0;             //variable qui permet de naviguer entre les cibles


    long long unsigned debut, fin, fpsCount = 0;

    doublet clavier[1000];

    for(int i = 0; i< 1000; i++) {

      clavier[i].enfonce = 0;
      clavier[i].relache = 0;

    }

    while(!quit) {

      //////////////////////////////////////FONCTIONS D'AFFICHAGE DES FPS, DU BACKGROUND////////////////////////////////////////////


      debut = SDL_GetTicks();

      SDL_FillRect(pSurface, NULL, SDL_MapRGB(pSurface->format, 255, 255, 255)); //on nettoye l'�cran en affichant un grand rectangle blanc


      //////////////////////////////////////FONCTIONS ++&+ SUR CANAL+////////////////////////////////////////////


      SDL_PollEvent(&event);

      SDL_PumpEvents();
      const Uint8 *state = SDL_GetKeyboardState(NULL);      //Vérification de quelles sont les touche qui sont enfoncé sur le clavier

      for(int i = 0; i < 1000; i++) {

        if(state[i]) {

           clavier[i].enfonce = 1;

         } else {

           clavier[i].enfonce = 0;

         }

      }






      //////////////////////////////////////FONCTIONS AUTOMATIQUE DURANT LE COMBAT////////////////////////////////////////////



      if(coop) {

        if(serveur) {

          attaqueAllie();

        }

        if(equipe[indicePersonnage]->PV > 0) {

          if(equipe[indicePersonnage]->delaiArt < 0) {

            equipe[indicePersonnage]->delaiAuto--;

            orientationPersoCombatRelative(indicePersonnage);

            if(distance(equipe[indicePersonnage]->posX, equipe[indicePersonnage]->posY, ennemis[equipe[indicePersonnage]->cible].posX, ennemis[equipe[indicePersonnage]->cible].posY) - ennemis[equipe[indicePersonnage]->cible].image->w/2/4 < equipe[indicePersonnage]->PRTAUTO && equipe[indicePersonnage]->delaiAuto < 0) {

                persoAutoAttaque(indicePersonnage, -1, -1);

            }

          }

        }

      } else {

        attaqueAllie();

        attaqueEnnemi();  //les personnages attaques l'ennemi qu'ils ciblent

      }



      //////////////////////////////////////FONCTIONS D'INPUTS POUR LE COMBAT////////////////////////////////////////////


            switch(etatCombat) {

              case 0:       //deplacement, choix et activations des arts, controle des personnages

                if(!coop) {

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



                if(testTouche(clavier[SDL_SCANCODE_E]) && !clavier[SDL_SCANCODE_1].enfonce && !clavier[SDL_SCANCODE_3].enfonce) { //si on appuie sur A sans appuiyer sur les gachette on utilise l'art sur lequel est positionn� notre curseur

                  if(equipe[indicePersonnage]->delaiArt < 0) {

                    if(ArtJeu[indicePersonnage][positionCurseur]->BUT == attaque) {

                      utiliseArt(positionCurseur, indicePersonnage);

                      char data[100];

                      sprintf(data, "a;%d;%d", positionCurseur, indicePersonnage);

                      fprintf(stderr, "Principale : %s\n", data);

                      if(serveur) {

                        send(client_socket1, data, sizeof(data), 0);

                      } else {

                        send(to_server_socket, data, sizeof(data), 0);

                      }


                    } else if(ArtJeu[indicePersonnage][positionCurseur]->BUT == soutien) {

                      if(ArtJeu[indicePersonnage][positionCurseur]->CIBLE_ALLIE == membreGroupe && ArtJeu[indicePersonnage][positionCurseur]->recup < 0) {

                        etatCombat = 1;

                      } else {

                        utiliseArtBuff(positionCurseur, indicePersonnage, 0);

                        char data[100];

                        sprintf(data, "b;%d;%d;%d", positionCurseur, indicePersonnage, 0);

                        fprintf(stderr, "Principale : %s\n", data);

                        if(serveur) {

                          send(client_socket1, data, sizeof(data), 0);

                        } else {

                          send(to_server_socket, data, sizeof(data), 0);

                        }

                      }

                    }

                  }

                }


              break;

                case 1:         //choix de la cible d'un art de soutien



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

                      utiliseArtBuff(positionCurseur, indicePersonnage, cible);

                      char data[100];

                      sprintf(data, "b;%d;%d;%d", positionCurseur, indicePersonnage, cible);

                      fprintf(stderr, "Principale : %s\n", data);

                      if(serveur) {

                        send(client_socket1, data, sizeof(data), 0);

                      } else {

                        send(to_server_socket, data, sizeof(data), 0);

                      }


                      etatCombat = 0;

                    }

                  }




                break;

                }

                for(int i = 0; i < nbEnnemi; i++) {

                  for(int j = 0; j < 3; j++)
                    fprintf(stderr, "hostilite de %s : %d\n", ennemis[i].nom, ennemis[i].hostilite[j]);

                }

                if(recupCibleEnn-- < 0) {

                  if(clavier[SDL_SCANCODE_I].enfonce) {

                    equipe[indicePersonnage]->cible++;

                    equipe[indicePersonnage]->cible %= nbEnnemi;

                    equipe[indicePersonnage]->enChoixCible = 1;

                    recupCibleEnn = DELAI_CIBLE_ENN;

                    char data[100];

                    sprintf(data, "y;%d;%d", indicePersonnage, equipe[indicePersonnage]->cible);

                    fprintf(stderr, "Principale : %s\n", data);

                    if(serveur) {

                      send(client_socket1, data, sizeof(data), 0);

                    } else {

                      send(to_server_socket, data, sizeof(data), 0);

                    }

                  }


                  if(clavier[SDL_SCANCODE_P].enfonce) {

                    equipe[indicePersonnage]->cible--;

                    if(equipe[indicePersonnage]->cible < 0) equipe[indicePersonnage]->cible = nbEnnemi-1;

                    equipe[indicePersonnage]->enChoixCible = 1;

                    recupCibleEnn = DELAI_CIBLE_ENN;

                    char data[100];

                    sprintf(data, "y;%d;%d", indicePersonnage, equipe[indicePersonnage]->cible);

                    fprintf(stderr, "Principale : %s\n", data);

                    if(serveur) {

                      send(client_socket1, data, sizeof(data), 0);

                    } else {

                      send(to_server_socket, data, sizeof(data), 0);

                    }

                  }

                }


                if(testTouche(clavier[SDL_SCANCODE_SPACE])) {

                  for(int j = 0; j < 3; j++) {

                    equipe[j]->cible = equipe[indicePersonnage]->cible;

                    equipe[j]->enCombat = 1;

                    equipe[j]->enChoixCible = 0;

                  }


                }



            if(!coop) {

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


            //////////////////////////////////////FONCTIONS D'INPUTS DE DEPLACEMENT////////////////////////////////////////////


            if(joy) {

              deplacementManette(controller, indicePersonnage, equipe);

            } else {

              deplacementClavier(indicePersonnage, equipe, clavier);

            }



            //////////////////////////////////////FONCTIONS DE DECREMENTATION DES ETATS////////////////////////////////////////////



            etatEnnemi();

            delaiEtatEnnemis();



            recuperationArt();      //d�cr�mentations des arts des personnages

            delaiModificationPerso();           //d�crementations des modifications des personnages



            delaiModificationEnnemi();


              //////////////////////////////////////FONCTIONS DE DEPLACEMENT////////////////////////////////////////////


              if(!coop) {

                persoPoursuit(indicePersonnage);

              }




              deplacementPersonnage(equipe);

              if(equipe[indicePersonnage]->vitX != 0 || equipe[indicePersonnage]->vitY != 0) {

                char data[100];

                sprintf(data, "p;%d;%d;%d", indicePersonnage, equipe[indicePersonnage]->posX, equipe[indicePersonnage]->posY);

                fprintf(stderr, "Principale : %s\n", data);

                if(serveur) {

                  send(client_socket1, data, sizeof(data), 0);

                } else {

                  send(to_server_socket, data, sizeof(data), 0);

                }

              }


              deplacementEnnemi(equipe);



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


              afficherPersonnages(screen, camera);

              afficherEnnemis(pSurface, camera);

              afficherArt(indicePersonnage, pSurface, cooldownArt);

              afficherCurseur(positionCurseur, pSurface);

              afficherHUD(equipe, pSurface);


              hudEnnemi(pSurface, camera);


              if(etatCombat == 1) afficherCible(cible, pSurface);

              gererTexte(pSurface, camera);

              gererEnnemis(ennemis, &nbEnnemi, equipe);

              while(nbEnnemi == 0) {

                victoire(screen, ennemis, &nbEnnemi);

              }

              SDL_UpdateWindowSurface(screen);

              for(int i = 0; i < 1000; i++) {

                if(state[i]) clavier[i].relache = 0;
                else clavier[i].relache = 1;

              }

              switch(event.type) {

                case SDL_QUIT:
                  quit = 1;
                  break;

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
