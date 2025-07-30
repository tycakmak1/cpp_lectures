out: main.o Car.o
	g++ -std=c++17 -Wpedantic main.o Car.o -o out

main.o: main.cpp
	g++ -std=c++17 -Wpedantic -c main.cpp

Car.o: Car.h Car.cpp
	g++ -std=c++17 -Wpedantic -c Car.cpp

cleanup:
	rm *.o out *.s

assem:
	g++ -std=c++17 -Wpedantic -S *.cpp

format:
	clang-format -i -style=file *.cpp
