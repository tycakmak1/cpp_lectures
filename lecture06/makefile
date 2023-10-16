out: main.o
	g++ -std=c++17 main.o -o out

main.o: main.cpp test.h
	g++ -std=c++17 -c main.cpp

clean:
	rm *.o out

assem:
	g++ -std=c++17 -S *.cpp

format:
	clang-format -i -style=file *.cpp *.h