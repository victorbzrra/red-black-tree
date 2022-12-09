#include <stdio.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1

#define TRUE 1
#define FALSE 0
#define FAIL -1

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
NODE * search(int key);
void removeKey(int key);
void fixDoubleBlack(NODE * node);
int hasRedChild(NODE * node);
void removeNode(NODE * node);
void swapKeys(NODE * x, NODE * y);
NODE * sibling(NODE * node);
int isOnLeft(NODE * node);
NODE * replace(NODE * node);
NODE * sucessor(NODE * node);