#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

void saveScore(char *name, int score, char *level)
{
    FILE *file = fopen("leaderboard.txt", "a");
    if (file == NULL)
    {
        printf("[!] Błąd otwierania pliku!\n");
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
        printf("[!] Błąd otwierania pliku!\n");
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

    printf("\nTop 5 wynikow:\n");
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

void endGame(Board *board, int uncoveredCells, int multiplier, char *level)
{
    char name[100];
    printBoard(board, 1);
    printf("Wynik: %d\n", uncoveredCells * multiplier);
    printf("Twoje imie: ");
    scanf("%s", name);
    saveScore(name, uncoveredCells * multiplier, level);
    getTopFiveScores();
}

void playGame(Board *board)
{
    int x, y;
    char action;
    int attempts = 0;
    int uncoveredCells = 0;
    int multiplier = (board->rows == EASY_ROWS) ? 1 : (board->rows == MEDIUM_ROWS) ? 2
                                                  : (board->rows == HARD_ROWS)     ? 3
                                                                                   : 2;
    char *level = (board->rows == EASY_ROWS) ? "Easy" : (board->rows == MEDIUM_ROWS) ? "Medium"
                                                    : (board->rows == HARD_ROWS)     ? "Hard"
                                                                                     : "Custom";
    int isFirstMove = 1;

    while (1)
    {
        printBoard(board, 0);
        printf("Ruchy: %d | Wynik: %d\n", attempts, uncoveredCells * multiplier);

        printf("\nPodaj ruch (f x y, aby oznaczyc flage, r x y, aby odkryc): ");
        scanf(" %c %d %d", &action, &x, &y);

        if (x < 1 || x > board->rows || y < 1 || y > board->cols)
        {

            printf("Niepoprawne wspolrzedne! Sprobuj ponownie.\n");
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

                printf("Flaga usunieta z (%d, %d)\n\n", x, y);
            }
            else if (board->visible[x][y] == '.')
            {
                board->visible[x][y] = 'f'; // Place flag

                printf("Flaga umieszczona na (%d, %d)\n\n", x, y);
            }
            else
            {

                printf("Miejsce jest juz odkryte! Nie mozna umiescic flagi.\n");
            }
        }
        else if (action == 'r')
        { // Reveal cell
            if (board->visible[x][y] == 'f')
            {
                printf("Nie mozna odkryc oznaczonej flaga komorki! Najpierw usun flage.\n");
                continue;
            }

            if (isFirstMove)
            {
                placeMines(board, x, y); // Place mines after the first move
                isFirstMove = 0;
            }

            if (board->grid[x][y] == '*')
            {
                printf("Koniec gry! Trafiles na mine na (%d, %d).\n", x + 1, y + 1);
                endGame(board, uncoveredCells, multiplier, level);
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
                printf("Gratulacje! Odkryles wszystkie komorki.\n");
                endGame(board, uncoveredCells, multiplier, level);
                break;
            }
        }
        else
        {
            printf("Niepoprawny ruch! Uzyj 'f' lub 'r'.\n");
        }
    }
}