#ifndef _LINK_LIST_H
#define _LINK_LIST_H

typedef struct link_list
{
    int number;
    struct link_list *next;
}LINK_LIST;

extern LINK_LIST *list_head;
extern LINK_LIST *list_init(LINK_LIST **head);
extern LINK_LIST *list_insert(LINK_LIST *head, int num);
extern int list_delete(LINK_LIST *head, int num);
extern void list_destroy(LINK_LIST **head);
extern void list_print(LINK_LIST *head);
extern LINK_LIST *list_find(LINK_LIST *head, int number);
extern LINK_LIST *list_reverse(LINK_LIST *head);
#endif
