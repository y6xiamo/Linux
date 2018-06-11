.PHONY:clean

myshell:myshell.o
	gcc -g $^ -o $@
%.o:%.c
	gcc -g -c $^ -o $@

clean:
	rm -rf *.o myshell
