all: Shell

Shell: shell.o
	g++ shell.o -o Shell -Wall -pedantic

%.o: %.cpp
	g++ -c $< -o $@

clean:
	rm -f *.o
	rm -f Analyze
