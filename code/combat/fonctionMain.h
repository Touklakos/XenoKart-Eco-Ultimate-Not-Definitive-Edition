
#include "ennemi.h"


extern char buffer[512];

extern int client_socket1, client_socket2, to_server_socket;
extern int coop;
extern int serveur;


extern int recupCurseur;           //variable affect� a DELAI_CURSEUR
extern int positionCurseur;
extern int recupCible;
extern int cible;
extern int recupCibleEnn;

extern int etatCombat;             //Si on se bat normalement ou si on est en train de choisir une cible pour un art de soutien


extern SDL_Surface * sol;


extern pthread_cond_t condition; /* Création de la condition */

extern pthread_mutex_t mutex; /* Création du mutex */



void afficherCible(int cible);
void afficherHUD();
void afficherCurseur(int a);
void SuiviCameraCombat(SDL_Rect *camera, Personnage *perso, Ennemi *enn);
void SuiviCameraExploration(SDL_Rect *camera, Personnage *perso);
void background(SDL_Rect camera);
void afficherHostilite(Ennemi *ennemi, SDL_Rect camera);
void gererTexte(SDL_Rect camera);
int controlePerso(int *indicePersonnage, int cote);
int gererEnnemis();
void victoire();
void defaite();
int testTouche(doublet clavier);
int hostname_to_ip(char * hostname , char* ip);
void view_ip();
void quitter(int to_server_socket);
void * recoit(void *sock);
void autoAttaque();
void ordreNouvCible();
void choixArt();
void utilisationArt();
void choixCibleArt();
void choixCibleEnnemi();
void echangePerso();
void ordreAttaque();
void mortalKombat();
void connexion();
void afficherCombat();
void freeAll();
void initJeu();
