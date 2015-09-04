#ifndef __DUAL_LINK_LIST__
#define __DUAL_LINK_LIST__

typedef struct link_msg
{
    int id;
}link_msg;

typedef struct dual_link_list_node
{
    struct dual_link_list_node *prev;
    struct dual_link_list_node *next;
    link_msg msg;
}DUAL_LINK_LIST;

#endif
