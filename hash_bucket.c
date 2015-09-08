#include <stdio.h>
#include <stdlib.h>

#include "hash_bucket.h"

#define BUCKET_SIZE 5
#define NUM 20

Link_list *Hash_bucket[BUCKET_SIZE];

Link_list **find_bucket(int id)
{
    
    return &Hash_bucket[id % BUCKET_SIZE];
}

void rand_init(void)
{
    struct timeval tpstart;

    gettimeofday(&tpstart,NULL);
    srand(tpstart.tv_usec);
}

int list_insert(int id)
{
    Link_list *new_node = NULL;
    Link_list **list = find_bucket(id);

    new_node = (Link_list *)malloc(sizeof(Link_list));
    if (!new_node) {
        perror("Fail to malloc");
        return -1;
    }

    new_node->id = id;
    new_node->prev = new_node->next = NULL;

    if (!(*list)) {
        (*list) = new_node;
        (*list)->prev = NULL;
        (*list)->next = NULL;
    } else {
        new_node->next = (*list);
        (*list)->prev = new_node;
        (*list) = new_node;
    }

    return 0;
}

Link_list *list_delete(int id)
{
    Link_list **list = find_bucket(id);
    Link_list *q = *list;
    Link_list *node = NULL;

    if (!q) {
        printf("list is NULL\n");
        return NULL;
    }

    while (q) {
        if (q->id == id) {
            break;
        }
        q = q->next;
    }

    if (!q) {
        return NULL;
    }

    if (q == *list) {
        *list = q->next;
    } else {
        if (q->next != NULL) {
            q->prev->next = q->next;
            q->next->prev = q->prev;
        } else {
            q->prev->next = q->next;
        }
    }

    return q;
}

Link_list *list_find(int id)
{
    Link_list *list = *(Link_list **)(find_bucket(id));

    if (!list) {
        printf("Func: %s: List is NULL\n", __FUNCTION__);
        return NULL;
    }

    while (list) {
        if (list->id == id) {
            return list;
        }

        list = list->next;
    }

    return NULL;
}

void list_print(void)
{
    int i;
    Link_list *p = NULL, *q = NULL;

    printf("------------start---------\n");
    for (i = 0; i < BUCKET_SIZE; i++) {
        p = Hash_bucket[i];

        while (p) {
            printf("Bucket %d, id: %d\n", i, p->id);
            p = p->next;
        }
    }
    printf("------------end---------\n");
}

int main(int argc, char *argv[])
{
    int i;
    int id;
    Link_list *target = NULL;

    rand_init();
    
    for (i = 0; i < NUM; i++) {
        id = rand() % (BUCKET_SIZE * 100);
        printf("Inset id: %d\n", id);
        list_insert(id);
    }

    list_insert(5);
    list_print();
    list_insert(10);
    list_print();
    list_insert(15);
    list_print();
    list_insert(20);
    list_print();

    list_delete(20);
    list_print();
    list_delete(10);
    list_print();
    list_delete(5);
    list_print();
    list_delete(15);
    list_print();
#if 0
    target = list_find(97);
    if (target) {
        printf("target: %d\n", target->id);
    } else {
        printf("target: not found\n");
    }


    target = list_find(98);
    if (target) {
        printf("target: %d\n", target->id);
    } else {
        printf("target: not found\n");
    }
#endif
    printf("hello world\n");
    return 0;
}
