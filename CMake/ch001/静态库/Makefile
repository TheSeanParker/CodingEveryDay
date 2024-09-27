main: main.o libab.a
	gcc main.o -o main -L. -lab

main.o: main.c
	gcc -c main.c -o main.o

libab.a: a.o b.o
	ar rcs libab.a a.o b.o

a.o: a.c
	gcc -c a.c -o a.o

b.o: b.c
	gcc -c b.c -o b.o