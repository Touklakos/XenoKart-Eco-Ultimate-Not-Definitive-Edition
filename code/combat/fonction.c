
#include "fonction.h"


/**
  \file fonction.c
  \brief boite à outils
  \author Mano Brabant
  \version 0.01
  \date 13 fevrier 2019
*/

/**
    \fn int distance(int a, int b, int c, int d)
    \brief calcule la distance entre deux points
    \param a composante en x du premier point
    \param b composante en y du premier point
    \param c composante en x du deuxieme point
    \param d composante en y du deuxieme point
    \return la distance entre les deux points
*/

int distance(int a, int b, int c, int d) {

    int vecX = c-a;
    int vecY = d-b;

    if(vecX == 0 && vecY == 0) return 0;

    return (int) sqrt(vecX*vecX + vecY*vecY);

}


/**
    \fn int collision(int h1, int d1, int b1, int g1, int h2, int d2, int b2, int g2)
    \brief calcule si deux AABB(Axis Aligned Bounding Box) sont en collision
    \param h1 taille minimum en y
    \param d1 taille maximum en x
    \param b1 taille maximum en y
    \param g1 taille minimum en x
    \param h2 taille minimum en y
    \param d2 taille maximum en x
    \param b2 taille maximum en y
    \param g2 taille minimum en x
    \si les deux AABB(Axis Aligned Bounding Box) sont en collision
*/


int collision(int h1, int d1, int b1, int g1, int h2, int d2, int b2, int g2) {

  return h1 > b2 && d1 < g2 && b1 < h2 && g1 > d2;

}
