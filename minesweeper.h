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
    char **grid;     // 2D array for the board
    short **visible; // 2D array for visible cells
    int rows;
    int cols;
    int mines;
} Board;

void initBoard(Board *board, int rows, int cols, int mines);
void placeMines(Board *board, int safeX, int safeY);
void printBoard(Board *board, int revealMines);
void freeBoard(Board *board);
void playGame(Board *board);
void endGame(Board *board, int uncoveredCells, int multiplier, char *level);
void revealConnectedCells(Board *board, int x, int y, int *uncoveredCells);
void saveScore(char *name, int score, char *level);
void getTopFiveScores();
int loadBoardFromFile(Board *board, const char *filename);
int runFileMode(const char *boardFile, const char *movesFile);
#endif