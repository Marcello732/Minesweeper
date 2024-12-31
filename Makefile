main: build
	./minesweeper

build: main.c board.c gameplay.c file_mode.c
	$(CC) $^ -o minesweeper 

test: 
	./minesweeper