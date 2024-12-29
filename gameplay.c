#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

void saveScore(char *name, int score, char *level)
{
    FILE *file = fopen("leaderboard.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "%s %d %s\n", name, score, level);
    fclose(file);
}

void getTopFiveScores()
{
    FILE *file = fopen("leaderboard.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    char name[100];
    int score;
    char level[10];
    int scores[5] = {0};
    char names[5][100];
    char levels[5][10];

    while (fscanf(file, "%s %d %s", name, &score, level) != EOF)
    {
        for (int i = 0; i < 5; i++)
        {
            if (score > scores[i])
            {
                for (int j = 4; j > i; j--)
                {
                    scores[j] = scores[j - 1];
                    strcpy(names[j], names[j - 1]);
                    strcpy(levels[j], levels[j - 1]);
                }
                scores[i] = score;
                strcpy(names[i], name);
                strcpy(levels[i], level);
                break;
            }
        }
    }

    printf("\nTop 5 Scores:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d. %s: %d %s\n", i + 1, names[i], scores[i], levels[i]);
    }

    fclose(file);
}

void revealConnectedCells(Board *board, int x, int y, int *uncoveredCells)
{
    if (x < 0 || x >= board->rows || y < 0 || y >= board->cols)
        return;
    if (board->visible[x][y] == '1' || board->visible[x][y] == 'f')
        return;

    board->visible[x][y] = '1'; // Mark cell as revealed

    if (board->grid[x][y] == '0')
    { // If no bombs around, recursively reveal neighbors
        (*uncoveredCells)++;
        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                if (dx != 0 || dy != 0)
                { // Avoid revealing the current cell again
                    revealConnectedCells(board, x + dx, y + dy, uncoveredCells);
                }
            }
        }
    }
}

void playGame(Board *board, char *name)
{
    int x, y;
    char action;
    int attempts = 0;
    int uncoveredCells = 0;
    int multiplier = (board->rows == EASY_ROWS) ? 1 : (board->rows == MEDIUM_ROWS) ? 2
                                                                                   : 3;
    char *level = (board->rows == EASY_ROWS) ? "Easy" : (board->rows == MEDIUM_ROWS) ? "Medium"
                                                                                     : "Hard";

    while (1)
    {
        printBoard(board, 0);
        printf("Attempts: %d | Score: %d\n\n", attempts, uncoveredCells * multiplier);

        printf("\nEnter your move (f x y to flag, r x y to reveal): ");
        scanf(" %c %d %d", &action, &x, &y);

        if (x < 0 || x >= board->rows || y < 0 || y >= board->cols)
        {
            printf("Invalid coordinates! Try again.\n");
            continue;
        }

        attempts++;
        x--;
        y--;

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
                printf("Game Over! You hit a mine at (%d, %d).\n", x + 1, y + 1);
                printBoard(board, 1);
                printf("Final Score: %d\n", uncoveredCells * multiplier);
                saveScore(name, uncoveredCells * multiplier, level);
                getTopFiveScores();
                break;
            }

            if (board->visible[x][y] == '.')
            {
                revealConnectedCells(board, x, y, &uncoveredCells); // Reveal connected cells
                uncoveredCells++;                                   // Increment uncovered cells counter
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
                saveScore(name, uncoveredCells * multiplier, level);
                getTopFiveScores();
                break;
            }
        }
        else
        {
            printf("Invalid action! Use 'f' or 'r'.\n");
        }
    }
}