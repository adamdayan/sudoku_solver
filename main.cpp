#include <iostream>
#include <cstdio>
#include <chrono>
#include "sudoku.h"

using namespace std; 
using namespace std::chrono;

int function_call_cnt = 0 ; 

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============" << endl << endl;

  cout << "Calling load_board():" << endl;
  load_board("easy.dat", board);

  cout << endl << "Displaying Sudoku board with display_board():" << endl;
  display_board(board);
  cout << "Done!" << endl << endl;

  cout << "=================== Question 1 ===================" << endl << endl;

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
    cout << "NOT ";
  cout << "complete." << endl << endl;

  cout << "=================== Question 2 ===================" << endl << endl;

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) 
    cout << "NOT ";
  cout << "a valid move. The board is:" << endl;
  display_board(board);

	// write more tests

  cout << "=================== Question 3 ===================" << endl << endl;

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board))
    cout << "Save board to 'easy-copy.dat' successful." << endl;
  else
    cout << "Save board failed." << endl;
  cout << endl;

  cout << "=================== Question 4 ===================" << endl << endl;

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:" << endl;
    display_board(board);
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

	// write more tests

  cout << "=================== Question 5 ===================" << endl << endl;

  
  function_call_cnt = 0;
  load_board("mystery1.dat", board); 

  auto start = high_resolution_clock::now(); 
  
  if (solve_board2(board)) {
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "The 'mystery1' board has a solution:" << endl;
    display_board(board);
    cout << "Function calls required: " << function_call_cnt << endl
	 << "Microseconds required: " << duration.count() << endl; 
  } else
    cout << "A solution cannot be found." << endl;
  cout << endl;

  function_call_cnt = 0;
  load_board("mystery2.dat", board);

  start = high_resolution_clock::now(); 
  
  if (solve_board2(board)) {
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "The 'mystery2' board has a solution:" << endl;
    display_board(board);
    cout << "Function calls required: " << function_call_cnt << endl
	 << "Microseconds required: " << duration.count() << endl;
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;

  function_call_cnt = 0;
  load_board("mystery3.dat", board);

  start = high_resolution_clock::now(); 
  
  if (solve_board2(board)) {
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "The 'mystery3' board has a solution:" << endl;
    display_board(board);

    
    cout << "Function calls required: " << function_call_cnt << endl
	 << "Microseconds required: " << duration.count() << endl;
  } else 
    cout << "A solution cannot be found." << endl;
  cout << endl;
	// write more tests

  return 0;
}
