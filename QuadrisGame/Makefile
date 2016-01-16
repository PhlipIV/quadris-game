CXX=g++
XXFLAGS=-Wall -MMD
EXEC=quadris
OBJECTS=main.o block.o iblock.o jblock.o lblock.o oblock.o sblock.o zblock.o tblock.o command.o grid.o levelControl.o quadris.o displayControl.o blockControl.o window.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC}
