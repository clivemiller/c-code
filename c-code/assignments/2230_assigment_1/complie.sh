gcc -S min.c
gcc -S max.c
gcc -S sum-avg.c
gcc -S arrayCalculator.c

as min.s -o min.o
as max.s -o max.o
as sum-avg.s -o sum-avg.o
as arrayCalculator.s -o arrayCalculator.o

ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
  /usr/lib/x86_64-linux-gnu/Scrt1.o \
  /usr/lib/x86_64-linux-gnu/crti.o \
  min.o max.o sum-avg.o arrayCalculator.o \
  -lc \
  /usr/lib/x86_64-linux-gnu/crtn.o



