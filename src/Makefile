main : main.o functions.o
	clang -o main main.o functions.o

main.o : main.c functions.h
	clang -c main.c

functions.o : functions.c functions.h
	clang -c functions.c

clean:
	rm -f *.o program 