out: main.o foo.o
	g++ -std=c++17 -Wpedantic main.o foo.o -o out

main.o: main.cpp
	g++ -std=c++17 -Wpedantic -c main.cpp

foo.o: foo.cpp foo.h
	g++ -std=c++17 -Wpedantic -c foo.cpp

cleanup:
	rm *.o out *.s

assem:
	g++ -std=c++17 -Wpedantic -S *.cpp

format:
	clang-format -i -style=file *.cpp *.h
