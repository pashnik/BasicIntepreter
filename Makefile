main: main.o executer.o interpreter.o lexer.o arithmetics.o errors.o stack.o
	gcc main.o executer.o interpreter.o lexer.o arithmetics.o errors.o stack.o -o main
main.o: main.c executer.h errors.h 
	gcc -std=c11 -pedantic -Wall -Wextra -c main.c
executer.o: executer.c executer.h errors.h lexer.h token.h
	gcc -std=c11 -pedantic -Wall -Wextra -c executer.c
interpreter.o: interpreter.c interpreter.h token.h lexer.h errors.h instructions.h stack.h
	gcc -std=c11 -pedantic -Wall -Wextra -c interpreter.c
lexer.o: lexer.c lexer.h errors.h instructions.h token.h
	gcc -std=c11 -pedantic -Wall -Wextra -c lexer.c
arithmetics.o: arithmetics.c arithmetics.h stack.h token.h errors.h
	gcc -std=c11 -pedantic -Wall -Wextra -c arithmetics.c 
errors.o: errors.c 
	gcc -std=c11 -pedantic -Wall -Wextra -c errors.c
stack.o: stack.c stack.h errors.h
	gcc -std=c11 -pedantic -Wall -Wextra -c stack.c
clean:
	rm -rf *.o main