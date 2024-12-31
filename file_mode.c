#include "minesweeper.h"
#include <stdlib.h>
#include <stdio.h>

int loadBoardFromFile(Board *board, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: Cannot open board file '%s'.\n", filename);
        return 0;
    }

    fscanf(file, "%d %d %d", &board->rows, &board->cols, &board->mines);
    board->grid = malloc(board->rows * sizeof(char *));
    board->visible = malloc(board->rows * sizeof(char *));

    for (int i = 0; i < board->rows; i++)
    {
        board->grid[i] = malloc(board->cols * sizeof(char));
        board->visible[i] = malloc(board->cols * sizeof(char));
        for (int j = 0; j < board->cols; j++)
        {
            fscanf(file, " %c", &board->grid[i][j]);
            board->visible[i][j] = '.'; // Initialize as hidden
        }
    }

    fclose(file);
    return 1;
}

int runFileMode(const char *boardFile, const char *movesFile)
{
    Board board;
    if (!loadBoardFromFile(&board, boardFile))
    {
        return 1;
    }

    FILE *file = fopen(movesFile, "r");
    if (!file)
    {
        printf("Error: Cannot open moves file '%s'.\n", movesFile);
        return 1;
    }

    int x, y;
    int correctSteps = 0;
    int uncoveredCells = 0;
    int success = 1;
    char action;
    int multiplier = (board.rows == EASY_ROWS) ? 1 : (board.rows == MEDIUM_ROWS) ? 2
                                                                                 : 3;

    while (fscanf(file, " %c %d %d", &action, &x, &y) != EOF)
    {

        if (x < 1 || x > board.rows || y < 1 || y > board.cols)
        {
            printf("Invalid move in file: (%c %d %d)\n", action, x, y);
            success = 0;
            break;
        }

        x--;
        y--;

        if (action == 'f')
        {
            if (board.visible[x][y] == 'f')
            {
                board.visible[x][y] = '.';
            }
            else if (board.visible[x][y] == '.')
            {
                board.visible[x][y] = 'f';
                correctSteps++;
            }
        }
        else if (action == 'r')
        {
            if (board.visible[x][y] == 'f')
            {
                success = 0; // Can't reveal flagged cell
                break;
            }
            if (board.grid[x][y] == '*')
            {
                success = 0; // Hit a mine
                break;
            }
            if (board.visible[x][y] == '.')
            {
                revealConnectedCells(&board, x, y, &uncoveredCells);
                uncoveredCells++;
                correctSteps++;
            }
        }
        else
        {
            printf("Invalid action in file: %c\n", action);
            success = 0;
            break;
        }
    }

    fclose(file);

    // Display results
    printf("Correct Steps: %d\n", correctSteps);
    printf("Final Score: %d\n", uncoveredCells * multiplier);
    printf("Game Result: %d\n", success);

    return 0;
}