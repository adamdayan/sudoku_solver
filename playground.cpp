#include <iostream>
#include <cstdio>
#include <ncurses.h>
#include"sudoku.h"

int function_call_cnt = 0;
int guess_cnt = 0; 

using namespace std;

int main()
{
  char board[9][9];

  initscr(); 
  
  load_board("mystery3.dat", board);
  display_board(board);

  if (solve_board(board))
    {
      printw("board solved\n");
    }
  else
    {
      printw("board not solved\n");
    }

  refresh();
  getch();

  endwin(); 
  return 0;
}


