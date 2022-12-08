#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

NODE * root = NULL;

NODE * createNode(int key) {
    NODE * new_node = malloc(sizeof(NODE));
    new_node -> key = key;
    new_node -> color = RED;
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> parent = NULL;

    return new_node;
}

NODE * insertNode(NODE * node, NODE * ghost) {
    if (node == NULL) {
        return ghost;
    }

    if (ghost -> key < node -> key) {
        node -> left = insertNode(node -> left, ghost);
        node -> left -> parent = node;
    } else if (ghost -> key > node -> key) {
        node -> right = insertNode(node -> right, ghost);
        node -> right -> parent = node;
    }

    return node;
}

void rightRotate(NODE * ghost) {
    NODE * left = ghost -> left;
    ghost -> left = left -> right;

    if (ghost -> left) {
        ghost -> left -> parent = ghost;
    }
    left -> parent = ghost -> parent;

    if (!ghost -> parent) {
        root = left;
    } else if (ghost == ghost -> parent -> left) {
        ghost -> parent -> left = left;
    } else {
        ghost -> parent -> right = left;
    }

    left -> right = ghost;
    ghost -> parent = left;
}

void leftRotate(NODE * ghost) {
    NODE * right = ghost -> right;
    ghost -> right = right -> left;

    if (ghost -> right) {
        ghost -> right -> parent = ghost;
    }
    right -> parent = ghost -> parent;

    if (!ghost -> parent) {
        root = right;
    } else if (ghost == ghost -> parent -> left) {
        ghost -> parent -> left = right;
    } else {
        ghost -> parent -> right = right;
    }

    right -> left = ghost;
    ghost -> parent = right;
}

void fixUp(NODE * root, NODE * pt) {
    NODE * parent_pt = NULL;
    NODE * grand_parent_pt = NULL;

    while ((pt != root) && (pt -> color != BLACK) && (pt -> parent -> color == RED)) {
        parent_pt = pt -> parent;
        grand_parent_pt = pt -> parent -> parent;

        if (parent_pt == grand_parent_pt -> left) {
            NODE * uncle_pt  = grand_parent_pt -> right;

            if (uncle_pt != NULL && uncle_pt -> color == RED) {
                    grand_parent_pt -> color = RED;
                    parent_pt -> color = BLACK;
                    uncle_pt -> color = BLACK;
                    pt = grand_parent_pt;
            } else {
                if (pt == parent_pt -> right) {
                    leftRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt -> parent;
                }

                rightRotate(grand_parent_pt);
                int ghost_color = parent_pt -> color;
                parent_pt -> color = grand_parent_pt -> color;
                grand_parent_pt -> color = ghost_color;
                pt = parent_pt;
            }
        } else {
            NODE * uncle_pt  = grand_parent_pt -> left;

            if (uncle_pt != NULL && uncle_pt -> color == RED) {
                grand_parent_pt -> color = RED;
                parent_pt -> color = BLACK;
                uncle_pt -> color = BLACK;
                pt = grand_parent_pt;
            } else {
                if (pt == parent_pt -> left) {
                    rightRotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt -> parent;
                }

                leftRotate(grand_parent_pt);
                int ghost_color = parent_pt -> color;
                parent_pt -> color = grand_parent_pt -> color;
                grand_parent_pt -> color = ghost_color;
                pt = parent_pt;
            }
        }
    }

    root -> color = BLACK;
}

void inOrder(NODE * node) {
    if (node == NULL) {
        return;
    }

    inOrder(node -> left);
    printf("%d ", node -> key);
    inOrder(node -> right);
}