out: main.o Date.o MyClass.o
	g++ -std=c++17 -Wpedantic main.o Date.o MyClass.o -o out

main.o: main.cpp
	g++ -std=c++17 -Wpedantic -c main.cpp

MyClass.o: MyClass.h MyClass.cpp
	g++ -std=c++17 -Wpedantic -c MyClass.cpp

Date.o: Date.h Date.cpp
	g++ -std=c++17 -Wpedantic -c Date.cpp

cleanup:
	rm out *.o *.s

assem:
	g++ -std=c++17 -Wpedantic -S *.cpp

format:
	clang-format -i -style=file *.cpp
