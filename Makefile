all: random_cond.c
	gcc -std=gnu11 -o random random_cond.c
clean:
	$(RM) random_cond
