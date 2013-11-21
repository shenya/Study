#include <stdio.h>

#include "link_list.h"

int main(void)
{
	int red[6] = {0};
	
	link_init(&link_head);
	link_insert(link_head, red, 1);
	

	return 0;
}
