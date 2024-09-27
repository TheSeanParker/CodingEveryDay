main: main.o liba.a libb.a
	g++ main.o -o main -L. -la -lb

liba.a: a.o
	ar rcs liba.a a.o

libb.a: b.o
	ar rcs libb.a b.o

a.o: liba/a.cpp
	g++ -c liba/a.cpp -o a.o

b.o: libb/b.cpp
	g++ -Iliba -c libb/b.cpp -o b.o

main.o: main.cpp
	g++ -Iliba -Ilibb -c main.cpp -o main.o
	
clean:
	rm *.o *.a *.so main 