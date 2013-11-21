#include <stdio.h>

#include "link_list.h"

int main(void)
{
	
	link_insert(link_head, 5);
	link_print(link_head);
	link_init(&link_head);
	link_print(link_head);
	link_insert(link_head, 5);
	link_insert(link_head, 6);
//	link_insert(link_head, 4);
//	link_insert(link_head, 7);
	link_print(link_head);
	link_del(link_head, 6);
	link_print(link_head);
	link_del(link_head, 6);
	link_print(link_head);
	link_del(link_head, 5);
	link_print(link_head);

	return 0;
}
