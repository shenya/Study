#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "binary_tree.h"

BitTree tree_create(void)
{
    BitTree T = NULL;
    char ch;
    char temp;

    printf("Please input data\n");
    scanf("%c", &ch);
    //Skip '\n'
    scanf("%c", &temp);
    if (ch == '#') {
        T = NULL;
    } else {
        T = (BitTree)malloc(sizeof(BitNode));
        if (T == NULL) {
            printf("error\n");
            exit(1);
        }

        T->data = ch;
        T->lchild = tree_create();
        T->rchild = tree_create();
    }

    return T;
}

void pre_order_tree(BitTree T)
{
    if (T) {
        printf("%5c", T->data);
        pre_order_tree(T->lchild);
        pre_order_tree(T->rchild);
    }
}

void mid_order_tree(BitTree T)
{
    if (T) {
    if (T->lchild) {
        mid_order_tree(T->lchild);
        printf("%5c", T->data);
        mid_order_tree(T->rchild);
    } else if (T->rchild) {
        printf("%5c", T->data);
        mid_order_tree(T->rchild);
    } else {
        printf("%5c", T->data);
    }

   }
    
}

void post_order_tree(BitTree T)
{
    if (T) {
        if (T->lchild) {
            post_order_tree(T->lchild);
            post_order_tree(T->rchild);
            printf("%5c", T->data);
        } else if (T->rchild) {
            post_order_tree(T->rchild);
            printf("%5c", T->data);
        } else {
            printf("%5c", T->data);
        }

   }
}
int main(int argc, char *argv[])
{
    BitTree bi_tree;

    bi_tree = tree_create();
    if (bi_tree == NULL ) {
        printf("Tree create error\n");
    } else {
        printf("Tree create successfully\n");
    }

    pre_order_tree(bi_tree);
    printf("\n");
    mid_order_tree(bi_tree);
    printf("\n");
    post_order_tree(bi_tree);
    printf("\n");
    printf("hello world\n");
    return 0;
}
