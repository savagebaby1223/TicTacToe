# Compilator si optiuni
CXX      = g++
CXXFLAGS = -std=c++14 -Wall

# Fisierele obiect ale bibliotecii de joc (clasele de date si logica)
LIB_OBJS = point.o board.o player.o human_player.o computer_player.o painter.o score_store.o game_engine.o

# Biblioteca statica proprie
LIB = libgame.a

all: TicTacToe

# 1. Construieste biblioteca statica din clasele jocului
$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

# 2. Leaga aplicatia de biblioteca proprie (-lgame) si de biblioteca externa SQLite (-lsqlite3)
TicTacToe: main.o $(LIB)
	$(CXX) -o TicTacToe.exe main.o -L. -lgame -lsqlite3

point.o: point.cpp point.hpp
	$(CXX) $(CXXFLAGS) -c point.cpp -o point.o

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp -o board.o

player.o: player.cpp player.hpp
	$(CXX) $(CXXFLAGS) -c player.cpp -o player.o

human_player.o: human_player.cpp human_player.hpp
	$(CXX) $(CXXFLAGS) -c human_player.cpp -o human_player.o

computer_player.o: computer_player.cpp computer_player.hpp
	$(CXX) $(CXXFLAGS) -c computer_player.cpp -o computer_player.o

painter.o: painter.cpp painter.hpp
	$(CXX) $(CXXFLAGS) -c painter.cpp -o painter.o

score_store.o: score_store.cpp score_store.hpp
	$(CXX) $(CXXFLAGS) -c score_store.cpp -o score_store.o

game_engine.o: game_engine.cpp game_engine.hpp
	$(CXX) $(CXXFLAGS) -c game_engine.cpp -o game_engine.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o *.a *.exe

.PHONY: all clean
