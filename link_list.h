#ifndef __LINK_LIST__
#define __LINK_LIST__

typedef struct link_list
{
	struct link_list *next;
	int red_card[6];
	int blue_card;
}LINK_LIST;

extern LINK_LIST *link_head;
extern LINK_LIST *link_init(LINK_LIST **head);
extern LINK_LIST *link_insert(LINK_LIST *head, int *red, int length);
extern void link_print(LINK_LIST *head);
extern int award_get(int flag);
extern int link_compare(LINK_LIST *head, int *card, int length);
#endif
