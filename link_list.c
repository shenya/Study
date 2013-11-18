#include <stdio.h>
#include <stdlib.h>
#include "link_list.h"

#define NDEBUG
#include <assert.h>

LINK_LIST *list_head = NULL;

/*
 * function: list_init
 */
LINK_LIST *list_init(LINK_LIST **list_head)
{
    *list_head = (LINK_LIST *)malloc(sizeof(LINK_LIST));
    if (*list_head == NULL) {
        perror("malloc error");
        return NULL;
    }

    return *list_head;
}

LINK_LIST *list_insert(LINK_LIST *list_head, int num)
{
    LINK_LIST *new_node;
    LINK_LIST *head_temp = list_head;

    if (list_head == NULL) {
        printf("List is not initialized\n");
        return NULL;
    }
    new_node = (LINK_LIST *)malloc(sizeof(LINK_LIST));
    if (new_node == NULL) {
        perror("fail to malloc");
        exit(1);
    }
    new_node->next = NULL;
    new_node->number = num;
    new_node->next = list_head->next;
    list_head->next = new_node;

    return head_temp;
}

/*
 * function: list_print
 *
 */
void list_print(LINK_LIST *list_head)
{
    LINK_LIST *list = list_head;

    if (list == NULL) {
        printf("list is not initialized\n");
        return;
    }

    if (list->next == NULL) {
        printf("list is NULL\n");
        return;
    }

    list = list->next;
    assert(!list);
    printf("--------------list start-------------\n");
    while (list) {
        printf("list node: %d\n", list->number);
        list = list->next;
    }
    printf("--------------list end-------------\n");
}

int list_delete(LINK_LIST *head, int num)
{
    LINK_LIST *p, *q;
    int ret = -1;

    if (head == NULL) {
        printf("list is not initialized\n");
        return -1;
    }

    if (head->next == NULL) {
        printf("list is NULL\n");
        return -1;
    }

    p = head;
    q = p->next;
    while (q) {
        if (q->number == num) {
            p->next = q->next;
            free(q);
            ret = 0;
            break;
        }
        p = p->next;
        q = q->next;
    }

    return ret;
}

/*
 * function: list_destroy
 */
void list_destroy(LINK_LIST **head)
{
    LINK_LIST *p = NULL, *q = NULL;

    if (head == NULL) {
        printf("list is not initialized\n");
        return;
    }

    p = (*head)->next;
    while (p) {
        printf("Delete node, number: %d\n", p->number);
        q = p;
        p = p->next;
        free(q);
    }

    free(*head);
    *head = NULL;
}

/*
 * function: list_find
 */
LINK_LIST *list_find(LINK_LIST *head, int number)
{
    LINK_LIST *p = head;

    if (p == NULL) {
        printf("List is not initialized\n");
        return NULL;
    }

    if (p->next == NULL) {
        printf("List is NULL\n");
        return NULL;
    }

    while (p->next) {
        if (p->next->number == number) {
            break;
        }
        p = p->next;
    }

    return p->next;
}

/*
 * function: list_reverse
 */
LINK_LIST *list_reverse(LINK_LIST *head)
{
    LINK_LIST *tmp, *p;

    if (head == NULL) {
        printf("List is not initialized\n");
        return NULL;
    }

    if (head->next == NULL) {
        printf("List is NULL\n");
        return NULL;
    }

    tmp = head->next;
    while (tmp->next) {
        p = tmp->next;
        tmp->next = p->next;
        p->next = head->next;
        head->next = p;
        list_print(head);
    }

    return head;
}
