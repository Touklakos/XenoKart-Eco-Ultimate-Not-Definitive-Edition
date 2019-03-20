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





void initEnnemi(Ennemi* ennemi, char fichier[50]);
int cibleEnnemis();
void ennemiPoursuit(Personnage *equipe[]);
void deplacementEnnemi(Personnage *equipe[]);
void afficherEnnemis(SDL_Surface *pSurface, SDL_Rect camera, Personnage *equipe[]);
void hudEnnemi(SDL_Surface *pSurface, SDL_Rect camera);
int orientationPersoCombatAbsolue(Personnage* perso);
int orientationPersoCombatRelative(Personnage* equipe[], int indicePersonnage);
int typeCoupPerso(Personnage *perso);
int typeCoupEnnemi(Ennemi *ennemi, Personnage *perso);
int ennemiAutoAttaque(Personnage* equipe[], Ennemi* ennemi, int indice);
int attaqueAllie(Personnage* equipe[]);
int persoAutoAttaque(Personnage* equipe[], int indice);
int attaqueEnnemi(Personnage* equipe[]);
int lanceArt(Art *art, Personnage* equipe[], int indice);
int utiliseArt(Art* art, Personnage* equipe[], int indice);
int etatEnnemi();
void delaiEtatEnnemis();
void delaiModificationEnnemi();
void persoPoursuit(Personnage *perso);
void deplacementPersonnage(Personnage *equipe[]);
