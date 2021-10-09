
EXECUTABLES = fork pthread1 join1 mutex1 condvar barrier1

all: $(EXECUTABLES)

clean:
	rm -f core *.o $(EXECUTABLES) a.out

fork: 
	gcc fork.c -o fork -lpthread

pthread1:
	gcc pthread1.c -o pthread1 -lpthread

join1:
	gcc join1.c -o join1 -lpthread

mutex1:
	gcc mutex1.c -o mutex1 -lpthread

condvar:
	gcc condvar.c -o condvar -lpthread

barrier1:
	gcc barrier1.c -o barrier1 -lpthread
