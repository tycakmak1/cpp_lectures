out: main.o
	gcc -std=c11 main.o -o out

main.o: main.c
	gcc -std=c11 -c main.c

cleanup:
	rm *.o *.s out

assem:
	gcc -std=c11 -S *.c

format:
	clang-format -i -style=file *.c