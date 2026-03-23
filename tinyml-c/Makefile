CC = gcc
CFLAGS = -Wall -O2

SRC = src/main.c src/linear_regression.c
OUT = tinyml

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
