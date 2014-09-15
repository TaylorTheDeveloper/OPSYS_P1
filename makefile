all: Shell

Shell: shell.o
	gcc shell.o -o Shell -Wall -pedantic -g

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -f *.o
	rm -f Shell
