CC = gcc
CFLAGS = -Wall -Wextra -g

all: pipe_example bidirectional_pipe

pipe_example: pipe_example.c
	$(CC) $(CFLAGS) -o pipe_example pipe_example.c

bidirectional_pipe: bidirectional_pipe.c
	$(CC) $(CFLAGS) -o bidirectional_pipe bidirectional_pipe.c

clean:
	rm -f pipe_example bidirectional_pipe

.PHONY: all clean
