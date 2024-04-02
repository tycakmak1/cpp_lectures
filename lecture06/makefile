out: main.o
	g++ -std=c++17 main.o -o out

main.o: main.cpp test.h
	g++ -std=c++17 -c main.cpp

cleanup:
	rm *.o out *.s

assem:
	g++ -std=c++17 -S *.cpp

format:
	clang-format -i -style=file *.cpp *.h
