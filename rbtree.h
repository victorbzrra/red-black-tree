#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BLACK 0
#define RED 1

#define TRUE 1
#define FALSE 0

typedef struct node {
    int key;
    int color;
    struct node * left, * right, * parent;
}NODE;

NODE * createNode(int key);
NODE * insertNode(NODE * node, NODE * ghost);

void inOrder(NODE * node);

void removeKey(int key);
void removeNode(NODE * node);

int verifyProperties(NODE * node);
int verifyProperty1(NODE * node);
int verifyProperty2(NODE * node);
int verifyProperty4(NODE * root);
int verifyProperty4Left(NODE * left);
int verifyProperty4Right(NODE * right);
int verifyProperty5(NODE * node);
int verifyProperty5Left(NODE * left);
int verifyProperty5Right(NODE * right);
void verifyProperty5Helper(NODE * node, int blackCount, int * pathBlackCount);

int count(NODE * root);

NODE * sibling(NODE * node);
NODE * replace(NODE * node);
NODE * sucessor(NODE * node);
NODE * search(int key);

int hasRedChild(NODE * node);
int isOnLeft(NODE * node);

void fixUp(NODE * root, NODE * pt);
void swapKeys(NODE * x, NODE * y);
void fixDoubleBlack(NODE * node);
void rightRotate(NODE * node);
void leftRotate(NODE * node);