#
# 20/03/2025
# UFRGS - INF01147 Compiladores - 2025/1
# Matheus Adam dos Anjos -> Arquivo base disponibilizado pelo professor
#

CXX = g++
CXXFLAGS = -std=c++11 -Wall

OBJ = lex.yy.o main.o symbols.o

target: etapa1

etapa1: $(OBJ)
	$(CXX) $(OBJ) -o etapa1

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -c

lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l 

clean:
	rm etapa1 lex.yy.cpp *.o

