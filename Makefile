CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o move.o player.o humanplayer.o aiplayer.o level1.o level2.o level3.o level4.o piece.o pawn.o rook.o knight.o bishop.o queen.o king.o board.o subject.o graphicsobserver.o textobserver.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
