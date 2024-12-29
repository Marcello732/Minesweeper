#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#define EASY_ROWS 9
#define EASY_COLS 9
#define EASY_MINES 10

#define MEDIUM_ROWS 16
#define MEDIUM_COLS 16
#define MEDIUM_MINES 40

#define HARD_ROWS 16
#define HARD_COLS 30
#define HARD_MINES 99

typedef struct
{
    char **grid;    // 2D array for the board
    char **visible; // 2D array for visible cells
    int rows;
    int cols;
    int mines;
} Board;

void initBoard(Board *board, int rows, int cols, int mines);
void placeMines(Board *board);
void printBoard(Board *board, int revealMines);
void freeBoard(Board *board);
void playGame(Board *board, char *name);

#endif