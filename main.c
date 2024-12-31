#include <stdio.h>
#include "minesweeper.h"

int main()
{
    int choice;
    char name[100];
    Board board;
    int rows, cols, mines;

    printf("Welcome to Minesweeper!\n");
    printf("Your name: ");
    scanf("%s", name);
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

    playGame(&board, name);
    freeBoard(&board);
    return 0;
}