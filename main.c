#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

extern NODE * root;
#define TRUE 1

int main() {
    int user_choice;
    int user_active = TRUE;
    int key;

    while (user_active == TRUE) {
        system("clear");
        printf("=======     RED BLACK TREE     =======\n");
        printf("[1] : INSERT NEW NODE\n");
        printf("[2] : SHOW RBTREE INORDER\n");

        printf("\nYour choice: ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                printf("\nInsert a key: ");
                scanf("%d", &key);

                NODE * ghost = createNode(key);
                root = insertNode(root, ghost);
                fixUp(root, ghost);

                break;
            case 2:
                printf("\n");
                inOrder(root);
                printf("\n");

                break;
            default:
                printf("\nInvalid choice!\n");

                break;
        }

        printf("\nTry again? 1 for 'yes' or other number for 'not' :)\n");
        scanf("%d", &user_active);
    }
    
}