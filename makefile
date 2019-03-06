
CC=gcc

FLAGS =-Wall -g

SDL_DIR=${HOME}/Projet/XenoKart-Eco-Ultimate-Not-Definitive-Edition/SDL2

SDL_LIB_DIR=${SDL_DIR}/lib

SDL_INC_DIR=${SDL_DIR}/include

CODE=code/

COMBAT=${CODE}/combat/
MENU=${CODE}/menu/

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lm
INCS=-I${SDL_INC_DIR}
PROG=incroyable main

all: sdl_text cleanO

sdl_text: ${COMBAT}incroyable.c
	${CC} -c ${COMBAT}incroyable.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}art.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}perso.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}deplacement.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}ennemi.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}degatsTxt.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ${COMBAT}fonction.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -o ${PROG} incroyable.o art.o perso.o deplacement.o ennemi.o degatsTxt.o fonction.o ${LIBS} ${INCS} ${FLAGS}

menu: ${MENU}menu.c
	${CC} -c ${MENU}menu.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -o main menu.o ${LIBS} ${INCS} ${FLAGS}

cleanO:
	rm -f *.o

clean: cleanO
	rm -f ${PROG}
