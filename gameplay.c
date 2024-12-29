#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"

void revealConnectedCells(Board *board, int x, int y)
{
    if (x < 0 || x >= board->rows || y < 0 || y >= board->cols)
        return;
    if (board->visible[x][y] == '1' || board->visible[x][y] == 'f')
        return;

    board->visible[x][y] = '1'; // Mark cell as revealed

    if (board->grid[x][y] == '0')
    { // If no bombs around, recursively reveal neighbors
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx != 0 || dy != 0)
                { // Avoid revealing the current cell again
                    revealConnectedCells(board, x + dx, y + dy);
                }
            }
        }
    }
}

void playGame(Board *board)
{
    int x, y;
    char action;
    int attempts = 0;
    int uncoveredCells = 0;
    int multiplier = (board->rows == EASY_ROWS) ? 1 : (board->rows == MEDIUM_ROWS) ? 2
                                                                                   : 3;

    while (1)
    {
        printBoard(board, 0);
        printf("Attempts: %d | Score: %d\n\n", attempts, uncoveredCells * multiplier);

        printf("Enter your move (f x y to flag, r x y to reveal): ");
        scanf(" %c %d %d", &action, &x, &y);

        if (x < 0 || x >= board->rows || y < 0 || y >= board->cols)
        {
            printf("Invalid coordinates! Try again.\n");
            continue;
        }

        attempts++;

        if (action == 'f')
        { // Place or remove flag
            if (board->visible[x][y] == 'f')
            {
                board->visible[x][y] = '.'; // Remove flag
                printf("Flag removed from (%d, %d)\n\n", x, y);
            }
            else if (board->visible[x][y] == '.')
            {
                board->visible[x][y] = 'f'; // Place flag
                printf("Flag placed on (%d, %d)\n\n", x, y);
            }
            else
            {
                printf("Cell already uncovered! Cannot place flag.\n");
            }
        }
        else if (action == 'r')
        { // Reveal cell
            if (board->visible[x][y] == 'f')
            {
                printf("Cannot reveal a flagged cell! Remove the flag first.\n");
                continue;
            }

            if (board->grid[x][y] == '*')
            {
                printf("Game Over! You hit a mine at (%d, %d).\n", x, y);
                printBoard(board, 1);
                printf("Final Score: %d\n", uncoveredCells * multiplier);
                break;
            }

            if (board->visible[x][y] == '.')
            {
                revealConnectedCells(board, x, y); // Reveal connected cells
                uncoveredCells++;                  // Increment uncovered cells counter
            }

            // Check win condition
            int hiddenCells = 0;
            for (int i = 0; i < board->rows; i++)
            {
                for (int j = 0; j < board->cols; j++)
                {
                    if (board->visible[i][j] == '.' || board->visible[i][j] == 'f')
                    {
                        hiddenCells++;
                    }
                }
            }
            if (hiddenCells == board->mines)
            {
                printf("Congratulations! You've cleared the board.\n");
                printBoard(board, 1);
                printf("Final Score: %d\n", uncoveredCells * multiplier);
                break;
            }
        }
        else
        {
            printf("Invalid action! Use 'f' or 'r'.\n");
        }
    }
}