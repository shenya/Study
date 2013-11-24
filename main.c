#include <stdio.h>
#include "link_list.h"
#include "card_file.h"

#define DATA_FILE "card.txt"

int main(void)
{
	int red[7] = {1, 3, 10, 20, 21, 26, 15};
	
	link_init(&link_head);

	link_print(link_head);

	read_file(DATA_FILE);


	link_print(link_head);

	link_compare(link_head, red, 7);
	

	return 0;
}
