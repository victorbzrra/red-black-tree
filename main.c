#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbtree.h"

extern NODE * root;

int main() {
    srand(time(NULL));
    int user_choice;
    int user_active = TRUE;
    int size;

    while (user_active == TRUE) {
        system("clear");
        printf("=======     RED BLACK TREE     =======\n");
        printf("[1] : INSERT NEW NODE\n");
        printf("[2] : SHOW RBTREE INORDER\n");
        printf("[3] : DELETE NODE\n");
        printf("[4] : VERIFY RBTREE\n");
        printf("[5] : COUNT NODES\n");

        printf("\nYour choice: ");
        scanf("%d", &user_choice);

        switch (user_choice) {
            case 1:
                printf("\nInsert a size of your RBTREE: ");
                scanf("%d", &size);

                for (int i = 0; i < size; i++) {
                    int random = rand() % 100;
                    NODE * ghost = createNode(i);
                    root = insertNode(root, ghost);
                    fixUp(root, ghost);
                }
                printf("\nRBTREE created!\n");

                break;
            case 2:
                printf("\n");
                inOrder(root);
                printf("\n");

                break;
            case 3:
                //  int loop = 0;
                printf("\nInsert a value: ");
                scanf("%d", &size);
                
                for (int i = 0; i < size; i++) {
                    removeKey(i);
                }

                /*
                while (loop < size) {
                    int random = rand() % 100;
                    NODE * search_random = search(random);

                    if (search_random != NULL && search_random -> key == random) {
                        removeKey(random);
                        loop++;
                    }  
                }
                */
                
                printf("\nRemoved nodes!\n");
                break;
            case 4:
                int verify = verifyProperties(root);
                if (!verify) printf("\nRBTREE failed!\n");

                break;
            case 5:
                int count_nodes = count(root);
                printf("\n%d\n", count_nodes);

                break;
            default:
                printf("\nInvalid choice!\n");

                break;
        }

        printf("\nTry again? 1 for 'yes' or other number for 'not' :)\n");
        scanf("%d", &user_active);
    }
    free(root);
}