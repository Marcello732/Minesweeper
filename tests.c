#include <stdio.h>
#include <string.h>
#include "minesweeper.h"

int test_reveal_connected_cells()
{
    Board board1 = {
        .rows = 5,
        .cols = 5,
        .mines = 2,
        .grid = (char *[]){
            (char[]){'0', '1', '*', '1', '0'},
            (char[]){'0', '1', '2', '1', '0'},
            (char[]){'0', '1', '*', '1', '0'},
            (char[]){'0', '1', '2', '1', '0'},
            (char[]){'0', '0', '0', '0', '0'},
        },
        .visible = (short *[]){
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
        },
    };

    Board board2 = {
        .rows = 5,
        .cols = 5,
        .mines = 2,
        .grid = (char *[]){
            (char[]){'0', '1', '*', '*', '1'},
            (char[]){'0', '1', '2', '2', '1'},
            (char[]){'0', '1', '*', '1', '0'},
            (char[]){'1', '1', '2', '1', '0'},
            (char[]){'1', '*', '1', '0', '0'},
        },
        .visible = (short *[]){
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
            (short[]){'.', '.', '.', '.', '.'},
        },
    };

    int uncoveredCells = 0;
    revealConnectedCells(&board1, 0, 0, &uncoveredCells);
    revealConnectedCells(&board2, 0, 0, &uncoveredCells);

    if (strcmp(board1.visible[2], (short[]){'1', '.', '.', '.', '.'}) != 0)
    {
        printf("test_reveal_connected_cells [board1] FAILED\n");
        return 1;
    }

    if (strcmp(board2.visible[2], (short[]){'1', '.', '.', '.', '.'}) != 0)
    {
        printf("test_reveal_connected_cells [board2] FAILED\n");
        return 1;
    }

    printf("test_reveal_connected_cells PASSED\n");
    return 0;
}

int main()
{
    int failed = 0;
    failed += test_reveal_connected_cells();

    if (failed == 0)
    {
        printf("Wszystkie testy zaliczone!\n");
    }
    else
    {
        printf("%d testów nie zaliczonych.\n", failed);
    }

    return failed;
}