#include "deplacement.h"


typedef struct {

    int posX;
    int posY;
    int vitX;
    int vitY;
    int orientationAbsolue;                //orientation (en haut, en bas, � droite, � gauche, en bas � droite, etc ...) par rapport à l'écran

    SDL_Surface* image[4];
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

void initEnnemi(Ennemi* ennemi, char fichier[50]);
int cibleEnnemi(Ennemi *ennemi);
void ennemiPoursuit(Ennemi *ennemi, Personnage *perso);
void deplacementEnnemi(Ennemi* ennemi, Personnage *equipe[]);
void afficherEnnemi(Ennemi *ennemi, SDL_Surface *pSurface, SDL_Rect camera, Personnage *equipe[], int etat);
void hudEnnemi(Ennemi *ennemi, SDL_Surface *pSurface, SDL_Rect camera);
int orientationPersoCombatAbsolue(Personnage* perso, Ennemi* ennemi);
int orientationPersoCombatRelative(Personnage* equipe[], int indicePersonnage, Ennemi* ennemi);
int typeCoupPerso(Personnage *perso, Ennemi *ennemi);
int typeCoupEnnemi(Ennemi *ennemi, Personnage *perso);
int ennemiAutoAttaque(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt);
int attaqueAllie(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt);
int persoAutoAttaque(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt);
int attaqueEnnemi(Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt);
int lanceArt(Art *art, Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt);
int utiliseArt(Art* art, Personnage* equipe[], Ennemi* ennemi, int indice, degatsTxt dgtsTxt[], int *nbDgtTxt);
int etatEnnemi(Ennemi *enn, int type, degatsTxt dgtsTxt[], int *nbDgtTxt);
void delaiEtat(Ennemi *ennemi);
void delaiModificationEnnemi(Ennemi* ennemi);
void persoPoursuit(Personnage *perso, Ennemi *ennemi);
void deplacementPersonnage(Personnage *equipe[], int indicePersonnage, Ennemi ennemis[]);
