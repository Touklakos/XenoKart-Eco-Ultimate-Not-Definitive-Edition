CC=gcc

FLAGS =-Wall -g

SDL_DIR=${HOME}/Projet/XenoKart-Eco-Ultimate-Not-Definitive-Edition/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include

CODE=code/

COMBAT=${CODE}/combat/
MENU=${CODE}/menu/
MAP=${CODE}/map/
LOBBY=${CODE}/lobby/

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lm -lpthread
INCS=-I${SDL_INC_DIR}
PROG=izi

all : iziAll clean

iziAll: izi.c menu map gestionMap lobby combat
		${CC} -c ${COMBAT}fonctionMain.c ${LIBS} ${INCS} ${FLAGS}
		${CC} -c izi.c ${LIBS} ${INCS} ${FLAGS}
		${CC} -o izi izi.o menu.o lobby.o fonctions.o ennemi.o art.o deplacement.o fonction.o perso.o degatsTxt.o map.o fonctionMain.o rentacleTape.o ${LIBS} ${INCS} ${FLAGS}

combat:
		${CC} -c ${COMBAT}ennemi.c ${LIBS} ${INCS} ${FLAGS}
		${CC} -c ${COMBAT}perso.c ${LIBS} ${INCS} ${FLAGS}
		${CC} -c ${COMBAT}art.c ${LIBS} ${INCS} ${FLAGS}
		${CC} -c ${COMBAT}deplacement.c ${LIBS} ${INCS} ${FLAGS}
		${CC} -c ${COMBAT}degatsTxt.c ${LIBS} ${INCS} ${FLAGS}
		${CC} -c ${COMBAT}fonction.c ${LIBS} ${INCS} ${FLAGS}

menu: ${MENU}menu.c
	${CC} -c ${MENU}menu.c ${LIBS} ${INCS} ${FLAGS}

map: ${MAP}map.c
	${CC} -c ${MAP}map.c ${LIBS} ${INCS} ${FLAGS}

gestionMap : ${MAP}rentacleTape.c map
	${CC} -c ${MAP}rentacleTape.c ${LIBS} ${INCS} ${FLAGS}

lobby : ${LOBBY}lobby.c
	${CC} -c ${LOBBY}lobby.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${LOBBY}fonctions.c ${LIBS} ${INCS} ${FLAGS}

clean:
	rm -f *.o

cleanall: clean
	rm -f ${PROG}
