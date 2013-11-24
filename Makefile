all:
	gcc main.c link_list.c card_file.c -g

clean:
	rm a.out
