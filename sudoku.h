#ifndef SUDOKU_H
#define SUDOKU_H

extern int function_call_cnt; 

/* function to load board. default is to print statements on status of read but this can be specified */ 
void load_board(const char* filename, char board[9][9], bool = true);

void display_board(const char board[9][9]); 

/* Function that checks whether all fields on a sudoku board are occupied by digits */ 
bool is_complete(char board[9][9]) ; 

/* function to check whether a digit already exists in a given column. returns boolean */
bool check_column(char digit, int column, char board[9][9]);

/* function to check whether a digit already exists in a given row. returns boolean */
bool check_row(char digit, int row, char board[9][9]);

/* function to check whether a digit already exists in a square frame */
bool check_frame(char digit, int row, int col, char board[9][9]); 

/* function to check whether given coordinates are in bounds */
bool in_bounds(int row, int column);

/* function to check whether a move is legal; if so it will write that move to the board */ 
bool make_move(const char* position, char digit, char board[9][9]); 

/* function that writes a board array to a data file. returns true if write successful otherwise returns false */ 
bool save_board(const char* filename, char board[9][9]); 

/* function that calculates the number of peers a cell has on its row. a peer is a cell that relates to the cell in question by occupying the same row, col or frame */
int row_peers(char board[9][9], int cell_row, int cell_col);

/* function that calculates the number of peers a cell has on its column */
int col_peers(char board[9][9], int cell_row, int cell_col);

/* function that calculates the number of peers a cell has in its frame */
int frame_peers(char board[9][9], int cell_row, int cell_col);

/* function that finds the empty cell on the board that currently has the most peers */ 
void most_peers(char board[9][9], int& row, int& col); 

/* helper function for solve_board that fills cells where there is only one possible move */ 
void deductive_presolve(char board[9][9]); 

/* improved function to solve board. fundamentally based on a backtrack algorithim but combines this with an optimisation that recursively calls the function on the cell with the most peers */ 
bool solve_board(char board[9][9]);


#endif
