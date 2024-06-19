CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD -g -Werror=vla
EXEC = watopoly
OBJECTS = main.o controller.o display.o game.o location.o player.o property.o PropertyGym.o PropertyRegular.o PropertyResidence.o subject.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

