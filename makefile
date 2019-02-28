
CC=gcc

FLAGS =-Wall -g

SDL_DIR=${HOME}/Projet/XenoKart-Eco-Ultimate-Not-Definitive-Edition/SDL2

SDL_LIB_DIR=${SDL_DIR}/lib

SDL_INC_DIR=${SDL_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lm
INCS=-I${SDL_INC_DIR}
PROG=incroyable

all: sdl_text

sdl_text: incroyable.c
	${CC} -c incroyable.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c art.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c perso.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c deplacement.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c ennemi.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c degatsTxt.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -c fonction.c ${LIBS} ${INCS} ${FLAGS}
	${CC} -o ${PROG} incroyable.o art.o perso.o deplacement.o ennemi.o degatsTxt.o fonction.o ${LIBS} ${INCS} ${FLAGS}



clean:
	rm -f ${PROG}
	rm -f *.o
