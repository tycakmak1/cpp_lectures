out: main.o Date.o MyClass.o
	g++ -std=c++17 main.o Date.o MyClass.o -o out

MyClass.o: MyClass.h MyClass.cpp
	g++ -std=c++17 -c MyClass.cpp

Date.o: Date.h Date.cpp
	g++ -std=c++17 -c Date.cpp

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

clean:
	rm *.o out

assem:
	g++ -std=c++17 -S *.cpp

format:
	clang-format -i -style=file *.cpp
