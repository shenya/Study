#ifndef __HASH_BUCKET_H__
#define __HASH_BUCKET_H__

typedef struct Link_list
{
    struct Link_list *prev;
    struct Link_list *next;

    int id;
}Link_list;

#endif
