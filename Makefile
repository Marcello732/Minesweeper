main: build
	./minesweeper

build: main.c board.c gameplay.c
	$(CC) $^ -o minesweeper 

test: 
	./minesweeper