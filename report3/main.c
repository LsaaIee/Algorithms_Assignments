#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NAME 10
#define MAX 30

struct node {
    int data;
    char color;

    struct node *left, *right, *parent;
};

void inorder(struct node *root){
    if (root == NULL){
        return;
    }
    inorder(root->left);
    printf("%d(%c) ", root->data, root->color);
    inorder(root->right);
}
void leftRotate(struct node **root, struct node *x){
    struct node *y = x->right;
    x->right = y->left;

    if (x->right != NULL){
        x->right->parent = x;
    }
    y->parent = x->parent;
    
    if (x->right == NULL){
        (*root) = y;
    }
    else if (x == x->parent->left){
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}
void rightRotate(struct node **root, struct node *y){
    struct node *x = y->right;
    y->right = x->left;

    if (x->right != NULL){
        x->right->parent = x;
    }
    x->parent = y->parent;
    
    if (x->right == NULL){
        (*root) = x;
    }
    else if (y == y->parent->left){
        y->parent->left = x;
    }
    else {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}
void insertFixup(struct node **root, struct node *z){
    while (z->parent->color == 'R' && z != *root){
        struct node *y = NULL;
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if (y != NULL && y->color == 'R'){
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right){
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(root, z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if (y != NULL && y->color == 'R'){
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left){
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}
void rbInsert(struct node **root, int data){
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = z->right = z->parent = NULL;

    if (*root == NULL){
        z->color = 'B';
        (*root) = z;
    }
    else {
        struct node *y = NULL;
        struct node *x = (*root);

        while (x != NULL){
            y = x;
            if (z->data < x->data){
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        z->parent = y;
        if (z->data < y->data){
            y->left = z;
        }
        else {
            y->right = z;
        }
        z->color = 'R';
        insertFixup(root, z);
    }
}
/*
void deleteFixup(struct node **root, struct node *x){
    while (x != root && x->color = 'B'){
        struct node *w;
        if (x == x->parent->left){
            w = x->parent->right;
            if (w->color == 'R'){
                w->color = 'B';
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == 'B' && w->right->color == 'B'){
                w->color = 'R';
                x = x-> parent;
            }
            else if (w->right->color == 'B'){
                w->left->color = 'B';
                w->color = 'R';
                rightRotate(root, w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = 'B';
            w->right->color = 'B';
            leftRotate(root, x->parent);
            x = root;
        }
        else {
            w = x->parent->left;
            if (w->color == 'R'){
                w->color = 'B';
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == 'B' && w->left->color == 'B'){
                w->color = 'R';
                x = x-> parent;
            }
            else if (w->left->color == 'B'){
                w->right->color = 'B';
                w->color = 'R';
                leftRotate(root, w);
                w = x->parent->left;
            }
            w->color = x->parent->color;
            x->parent->color = 'B';
            w->left->color = 'B';
            rightRotate(root, x->parent);
            x = root;
        }
    }
    x->color = 'B';
}
void rbDelete(struct node **root, int data){
    struct node *z = (struct node*)malloc(sizeof(struct node));
    struct node *y;
    struct node *x;
    if (z->left == NULL || z->right == NULL){
        y = z;
    }
    else {
        
    }
}
*/
void randGraph(){
    char graph[27];
    srand(time(NULL));
	for(int i = 0; i < 27; i++){
        int check = 0;
        char c = (rand()%(122-97)+97);
        int j;
        for (j = 0; j < i; j++){
            if (graph[j] == c){
                check = 1;
                i--;
                break;
            }
        }
        if (check != 1){
            graph[i] = c;
            printf("%c", graph[i]);
        }
    }
}
void input(char name[], char source[], char dest[], int date){
    int i = 1;
    struct node *root = NULL;
    while (i != 11){
        printf("input your name, source, destination, and date in order:\n");
        while (scanf("%10[^,], %1[^,], %1[^,], %d", name, source, dest, &date) == 4){
            printf("----------------------------------------------------------------------------------\n");
            printf("Before insertion:\n");
            inorder(root);
            printf("\n");
            printf("After insertion\n");
            rbInsert(&root, i);
            inorder(root);
            printf("\n\n");
            break;
        }
        i++;
    }
}

int main(){
    char name[NAME], source[2], dest[2];
    int date;
    
    //input(name, source, dest, date);
    randGraph();
    return 0;
}