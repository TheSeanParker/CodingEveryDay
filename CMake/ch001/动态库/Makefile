main: main.o liba.so
	gcc main.o -o main -L. '-Wl,-R$$ORIGIN' -la

main.o: main.c
	gcc -c main.c -o main.o

liba.so: a.o
	gcc -shared a.o -o liba.so

a.o: a.c
	gcc -fPIC -c a.c -o a.o

clean:
	rm *.o *.so main || true