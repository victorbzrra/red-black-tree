#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

typedef struct node {
    int key;
    int color;
    struct node * left, * right, * parent;
}NODE;

NODE * createNode(int key);
NODE * insertNode(NODE * node, NODE * ghost);
void rightRotate(NODE * ghost);
void leftRotate(NODE * ghost);
void fixUp(NODE * root, NODE * pt);
void inOrder(NODE * node);