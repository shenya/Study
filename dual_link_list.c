#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dual_link_list.h"




DUAL_LINK_LIST *g_link_list;

int list_insert(DUAL_LINK_LIST *node)
{
    if (!node) {
        return -1;
    }

    if (!g_link_list) {
        g_link_list = node;
        node->next = node->prev = node;
    }

    g_link_list->prev->next = node;
    node->prev = g_link_list->prev;
    node->next = g_link_list;
    g_link_list->prev = node;

    g_link_list = node;

    return 0;
}

DUAL_LINK_LIST *list_delete(int id)
{
    DUAL_LINK_LIST *p = g_link_list;
    while (p) {
        if (p->msg.id == id) {
            p->next->prev = p->prev;
            p->prev->next = p->next;
            if (p == g_link_list) {
                if (p->next == p) {
                    g_link_list = NULL;
                } else {
                    g_link_list = p->next;
                }
            }
            return p;
        }

        p = p->next;
    }

    return NULL;
}

void print_list(void)
{
    DUAL_LINK_LIST *p = g_link_list;
    if (!p) {
        printf("%s:Link list is NULL\n", __FILE__);
        return;
    }

    printf("**************start**************\n");
    do {
        usleep(200000);
        printf("Link: id: %d\n", p->msg.id);
        p = p->next;
    } while (p != g_link_list);
    printf("***************end**************\n");
}

void link_init(int size)
{
   int i = 0;
   DUAL_LINK_LIST *new_node = NULL;

   for (i = 0; i < size; i++) {
       new_node = (DUAL_LINK_LIST *)malloc(sizeof(DUAL_LINK_LIST));
       if (!new_node) {
           perror("Fail to malloc");
           return;
       }

       memset(new_node, 0, sizeof(DUAL_LINK_LIST));
       new_node->msg.id = i;

       list_insert(new_node);
   }
}

int link_destroy(void)
{
   DUAL_LINK_LIST *p = g_link_list;
   DUAL_LINK_LIST *q = NULL;
   int cnt = 0;

   while (p) {
       cnt++;
       q = p;
       p = p->next;
       if (p == g_link_list) {
           p = NULL;
           g_link_list = NULL;
       }
       free(q);
   }
    
}

DUAL_LINK_LIST *list_find(int id)
{
    DUAL_LINK_LIST *p = g_link_list;

    while (p) {
        if (p->msg.id == id) {
            return p;
        }
        p = p->next;
        if (p == g_link_list) {
            break;
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    DUAL_LINK_LIST *node = NULL;
    link_init(5);

    print_list();

#if 0
    node = list_delete(3);
    if (node) {
        printf("Delete node: %d\n", node->msg.id);
        free(node);
    }
    print_list();

    node = list_delete(0);
    if (node) {
        printf("Delete node: %d\n", node->msg.id);
        free(node);
    }
    print_list();

    node = list_delete(2);
    if (node) {
        printf("Delete node: %d\n", node->msg.id);
        free(node);
    }
    print_list();

    node = list_delete(1);
    if (node) {
        printf("Delete node: %d\n", node->msg.id);
        free(node);
    }
    print_list();

    node = list_delete(4);
    if (node) {
        printf("Delete node: %d\n", node->msg.id);
        free(node);
    }
    print_list();
#endif
#if 0
    link_destroy();
    print_list();
#endif

    node = list_find(2);
    if (node) {
        printf("Find node: %d\n", node->msg.id);
    }

    node = list_find(8);
    if (node) {
        printf("Find node: %d\n", node->msg.id);
    } else {
        printf("Can't find node for id: %d\n", 8);
    }
    
    return 0;
}
