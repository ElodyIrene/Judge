main: main.o Input.o Execute.o Output.o Input.h Execute.h Output.h std.h
	g++ -o main main.o Input.o Execute.o Output.o Input.h Execute.h Output.h std.h -g

main.o: main.cpp
	g++ -c -o main.o main.cpp
Input.o: Input.cpp
	g++ -c -o Input.o Input.cpp
Execute.o: Execute.cpp
	g++ -c -o Execute.o Execute.cpp
Output.o: Output.cpp
	g++ -c -o Output.o Output.cpp

clean:
	rm *.o
