
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
PROG=incroyable menu lobby map

all: sdl_text menu lobby map clean

sdl_text: ${COMBAT}incroyable.c
	${CC} -c ${COMBAT}incroyable.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}art.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}perso.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}deplacement.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}ennemi.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}degatsTxt.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}fonction.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${LOBBY}lobby.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${LOBBY}fonctions.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -o incroyable incroyable.o art.o perso.o deplacement.o ennemi.o degatsTxt.o fonction.o ${LIBS} ${INCS} ${FLAGS}
	${CC} -o lobby lobby.o fonctions.o perso.o degatsTxt.o ${LIBS} ${INCS} ${FLAGS}

menu: ${MENU}menu.c
	${CC} -c ${MENU}menu.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -o menu menu.o ${LIBS} ${INCS} ${FLAGS}

map: ${MAP}map.c
	${CC} -c ${MAP}map.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -o map map.o ${LIBS} ${INCS} ${FLAGS}

clean:
	rm -f *.o

cleanall: clean
	rm -f ${PROG}
