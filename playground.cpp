#include <iostream>
#include <cstdio>
#include"sudoku.h"

int function_call_cnt = 0;
int guess_cnt = 0; 

using namespace std;

int main()
{
  char board[9][9];

  load_board("mystery3.dat", board);
  display_board(board);

  if (solve_board(board))
    cout << "board solved" << endl;
  else
    cout << "board not solved" << endl;

  cout << function_call_cnt << " function calls\n"
       << guess_cnt << " guesses\n"; 
  
  display_board(board); 
  
  return 0;
}


