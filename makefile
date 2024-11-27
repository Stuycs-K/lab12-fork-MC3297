compile: main.c
	@gcc -Wall main.c
run: a.out
	@./a.out
clean:
	rm -f *.out