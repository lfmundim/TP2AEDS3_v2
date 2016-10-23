CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -Werror -std=c99 -pedantic
OBJ = main.o dijkstra.o vinicius.o map.o graph.o
DEPS = dijkstra.h vinicius.h map.h graph.h
VFLAGS = --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./exec < input > output && cat output
TIMED_RUN = time ./exec < input
COMPARE = diff output expected

all: exec

exec: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o exec

valgrind:
	valgrind $(VFLAGS) $(EXEC)
run:
	$(EXEC)
timed:
	$(TIMED_RUN)

compare:
	$(COMPARE)
