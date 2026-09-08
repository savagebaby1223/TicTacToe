all: TicTacToe

TicTacToe: point.o cell.o player.o board.o game_engine.o painter.o listener.o main.o
	g++ -o TicTacToe.exe point.o cell.o player.o board.o game_engine.o painter.o listener.o main.o

point.o:
	g++ point.cpp -o point.o -c

cell.o:
	g++ cell.cpp -o cell.o -c

player.o:
	g++ player.cpp -o player.o -c

board.o:
	g++ board.cpp -o board.o -c

game_engine.o:
	g++ game_engine.cpp -o game_engine.o -c

painter.o:
	g++ painter.cpp -o painter.o -c

listener.o:
	g++ listener.cpp -o listener.o -c

main.o:
	g++ main.cpp -o main.o -c

clean:
	rm -f *.o *.exe