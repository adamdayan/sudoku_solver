sudoku: sudoku.o main.o
	g++ -std=c++14 sudoku.o main.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -std=c++14 -Wall -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	  g++ -std=c++14 -Wall -g -c sudoku.cpp

clean:
	rm -f *.o sudoku
