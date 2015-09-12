#ifndef __BINARY_TREE__
#define __BINARY_TREE__

typedef struct bitNode {
    char data;
    struct bitNode *lchild;
    struct bitNode *rchild;
}BitNode, *BitTree;

#endif
