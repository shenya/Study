#include <stdio.h>

#include "link_list.h"

int main(void)
{
        LINK_LIST *p = NULL;
	
	list_print(list_head);
        list_init(&list_head);
	list_print(list_head);
	list_insert(list_head, 4);
	list_insert(list_head, 3);
	list_insert(list_head, 2);
	list_insert(list_head, 1);
	list_print(list_head);
        list_reverse(list_head);
	list_print(list_head);
/*
        p = list_find(list_head, 4);
        if (p) {
            printf("Find-number: %d\n", p->number);
        }

	list_print(list_head);
        list_delete(list_head, 6);
        list_print(list_head);
        list_delete(list_head, 6);
        list_print(list_head);
        list_delete(list_head, 4);
        list_print(list_head);
        list_destroy(&list_head);
        list_print(list_head);
*/
	return 0;
}
