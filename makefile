CXX = g++
CXXFLAGS = -Wall


ARGS = $(MAKECMDGOALS)
HEADERS = src/*.hpp
SRC = $(wildcard src/*.cpp)
BIN = out


out: 
	$(CXX) $(SRC) -o $(BIN)  $(CXXFLAGS)
	./$(BIN)
	rm $(BIN)

clean: 
	rm $(BIN)

x:
	echo $(SRC)