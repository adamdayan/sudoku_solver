#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/* function to check whether a sudoku board has all positions occupied with digits */
bool is_complete(char board[9][9])
{
  for (int row = 0; row < 8; row++)
    {
      for (int col = 0; col < 8; col++)
	{
	  if ((board[row][col] > 57 || board[row][col] < 48))
	    return false;
	}
    }
  return true;
}

/* function to check whether a digit already exists in a given column. returns boolean */
bool check_column(char digit, int column, char board[9][9])
{
  for (int row = 0; row < 9; row++)
    {
      if (board[row][column] == digit)
	return false;
    }

  return true;
}

/* function to check whether a digit already exists in a given row. returns boolean */
bool check_row(char digit, int row, char board[9][9])
{
  for (int column = 0; column < 9; column++)
    {
      if (board[row][column] == digit)
	return false;
    }

  return true;
}

/* function to check whether given coordinates are in bounds */
bool in_bounds(int row, int column)
{
  if ((row >= 0 && row < 9) && (column >= 0 && column < 9))
    return true;
  else
    return false;
}

/* function to check whether a move is legal; if so it will write that move to the board */ 
bool make_move(const char* position, char digit, char board[9][9])
{
  int row, col;

  row = position[0] - 'A';
  col = position[1] - 49; //-48 changes char to digit; -1 changes it to an index

  if (check_column(digit, col, board) && check_row(digit, row, board) && in_bounds(row, col))
    {
      board[row][col] = digit;
      return true;
    }
  else
    return false;
}
  
/* function that writes a board array to a data file. returns true if write succesful otherwise returns false */
bool save_board(const char* filename, char board[9][9])
{
  ofstream ostream;

  ostream.open(filename);

  for (int row = 0; row < 9; row++)
    {
      for (int col = 0; col < 9; col++)
	{
	  if (ostream.is_open())
	    ostream << board[row][col];
	  else
	    return false;
	}
      ostream << endl; 
    }

  ostream.close(); 
  
  return true;
}
