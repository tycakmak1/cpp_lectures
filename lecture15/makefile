out: main.o Complex.o
	g++ -std=c++17 -Wpedantic main.o Complex.o -o out

main.o: main.cpp
	g++ -std=c++17 -Wpedantic -c main.cpp

Complex.o: Complex.h Complex.cpp
	g++ -std=c++17 -Wpedantic -c Complex.cpp

cleanup:
	rm *.o out *.s

assem:
	g++ -std=c++17 -Wpedantic -S *.cpp

format:
	clang-format -i -style=file *.cpp *.h
