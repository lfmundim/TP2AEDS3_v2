CC = gcc
CFLAGS = -g -O0 -Wall -Wextra -std=c99 -pedantic
OBJ = main.o dijkstra.o vinicius.o map.o graph.o
DEPS = dijkstra.h vinicius.h map.h graph.h
VFLAGS = --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes
EXEC = ./exec < toys/in5
TIMED_RUN = time ./exec < input
COMPARE = diff output expected
TEST = ./exec < toys/in1 && cat toys/out1 && ./exec < toys/in2 && cat toys/out2 && ./exec < toys/in3 && cat toys/out3 && ./exec < toys/in4 && cat toys/out4 && ./exec < toys/in5 && cat toys/out5 && ./exec < toys/in6 && cat toys/out6 && ./exec < toys/in7 && cat toys/out7 && ./exec < toys/in8 && cat toys/out8 && ./exec < toys/in9 && cat toys/out9 && ./exec < toys/in10 && cat toys/out10

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
test:
	$(TEST)
