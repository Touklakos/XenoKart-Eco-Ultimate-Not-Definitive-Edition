#include "modif.h"
#include "etat.h"
#include "const.h"
#include "fonction.h"
#include "degatsTxt.h"

/*Structure des arts (attaque sp�ciales des personnages)*/

typedef struct {

    int TYPE;           //physique ou ether (differentes facon de calculer les degats)
    int BUT;            //attaque ou soutien
    int CIBLE_ALLIE;         //un alli�/ le groupe/ un ennemi/ tous les ennemis/ etc ...
    int DMGMIN[4];         //D�gats minimum de l'art
    int DMGMAX[4];         //D�gats maximum de l'art
    int delaiRecup[4];     //D�lai requis entre deux utilisation
    int recup;          //Variable qui prend la valeur de delaiRecup quand l'art est utilis� (l'art peut �tre quand cette variable est inf�rieure � 0)
    int delaiRecupAct;  //Variable qui prend la valeur de delaiRecup quand l'art est utilisé (elle n'est pas décrémenté elle servira a afficher le cooldown))
    int delaiAnimation;
    int nbFrames;
    int PRTART[4];         //port�e de l'art
    int idArt;          //identifiant de l'art
    SDL_Surface *image; //image de l'art (en bas de l'ecran)
    int etats[4][3];      //valeur de l'effet fournaise, frisson, poison



    Modif buff[15];    //valeurs des differents buff applicable � un personnage
    Modif debuff[4][15];    //valeurs des differents debuff applicable � un ennemi


    int soin;

} Art;

int initArt(Art *art, char fichier[50]);
void afficherArt(Art *art[], SDL_Surface* screen, SDL_Surface *cooldownArt);
void recuperationArt(Art *art);
