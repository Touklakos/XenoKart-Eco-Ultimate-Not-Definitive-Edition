
#include "art.h"

typedef struct {

    int posX;
    int posY;
    int vitX;
    int vitY;
    int orientationAbsolue;                //orientation (en haut, en bas, � droite, � gauche, en bas � droite, etc ...) par rapport à l'écran
    int orientationRelative;               //orientation (en haut, en bas, � droite, � gauche, en bas � droite, etc ...) par rapport � l'ennemi ciblé

    SDL_Surface* image;             //sprite du personnage (tableau dans le future pour animation)
    int numFrame;




    //def stats in-game
    int NV;
    int EXP;

    int MAXPV;                      //stat enregistr�e dans un fichier


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


    float modif[15];               //stat �gale � celle ci-dessus, elle peut changer au cours d'un combat gr�ce � d'autres arts (les modifications seront rang�es dans "delai[MAXPV]" pour MAXPV "delai[FRC]" pour FRC etc ...) (variable utilis� pour les calculs en combat)
    Modif delai[15][50];           //valeurs et delais des modifications de "modifMAXPV" (quand le delai est �gal � 0 on modifie (modifMAXPV dans l'autre sens)
    int nbDelai[15];               //nombre de modification sur modif


    int nbArt;
    Art ArtPool[20];


    int CHANCE;

    int tension;
    int delaiAuto;
    int delaiArt;


    int enCombat;
    int enChoixCible;
    int cible;



} Personnage;

void initPersonnage(Personnage* perso, char fichier[50]);
void afficherPersonnage(Personnage *perso, SDL_Window* screen, SDL_Rect camera);
void delaiModificationPerso(Personnage* perso);
void utiliseArtBuff(Art* art, Personnage* equipe[3], int indicePersonnage, SDL_Surface *pSurface);
