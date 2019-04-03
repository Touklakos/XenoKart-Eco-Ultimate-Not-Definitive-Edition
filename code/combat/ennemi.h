
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

#include "deplacement.h"


typedef struct {

    int posX;
    int posY;
    int vitX;
    int vitY;
    int orientationAbsolue;                //orientation (en haut, en bas, � droite, � gauche, en bas � droite, etc ...) par rapport à l'écran

    SDL_Surface* image;
    int numFrame;
    char nom[50];


    //def stats in-game
    int NV;

    int MAXPV;
    int PV;
    int FRC;
    int MGE;
    int ATTMIN;
    int ATTMAX;
    int VITATT;
    int CRIT;
    int CNTR;
    int DBLATT;
    int GARDE;
    int DEFPHY;
    int DEFMGE;
    int AGI;
    int DEXT;
    int PRTAUTO;
    int RES_ETATS[3];

    float modif[15];               //stat �gale � celle ci-dessus, elle peut changer au cours d'un combat gr�ce � d'autres arts (les modifications seront rang�es dans "delai[MAXPV]" pour MAXPV "delai[FRC]" pour FRC etc ...) (variable utilis� pour les calculs en combat)
    Modif delai[15][50];           //valeurs et delais des modifications de "modifMAXPV" (quand le delai est �gal � 0 on modifie (modifMAXPV dans l'autre sens)
    int nbDelai[15];               //nombre de modification sur modif


    int CHANCE;

    int hostilite[3];

    int cible;


    Etat etats[3];

    int delaiAuto;

    int enCombat;


} Ennemi;

extern Ennemi ennPool[100];

extern int nbEnnemiPool;

extern Ennemi ennemis[100];

extern int nbEnnemi;


extern int client_socket1, client_socket2, to_server_socket;

extern int coop;
extern int serveur;



void initEnnemi(Ennemi* ennemi, char fichier[50]);
int cibleEnnemis();
void ennemiPoursuit();
void deplacementEnnemi();
void afficherEnnemis(SDL_Surface *pSurface, SDL_Rect camera);
void hudEnnemi(SDL_Surface *pSurface, SDL_Rect camera);
int orientationPersoCombatAbsolue(int indice);
int orientationPersoCombatRelative(int indice);
int typeCoupPerso(int indice);
int typeCoupEnnemi(int indice);
int ennemiAutoAttaque(int indice, int degats, int type);
int attaqueAllie();
int persoAutoAttaque(int indice, int degats, int type);
int attaqueEnnemi();
int lanceArt(int indiceArt, int indicePersonnage, int degats);
int utiliseArt(int indiceArt, int indicePersonnage);
int etatEnnemi();
void delaiEtatEnnemis();
void delaiModificationEnnemi();
void persoPoursuit(int indicePersonnage);
void deplacementPersonnage();
void afficherPersonnages(SDL_Surface* pSurface, SDL_Rect camera);
void utiliseArtBuff(int indiceArt, int indicePersonnage, int cible);
