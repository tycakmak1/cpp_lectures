out: main.o
	g++ -std=c++17 main.o -o out

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

cleanup:
	rm *.o *.s out
	
assem:
	g++ -std=c++17 -S *.cpp

format:
	clang-format -i -style=file *.cpp