# Makefile pentru proiectul TicTacToe
#
#   make         construieste jocul (TicTacToe.exe)
#   make test    construieste si ruleaza testele unitare
#   make docs    genereaza documentatia cu Doxygen (in directorul docs/)
#   make clean   sterge fisierele generate

CXX      = g++
CXXFLAGS = -std=c++14 -Wall

LIB_OBJS = point.o board.o player.o human_player.o computer_player.o painter.o score_store.o game_engine.o
LIB = libgame.a

TEST_OBJS = tests/test_main.o tests/test_point.o tests/test_board.o tests/test_players.o tests/test_score_store.o
TEST_EXE  = tests/run_tests.exe

all: TicTacToe

# biblioteca statica proprie: toate clasele jocului
$(LIB): $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

# executabilul legat de biblioteca proprie si de biblioteca externa SQLite
TicTacToe: main.o $(LIB)
	$(CXX) -o TicTacToe.exe main.o -L. -lgame -lsqlite3

main.o: main.cpp game_engine.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

point.o: point.cpp point.hpp
	$(CXX) $(CXXFLAGS) -c point.cpp -o point.o

board.o: board.cpp board.hpp cell.hpp point.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp -o board.o

player.o: player.cpp player.hpp
	$(CXX) $(CXXFLAGS) -c player.cpp -o player.o

human_player.o: human_player.cpp human_player.hpp player.hpp
	$(CXX) $(CXXFLAGS) -c human_player.cpp -o human_player.o

computer_player.o: computer_player.cpp computer_player.hpp player.hpp board.hpp
	$(CXX) $(CXXFLAGS) -c computer_player.cpp -o computer_player.o

painter.o: painter.cpp painter.hpp drawable.hpp
	$(CXX) $(CXXFLAGS) -c painter.cpp -o painter.o

score_store.o: score_store.cpp score_store.hpp game_result.hpp
	$(CXX) $(CXXFLAGS) -c score_store.cpp -o score_store.o

game_engine.o: game_engine.cpp game_engine.hpp
	$(CXX) $(CXXFLAGS) -c game_engine.cpp -o game_engine.o

# ---- teste unitare ----
# testele se leaga de aceeasi biblioteca libgame.a ca jocul
test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS) $(LIB)
	$(CXX) -o $(TEST_EXE) $(TEST_OBJS) -L. -lgame -lsqlite3

tests/%.o: tests/%.cpp tests/test_framework.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- documentatie (necesita doxygen) ----
docs:
	doxygen Doxyfile

clean:
	rm -f *.o *.a *.exe tests/*.o tests/*.exe tests_results.db
	rm -rf docs

.PHONY: all test docs clean
