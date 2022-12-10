#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rbtree.h"

NODE * root = NULL;
int size_of_tree = 0;

NODE * createNode(int key) {
    NODE * new_node = malloc(sizeof(NODE));
    new_node -> key = key;
    new_node -> color = RED;
    new_node -> left = NULL;
    new_node -> right = NULL;
    new_node -> parent = NULL;

    return new_node;
}

int count(NODE * root) {
    if (root != NULL) {
        size_of_tree += 1;
        count(root -> left);
        count(root -> right);
    }

    return size_of_tree;
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

int verifyProperties(NODE * root) {
    int verify;
    
    verify = verifyProperty1(root);
    if (verify == 0 || verify == -1) {
        return 0;
    } else {
        printf("Property 1 that's OK!\n");
    }

    verify = verifyProperty2(root);
    if (verify == -1) {
        return 0;
    } else {
        printf("Property 2 that's OK!\n");
    }

    verify = verifyProperty4(root);

    if (verify == -1 || verify > 0) {
        return 0;
    } else {
        printf("Property 4 that's OK!\n");
    }
    
    verify = verifyProperty5(root);
    if (verify == -1) {
        return 0;
    } else {
        printf("Property 5 that's OK!\n");
    }
}

int verifyProperty1(NODE * node) {    
    if (node == NULL) {
        return 0;
    }

    if (node -> color == RED || node -> color == BLACK) {
        verifyProperty1(node -> left);
        verifyProperty1(node -> right);
    } else {
        return -1;
    }

    return 1;
}

int verifyProperty2(NODE * node) {
    return (node -> color == BLACK) ? 1 : -1;
}

int verifyProperty4(NODE * root) {
    if (root != NULL) {
        if (root -> color == RED) {
            if (root -> left != NULL) {
                if (root -> left -> color != BLACK) {
                    return 1;
                }
            }

            if (root -> right != NULL) {
                if (root -> right -> color != BLACK) {
                    return 1;
                }
            }
        }
        return verifyProperty4Left(root -> left) + verifyProperty4Right(root -> right);
    } else {
        return -1;
    }
}

int verifyProperty4Left(NODE * left) {
    if (left != NULL) {
        if (left -> color == RED) {
            if (left -> left != NULL && left -> left -> color != BLACK) {
                return 1;
            }

            if (left -> right != NULL && left -> right -> color != BLACK) {
                return 1;
            }
                
            if (left -> parent != NULL && left -> parent -> color != BLACK) {
                return 1;
            }
        }
        return 0 + verifyProperty4Left(left -> left) + verifyProperty4Right(left -> right);
    } else {
        return 0;
    }
}

int verifyProperty4Right(NODE * right) {
    if (right != NULL) {
        if (right -> color == RED) {
            if (right -> left != NULL && right -> left -> color != BLACK) {
                return 1;
            }

            if (right -> right != NULL && right -> right -> color != BLACK) {
                return 1;
            }
                
            if (right -> parent != NULL && right -> parent -> color != BLACK) {
                return 1;
            }
        }
        return 0 + verifyProperty4Right(right -> right) + verifyProperty4Left(right -> left);
    } else {
        return 0;
    }
}

int verifyProperty5(NODE * node) {
    if (node == NULL) {
        return -1;
    } else if (verifyProperty5Left(node -> left) == verifyProperty5Right(node -> right)){
        return 1;
    }
}
int verifyProperty5Left(NODE * left) {
    if (left != NULL) {
        if (left -> color == BLACK) {
            return 0 + verifyProperty5Left(left -> left) + verifyProperty5Right(left -> right);
        }
    } else {
        return 1;
    }
}

int verifyProperty5Right(NODE * right) {
    if (right != NULL) {
        if (right -> color == BLACK) {
            return 0 + verifyProperty5Right(right -> right) + verifyProperty4Left(right -> left);
        }
    } else {
        return 1;
    }
}

void verifyProperty5Helper(NODE * node, int blackCount, int * pathBlackCount) {
    if (node -> color == BLACK) {
        blackCount++;
    }

    if (node == NULL) {
        if (*(pathBlackCount) == -1) {
            *(pathBlackCount) = blackCount;
        }
        else {
            assert(blackCount == *(pathBlackCount));
        }
        return;
    }

    verifyProperty5Helper(node -> left,  blackCount, pathBlackCount);
    verifyProperty5Helper(node -> right, blackCount, pathBlackCount);
}

NODE * search(int key) {
    NODE * ghost = root;

    while (ghost != NULL) {
        if (ghost -> key > key) {
            if (ghost -> left == NULL) {
                break;
            } else {
                ghost = ghost -> left;
            }
        } else if (ghost -> key == key) {
            break;
        } else {
            if (ghost -> right == NULL) {
                break;
            } else {
                ghost = ghost -> right;
            }
        }
    }

    return ghost;
}

void removeKey(int key) {
    if (root == NULL) {
        return;
    }

    NODE * ghost = search(key);

    if (ghost -> key != key) {
        printf("\nNo node found to delete with value: [%d].\n", key);
        return;
    }

    removeNode(ghost);
}

NODE * sucessor(NODE * node) {
    NODE * ghost = node;

    while (ghost -> left != NULL) {
        ghost = ghost -> left;
    }

    return ghost;
}

NODE * replace(NODE * node) {
    if (node -> left != NULL && node -> right != NULL) {
        return sucessor(node -> right);
    }

    if (node -> left == NULL && node -> right == NULL) {
        return NULL;
    }

    if (node -> left != NULL) {
        return node -> left;
    } else {
        return node -> right;
    }
}
int isOnLeft(NODE * node) {
    if (node -> parent -> left == node) {
        return TRUE;
    }

    return FALSE;
}

NODE * sibling(NODE * node) {
    if (node -> parent == NULL) {
        return NULL;
    }

    if (isOnLeft(node)) {
        return node -> parent -> right;
    }

    return node -> parent -> left;
}

void swapKeys(NODE * x, NODE * y) {
    int key;
    key = x -> key;

    x -> key = y -> key;
    y -> key = key;
}

void removeNode(NODE * node) {
    NODE * ghost = replace(node);

    int verifyColorBlack = ((ghost == NULL || ghost -> color == BLACK) && (node -> color == BLACK)) ? TRUE : FALSE;
    NODE * parent = node -> parent;

    if (ghost == NULL) {
        if (node == root) {
            root = NULL;
        } else {
            if (verifyColorBlack) {
                fixDoubleBlack(node);
            } else {
                NODE * sibling_node = sibling(node);
                if (sibling_node != NULL) {
                    sibling_node -> color = RED;
                }
            }

            if (isOnLeft(node)) {
                parent -> left = NULL;
            } else {
                parent -> right = NULL;
            }
        }

        free(node);
        return;
    }

    if (node -> left == NULL || node -> right == NULL) {
        if (node == root) {
            node -> key = ghost -> key;
            node -> left = NULL;
            node -> right = NULL;

            free(ghost);
        } else {
            if (isOnLeft(node)) {
                parent -> left = ghost;
            } else {
                parent -> right = ghost;
            }

            free(node);
            ghost -> parent = parent;

            if (verifyColorBlack) {
                fixDoubleBlack(ghost);
            } else {
                ghost -> color = BLACK;
            }
        }
        return;
    }

    swapKeys(ghost, node);
    removeNode(ghost);
}

int hasRedChild(NODE * node) {
    if (node -> left != NULL && node -> left -> color == RED) {
        return TRUE;
    } else if (node -> right != NULL && node -> right -> color == RED) {
        return TRUE;
    }

    return FALSE;
}

void fixDoubleBlack(NODE * node) {
    if (node == root) {
        return;
    }

    NODE * sibling_node = sibling(node);
    NODE * parent = node -> parent;

    if (sibling_node == NULL) {
        fixDoubleBlack(parent);
    } else {
        if (sibling_node -> color == RED) {
            parent -> color = RED;
            sibling_node -> color = BLACK;

            if (isOnLeft(sibling_node)) {
                rightRotate(parent);
            } else {
                leftRotate(parent);
            }
            
            fixDoubleBlack(node);
        } else {
            if (hasRedChild(sibling_node)) {
                if (sibling_node -> left != NULL && sibling_node -> left -> color == RED) {
                    if (isOnLeft(sibling_node)) {
                        sibling_node -> left -> color = sibling_node -> color;
                        sibling_node -> color = parent -> color;
                        rightRotate(parent);
                    } else {
                        sibling_node -> left -> color = parent -> color;
                        rightRotate(sibling_node);
                        leftRotate(parent);
                    }
                } else {
                    if (isOnLeft(sibling_node)) {
                        sibling_node -> right -> color = parent -> color;
                        leftRotate(sibling_node);
                        rightRotate(parent);
                    } else {
                        sibling_node -> right -> color = sibling_node -> color;
                        sibling_node -> color = parent -> color;
                        leftRotate(parent);
                    }
                }
                parent -> color = BLACK;
            } else {
                sibling_node -> color = RED;

                if (parent -> color == BLACK) {
                    fixDoubleBlack(parent);
                } else {
                    parent -> color = BLACK;
                }
            }
        }
    }
}