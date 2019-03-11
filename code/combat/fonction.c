
#include "fonction.h"


/**
  \file fonction.c
  \brief texte des degats qui serront afficher à l'ecran
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
*/

int distance(int a, int b, int c, int d) {

    int vecX = c-a;
    int vecY = d-b;

    return (int) sqrt(vecX*vecX + vecY*vecY);

}

int collision(int h1, int d1, int b1, int g1, int h2, int d2, int b2, int g2) {

  return h1 > b2 && d1 < g2 && b1 < h2 && g1 > d2;

}
