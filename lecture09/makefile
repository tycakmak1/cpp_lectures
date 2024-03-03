out: main.o foo.o
	g++ -std=c++17 main.o foo.o -o out

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

foo.o: foo.cpp foo.h
	g++ -std=c++17 -c foo.cpp

cleanup:
	rm *.out *.s

assem:
	g++ -std=c++17 -S *.cpp

format:
	clang-format -i -style=file *.cpp *.h
