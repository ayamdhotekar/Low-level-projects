CC = gcc
CFLAGS = -Wall -O2

SRC = src/main.c src/kmeans.c
OUT = kmeans

all:
	$(CC) $(CFLAGS) $(SRC) -lm -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)
