all: stallionShell

stallionShell: shell.o
	gcc shell.o -o stallionShell -Wall -pedantic -g

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -f *.o
	rm -f stallionShell
