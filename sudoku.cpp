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
void load_board(const char* filename, char board[9][9], bool communicate) {

  if (communicate)
    cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in && communicate)
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

  if (communicate)
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
  for (int row = 0; row < 9; row++)
    {
      for (int col = 0; col < 9; col++)
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

/* function to check whether a digit already exists in a square frame */
bool check_frame(char digit, int row, int col, char board[9][9])
{
  int row_lower_bound = (row / 3) * 3;
  int row_upper_bound = row_lower_bound + 2;
  int col_lower_bound = (col / 3) * 3;
  int col_upper_bound = col_lower_bound + 2;

  for (int row_count = row_lower_bound; row_count <= row_upper_bound; row_count++)
    {
      for (int col_count = col_lower_bound; col_count <= col_upper_bound; col_count++)
	{
	  if (digit == board[row_count][col_count])
	    return false;
	}
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

/* overloaded function to check whether a move is legal using position-to-write-to and digit-to-write; if so it will write that move to the board */ 
bool make_move(const char* position, char digit, char board[9][9])
{
  int row, col;

  row = position[0] - 'A';
  col = position[1] - 49; //-48 changes char to digit; -1 changes it to an index

  if (check_column(digit, col, board)
      && check_row(digit, row, board)
      && in_bounds(row, col)
      && check_frame(digit, row, col, board))
    {
      board[row][col] = digit;
      return true;
    }
  else
    return false;
}

/* overloaded function to check whether a move is legal using indicies-to-write-to and digit-to-write; if so it will write that move to the board */ 
bool make_move(int row, int col, int value, char board[9][9])
{
  char digit = static_cast<char>(value) + '0'; 
  if (check_column(digit, col, board)
      && check_row(digit, row, board)
      && in_bounds(row, col)
      && check_frame(digit, row, col, board))
    {
      board[row][col] = digit;
      return true;
    }
  else
    return false;
}

/* function that checks whether a saved board object is the same as a board object in program memory */bool save_check(const char* filename, char board[9][9])
{
  char saved_board[9][9];

  load_board(filename, saved_board, false); 
  for (int row = 0; row < 9; row++)
    {
      for (int col = 0; col < 9; col++)
	{
	  if (!(board[row][col] == saved_board[row][col]))
	    return false;
	}
    }

  return true;
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

  if (save_check(filename, board))
    return true;
  else
    return false; 
}

/* function that calculates the number of peers a cell has on its row. a peer is a cell that relates to the cell in question by occupying the same row, col or frame */
int row_peers(char board[9][9], int cell_row, int cell_col)
{
  int cnt = 0;

  for (int col = 0; col < 9; col++)
    {
      if (board[cell_row][col] != '.' && col != cell_col)
	cnt++;
    }

  return cnt;
}

/* function that calculates the number of peers a cell has on its column */
int col_peers(char board[9][9], int cell_row, int cell_col)
{
  int cnt = 0;

  for (int row = 0; row < 9; row++)
    {
      if (board[row][cell_col] != '.' && row != cell_row)
	cnt++;
    }

  return cnt;
}

/* function that calculates the number of peers a cell has in its frame */
int frame_peers(char board[9][9], int cell_row, int cell_col)
{
  int row_lower_bound = (cell_row / 3) * 3;
  int row_upper_bound = row_lower_bound + 2;
  int col_lower_bound = (cell_col / 3) * 3;
  int col_upper_bound = col_lower_bound + 2;
  int cnt = 0; 
  
  for (int row_iterator = row_lower_bound; row_iterator <= row_upper_bound; row_iterator++)
    {
      for (int col_iterator = col_lower_bound; col_iterator <= col_upper_bound; col_iterator++)
	{
	  if (board[row_iterator][col_iterator] != '.' && row_iterator != cell_row && col_iterator != cell_col)
	    cnt++; 
	}
    }

  return cnt;
}

/* function that finds the empty cell on the board that currently has the most peers */ 
void most_peers(char board[9][9], int& row, int& col)
{
  //char peer_board[9][9];
  int max_peers = 0, max_peers_row = 0, max_peers_col = 0, peers = 0;

  for (int row_iterator = 0; row_iterator < 9; row_iterator++)
    {
      for (int col_iterator = 0; col_iterator < 9; col_iterator++)
	{
	  if (board[row_iterator][col_iterator] == '.')
	    {
	      peers = row_peers(board, row_iterator, col_iterator) + col_peers(board, row_iterator, col_iterator);
	      if (peers > max_peers)
		{
		  max_peers = peers;
		  max_peers_row = row_iterator;
		  max_peers_col = col_iterator;
		}
	    }
	}
    }

  row = max_peers_row;
  col = max_peers_col;
}


/* function that solves the sudoku board using a backtracking approach. returns true if board is soluble, false otherwise */
bool solve_board(char board[9][9])
{
  function_call_cnt++; 
  for (int row = 0; row < 9; row++)
    {
      for (int col = 0; col < 9; col++)
	{ 
	  if (board[row][col] == '.')
	    {
	      for (int working_num = 1; working_num <= 9; working_num++)
		{
		  bool move_result = make_move(row, col, working_num, board); 
		  
		  if (is_complete(board))
		    { 
		      return true;
		    }
		  else if (move_result)
		    {
		      if (!solve_board(board) && working_num == 9)
			{
			  board[row][col] = '.';
			  return false; 
			}
		      else if (is_complete(board))
			return true; 
		    }
		  else if (working_num < 9)
		    continue;
		  else
		    {
		      board[row][col] = '.';
		      return false; 
		    }
		}
	    }
	}
    }
}

bool solve_board2(char board[9][9])
{
  int row, col; 
  
  function_call_cnt++; 
  while (!is_complete(board))
    {
      most_peers(board, row, col); 
      
      for (int working_num = 1; working_num <= 9; working_num++)
	{
	  bool move_result = make_move(row, col, working_num, board); 
		  
	  if (is_complete(board))
	    { 
	      return true;
	    }
	  else if (move_result)
	    {
	      if (!solve_board(board) && working_num == 9)
		{
		  board[row][col] = '.';
		  return false; 
		}
	      else if (is_complete(board))
		return true; 
	    }
	  else if (working_num < 9)
	    continue;
	  else
	    {
	      board[row][col] = '.';
	      return false; 
	    }
	}
    }
}
