# Sprawozdanie

Jest to sprawozdanie do wykonanej gry Minesweeper w języku C.

## Podręcznik użytkowania

Zasady gry są identyczne jak w 'normalnym' saperze. Dostajemy planszę z zakrytymi polami i naszym zadaniem jest znalezienie wszystkich min.

Program uruchamiamy używajac pliku Makefile, czyli komendą `make` (buduje, przeprowadza testy i odpala aplikację w domyślnym trybie) lub po prostu `./minesweeper`.

Możemy rownież odpalić same testy jednostkowe komendą `make run_tests`.

### Dostępne opcje do komendy `./minesweeper`:

- `-h`: wyświetla pomoc
- `-f`: ustawia tryb wczytywania z pliku
- `-m <moves_file>`: działa razem z `-f` i wczytuje plik z ruchami
- `-b <board_file>`: działa razem z `-f` i wczytuje plik z planszą

Przykład komendy z wczytywaniem z pliku: `./minesweeper -f -b boards/board.txt -m moves/moves.txt`.

Format pliku <moves_file>:

```r 1 1
r 1 2
f 6 6
r 3 3
```

Format pliku <board_file>:

```
5 5 5 (liczba kolumn, wierszy i min)
. . * . .
. 1 2 1 .
. 1 * 1 .
. 1 2 1 .
. . . . .
```

## Implementacja

### Podział programu

- `main.c`: zawiera funkcję `main` oraz obsługę argumentów programu
- `minesweeper.h`: zawiera definicje wszystkich funkcji programu i struktury Board
- `board.c`: implemendatcja funckji do zarządzania planszą gry
- `gameplay.c`: implementacja funcji logiki gry
- `file_mode.c`: implementacja funkcji do obsługi trybu gry z pliku
- `leaderboard.txt`: przechowuje wyniki graczy

### Kluczowe funkcje

- `void initBoard(Board *board, int rows, int cols, int mines);`: inicjalizuje planszę do gry
- `void placeMines(Board *board, int safeX, int safeY);`: umiejscawia miny w losowy sposób z zastrzezeniem ze w pierwszym ruchu gracz nie trafi w minę
- `void playGame(Board *board);`: odpowiada za rozgrywkę (odczytywanie ruchów i odpowiednie akcje)
- `void revealConnectedCells(Board *board, int x, int y, int *uncoveredCells);`: odpowiada za odkrywanie kolejnych połaczonych pól, które są wolne od min
- `int loadBoardFromFile(Board *board, const char *filename);`: odpowiada za wczytywanie planszy z pliku
- `int runFileMode(const char *boardFile, const char *movesFile);`: odpowiednik funcji `playGame()` tylko dla trybu gry z pliku

### Mniej wazne funkcje

- `void endGame(Board *board, int uncoveredCells, int multiplier, char *level);`:
- `void printBoard(Board *board, int revealMines);`: wyświetla planszę
- `void freeBoard(Board *board);`: zwalnia pamięć
- `void saveScore(char *name, int score, char *level);`: zapisuje wynik
- `void getTopFiveScores();`: zwraca 5 najlepszych wyników z pliku leaderboard.txt

### Ważniejsze struktury

- struktura reprezentująca planszę:

```
  typedef struct{
    char **grid; //tablica dla planszy
    short **visible; //tablica dla odkrytych komórek
    int rows; // ilość wierszy
    int cols; // ilość kolumn
    int mines; // ilość min
  } Board;
```

### Testy

Testy sprawdzają poprawność tworzenia planszy i odkrywania pól.

Wszystkie testy zakończyły się pomyślnie.

## Podział pracy w zespole

Pracowałem samemu, w jednoosobowym zespole.

## Podsumowanie

Wszystkie funkcjonalności udało się zaimplementować. Największe trudności sprawiła implementacja funkcji `revealConnectedCells`, która wymagała dokładnego przemyślenia logiki odkrywania sąsiednich komórek i `placeMines()`, by użytkownik nie natrafił na mine przy pierwszym ruchu.

Wnioski: Projekt pozwolił na praktyczne zastosowanie wiedzy z zakresu programowania w C i 'pokręcenia głową'.
