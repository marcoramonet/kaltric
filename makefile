CXX = g++
CXXFLAGS = -Wall


ARGS = $(MAKECMDGOALS)
HEADERS = src/*.hpp
SRC = $(wildcard *.cpp)
BIN = out


out: 
	$(CXX) $(SRC) -o $(BIN)  $(CXXFLAGS)
	./$(BIN)
	rm $(BIN)

scrap:
	$(CXX) scrap.cpp FilePosition.cpp Lexer.cpp Token.cpp -o scrap $(CXXFLAGS)
	./scrap
	rm scrap

clean: 
	rm $(BIN)