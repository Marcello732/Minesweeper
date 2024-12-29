#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"

void initBoard(Board *board, int rows, int cols, int mines)
{
    board->rows = rows;
    board->cols = cols;
    board->mines = mines;

    board->grid = malloc(rows * sizeof(char *));
    board->visible = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++)
    {
        board->grid[i] = malloc(cols * sizeof(char));
        board->visible[i] = malloc(cols * sizeof(char));
        for (int j = 0; j < cols; j++)
        {
            board->grid[i][j] = '0';    // Initialize to 0
            board->visible[i][j] = '.'; // Hidden state
        }
    }

    placeMines(board);
}

void placeMines(Board *board)
{
    srand(time(NULL));
    int placed = 0;

    // Place mines
    while (placed < board->mines)
    {
        int r = rand() % board->rows;
        int c = rand() % board->cols;

        if (board->grid[r][c] != '*')
        {
            board->grid[r][c] = '*';
            placed++;

            // Update surrounding cells
            for (int dr = -1; dr <= 1; dr++)
            {
                for (int dc = -1; dc <= 1; dc++)
                {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < board->rows && nc >= 0 && nc < board->cols && board->grid[nr][nc] != '*')
                    {
                        board->grid[nr][nc]++;
                    }
                }
            }
        }
    }
}

void printBoard(Board *board, int revealMines)
{
    printf("  | "); // Top border numbering
    for (int j = 0; j < board->cols; j++)
    {
        printf("%d ", j + 1);
    }
    printf("\n");
    printf("--");
    printf("|");
    for (int j = 0; j < board->cols; j++)
    {
        printf("--");
    }
    printf("\n");

    for (int i = 0; i < board->rows; i++)
    {
        printf("%d | ", i + 1); // Row numbering
        for (int j = 0; j < board->cols; j++)
        {
            if (revealMines)
            {
                printf("%c ", board->grid[i][j]);
            }
            else if (board->visible[i][j] == 'f')
            {
                printf("F "); // Display flag
            }
            else if (board->visible[i][j] == '1')
            {
                printf("%c ", board->grid[i][j]); // Display number or mine
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
}

void freeBoard(Board *board)
{
    for (int i = 0; i < board->rows; i++)
    {
        free(board->grid[i]);
        free(board->visible[i]);
    }
    free(board->grid);
    free(board->visible);
}