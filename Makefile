all:
	gcc main.c link_list.c -g -Wall -O2

clean:
	rm a.out
