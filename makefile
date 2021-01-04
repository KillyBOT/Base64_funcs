cc = gcc

all: test.o base64.o
	$(CC) -o test test.c base64.c

test.o: test.c base64.h
	$(CC) -c test.c

base64.o: base64.c base64.h
	$(CC) -c base64.c

clean:
	rm *.o