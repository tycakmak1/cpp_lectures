out: main.o complex.o
	g++ -std=c++17 -Wpedantic main.o complex.o -o out

main.o: main.cpp
	g++ -std=c++17 -Wpedantic -c main.cpp

complex.o: complex.h complex.cpp
	g++ -std=c++17 -Wpedantic -c complex.cpp

cleanup:
	rm *.o out *.s

assem:
	g++ -std=c++17 -Wpedantic -S *.cpp

format:
	clang-format -i -style=file *.cpp *.h
