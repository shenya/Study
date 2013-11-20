#include <stdio.h>

#include "link_list.h"

int main(void)
{
	
	link_print(link_head);
	link_insert(&link_head, 5);

	link_print(link_head);

	printf("hello \n");

	return 0;
}
