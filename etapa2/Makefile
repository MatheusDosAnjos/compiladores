#
# 20/03/2025
# UFRGS - INF01147 Compiladores - 2025/1
# Matheus Adam dos Anjos
#

CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = etapa2
OBJ = parser.tab.o lex.yy.o main.o symbols.o

target: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -c

lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l 

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

clean:
	rm $(TARGET) lex.yy.cpp parser.tab.* *.o

