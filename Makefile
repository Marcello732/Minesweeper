main: build run_tests
	./minesweeper

build: main.c board.c gameplay.c file_mode.c
	$(CC) $^ -o minesweeper 

clean:
	rm -f minesweeper

test: tests.c board.c gameplay.c file_mode.c
	$(CC) $^ -o tests -w

run_tests: test
	./tests