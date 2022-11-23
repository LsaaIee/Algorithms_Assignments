#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME 10
#define MAX 30

struct node {
    int data;
    char color;

    struct node *left, *right, *parent;
};

void input(char name[], char source[], char dest[], int date){
    int i = 0;
    while (i != 11){
        printf("Input your name, source, destination, and date in order: \n");
        while (scanf("%10[^,], %1[^,], %1[^,], %d", name, source, dest, &date) == 4){
            printf("%s\n", name);
            printf("%s\n", source);
            printf("%s\n", dest);
            printf("%d\n", date);
            printf("----------------------------------------------------------------------------------\n");
            rbPrint();
            rbInsert();
            break;
        }
        i++;
    }
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
    while (z != *root && z->parent->color == 'R'){
        struct node *y;
        if (z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
        }
        else {
            y = z->parent->parent->left;
        }

        if (y->color == 'R'){
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }
        else {
            if (z->parent == z->parent->parent->left && z == z->parent->left){
                char ch = z->parent->color;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root, z->parent->parent);
            }

            if (z->parent == z->parent->parent->left && z == z->parent->right){
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                leftRotate(root,z->parent);
                rightRotate(root,z->parent->parent);
            }

            if (z->parent == z->parent->parent->right && z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                leftRotate(root,z->parent->parent);
            }

            if (z->parent == z->parent->parent->right && z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent);
                leftRotate(root,z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}
void rbInsert(struct node **root, int data){
    
}
void rbDelete(){

}
void rbPrint(){

}

int main(){
    char name[NAME], source[2], dest[2];
    int date; 

    input(name, source, dest, date);
    
    return 0;
}