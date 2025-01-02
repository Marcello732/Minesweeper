#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"

int playInteractiveGame()
{
    int choice;
    Board board;
    int rows, cols, mines;

    printf("Welcome to Minesweeper!\n");
    printf("\nSelect difficulty level:\n");
    printf("1. Easy (9x9, 10 mines)\n");
    printf("2. Medium (16x16, 40 mines)\n");
    printf("3. Hard (16x30, 99 mines)\n");
    printf("4. Custom level (choose your own dimensions)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        initBoard(&board, EASY_ROWS, EASY_COLS, EASY_MINES);
        break;
    case 2:
        initBoard(&board, MEDIUM_ROWS, MEDIUM_COLS, MEDIUM_MINES);
        break;
    case 3:
        initBoard(&board, HARD_ROWS, HARD_COLS, HARD_MINES);
        break;
    case 4:
        printf("Enter number of rows, columns, and mines: ");
        scanf("%d %d %d", &rows, &cols, &mines);
        initBoard(&board, rows, cols, mines);
        break;
    default:
        printf("[!] Invalid choice!\n");
        return 1;
    }

    playGame(&board);
    freeBoard(&board);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "-f") == 0)
    {
        if (argc < 4)
        {
            printf("Usage: %s -f <board_file> <moves_file>\n", argv[0]);
            return 1;
        }

        const char *boardFile = argv[2];
        const char *movesFile = argv[3];
        return runFileMode(boardFile, movesFile);
    }

    playInteractiveGame();
    return 0;
}