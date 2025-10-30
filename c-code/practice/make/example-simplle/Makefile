CC := gcc
oFlag := -o
cFlag := -c

printHello: main.o util.o
	$(CC) $(oFlag) printHello main.o util.o

main.o: main.c
	$(CC) $(cFlag) main.c

util.o: util.c
	$(CC) $(cFlag) util.c

clean: 
	rm main.o printHello util.o