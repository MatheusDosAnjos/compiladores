#
# 05/04/2025
# UFRGS - INF01147 Compiladores - 2025/1
# Matheus Adam dos Anjos
#

CXX = g++
CXXFLAGS = -std=c++11 -Wall

TARGET = etapa4
OBJ = parser.tab.o lex.yy.o main.o symbols.o ast.o semantic.o

GREEN  = \033[0;32m
RED    = \033[0;31m
NC     = \033[0m

target: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) $< -c

lex.yy.cpp: scanner.l parser.tab.hpp
	flex -o lex.yy.cpp scanner.l 

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

test:
	@echo "Running tests with $(TARGET)..."
	@for file in tests/*; do \
		printf "==> $$file ... "; \
		./$(TARGET) $$file; \
		RC=$$?; \
		if [ $$RC -eq 0 ]; then printf "$(GREEN)[OK]$(NC)\n"; \
		elif [ $$RC -eq 3 ]; then printf "$(RED)[SYNTAX ERROR]$(NC)\n"; \
		elif [ $$RC -eq 4 ]; then printf "$(RED)[SEMANTIC ERROR]$(NC)\n"; \
		else printf "[RC=$$RC]\n"; \
		fi; \
	done

clean:
	rm $(TARGET) lex.yy.cpp parser.tab.cpp parser.tab.hpp *.o
