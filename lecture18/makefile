out: main.o Date.o Myclass.o
	g++ -std=c++17 -Wpedantic main.o Date.o Myclass.o -o out

main.o: main.cpp
	g++ -std=c++17 -Wpedantic -c main.cpp

Myclass.o: Myclass.h Myclass.cpp
	g++ -std=c++17 -Wpedantic -c Myclass.cpp

Date.o: Date.h Date.cpp
	g++ -std=c++17 -Wpedantic -c Date.cpp

cleanup:
	rm out *.o *.s

assem:
	g++ -std=c++17 -Wpedantic -S *.cpp

format:
	clang-format -i -style=file *.cpp
