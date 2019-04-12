

/**
  \file modif.h
  \brief Structure qui permet de sauvegarder les valeurs de modifications des stats (valeur) pendant un certain temps (delai)
  \author Mano Brabant
*/


/*Structure qui permet de sauvegarder les valeurs de modifications des stats (valeur) pendant un certain temps (delai)*/

/**
    \struct Modif
    \brief Structure des modifications des statistiques
*/


typedef struct {

    float valeur;

    int delai;

} Modif;
