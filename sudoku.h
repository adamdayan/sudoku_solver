#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* Function that checks whether all fields on a sudoku board are occupied by digits */ 
bool is_complete(char board[9][9]) ; 

#endif
