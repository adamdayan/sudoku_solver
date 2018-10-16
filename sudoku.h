#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* Function that checks whether all fields on a sudoku board are occupied by digits */ 
bool is_complete(char board[9][9]) ; 

/* function to check whether a digit already exists in a given column. returns boolean */
bool check_column(char digit, int column, char board[9][9]);

/* function to check whether a digit already exists in a given row. returns boolean */
bool check_row(char digit, int row, char board[9][9]);

/* function to check whether given coordinates are in bounds */
bool in_bounds(int row, int column);

/* function to check whether a move is legal; if so it will write that move to the board */ 
bool make_move(const char* position, char digit, char board[9][9]); 

/* function that writes a board array to a data file. returns true if write successful otherwise returns false */ 
bool save_board(const char* filename, char board[9][9]); 

#endif
