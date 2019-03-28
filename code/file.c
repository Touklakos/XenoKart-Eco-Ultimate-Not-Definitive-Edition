
#include <stdlib.h>

typedef struct element {

	int entier; 
	struct element* suiv;
	struct element* prec;

} tElement;


tElement *tete;
tElement *queue;


void initFile() {

	tete = NULL;
	queue = NULL;

}

int fileVide() {

	return tete == NULL;

}

void ajouter(int c) {

	tElement *nouv;

	nouv = malloc(sizeof(tElement));
	nouv->entier = c;
	nouv->suiv = NULL;
	if(fileVide()) {

		tete = nouv;

	} else {
		
		queue->suiv = nouv;

	}

	queue = nouv;

}

void retirer(int *c) {

	tElement *premier;

	if(!fileVide()) {

		premier = tete;
		*c = premier->entier;
		tete = premier->suiv;
		free(premier);

	}

}








