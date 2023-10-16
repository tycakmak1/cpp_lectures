out: main.o complex.o
	g++ -std=c++17 main.o complex.o -o out

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

complex.o: complex.h complex.cpp
	g++ -std=c++17 -c complex.cpp

clean:
	rm *.o *.s out

assem:
	g++ -std=c++17 -S *.cpp

format:
	clang-format -i -style=file *.cpp *.h
