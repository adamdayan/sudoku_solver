sudoku: sudoku.o tests.o
	g++ sudoku.o tests.o -o sudoku

tests.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp -o tests.o

sudoku.o: sudoku.cpp sudoku.h
	  g++ -Wall -g -c sudoku.cpp -o sudoku.o

clean:
	rm -f *.o sudoku
