#ifndef __LINK_LIST__
#define __LINK_LIST__

typedef struct link_list
{
	struct link_list *next;
	int number;
}LINK_LIST;

extern LINK_LIST *link_head;
extern LINK_LIST *link_insert(LINK_LIST **head, int num);
extern void link_print(LINK_LIST *head);
#endif
