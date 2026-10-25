all: TicTacToe

TicTacToe: point.o board.o player.o human_player.o computer_player.o painter.o game_engine.o main.o
	g++ -o TicTacToe.exe point.o board.o player.o human_player.o computer_player.o painter.o game_engine.o main.o

point.o:
	g++ point.cpp -o point.o -c -std=c++14

board.o:
	g++ board.cpp -o board.o -c -std=c++14

player.o:
	g++ player.cpp -o player.o -c -std=c++14

human_player.o:
	g++ human_player.cpp -o human_player.o -c -std=c++14

computer_player.o:
	g++ computer_player.cpp -o computer_player.o -c -std=c++14

painter.o:
	g++ painter.cpp -o painter.o -c -std=c++14

game_engine.o:
	g++ game_engine.cpp -o game_engine.o -c -std=c++14

main.o:
	g++ main.cpp -o main.o -c -std=c++14

clean:
	rm -f *.o *.exe
