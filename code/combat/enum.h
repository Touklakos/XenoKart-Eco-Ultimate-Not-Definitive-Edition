
/**
  \file enum.h
  \brief enumeration du programme
  \author Mano Brabant
*/




/**
    \enum eType
    \brief Enumeration des types d'art
*/
typedef enum {physique, ether} eType;


/**
    \enum eBut
    \brief Enumeration des but des arts
*/
typedef enum {attaque, soutien} eBut;


/**
    \enum eCible
    \brief Enumeration des cibles possible pour un art de soutien
*/
typedef enum {soiMeme, allie, membreGroupe, groupe} eCible;


/**
    \enum eOrientationAbsolue
    \brief Enumeration des orientations absolue des personnages et des ennemis
*/
typedef enum {haut, droite, bas, gauche} eOrientationAbsolue;


/**
    \enum eOrientationRelative
    \brief Enumeration des orientations relatives des personnages par rapport aux ennemis
*/
typedef enum {devant, droiteR, derriere, gaucheR} eOrientationRelative;


/**
    \enum eBuff
    \brief Enumeration des differentes statistique modifiables durant le combat
*/
typedef enum {MAXPV, FRC, MGE, ATTMIN, ATTMAX, VITATT, CRIT, CNTR, DBLATT, GARDE, DEFPHY, DEFMGE, AGI, DEXT, PRTAUTO} eBuff;


/**
    \enum eEtat
    \brief Enumeration des etats
*/
typedef enum {fournaise, frisson, poison} eEtat;


/**
    \enum eCoup
    \brief Enumeration des type de coup
*/
typedef enum {normalC, critiqueC, esquiveC, gardeC, soinC, fournaiseC, frissonC, poisonC} eCoup;
