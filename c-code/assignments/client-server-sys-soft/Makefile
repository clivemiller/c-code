CC = gcc
CFLAGS = -Wall -Wextra -g

all: Server Client

Server: _Server.c
	$(CC) $(CFLAGS) -o Server _Server.c

Client: _Client.c
	$(CC) $(CFLAGS) -o Client _Client.c

clean:
	rm -f Server Client

.PHONY: all clean
