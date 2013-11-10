all:
	gcc debug.c -g

.PHONY:clean
clean:
	rm a.out
