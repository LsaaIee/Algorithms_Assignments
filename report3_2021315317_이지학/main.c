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
/*
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
*/
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
    // Allocate memory for new node
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = z->right = z->parent = NULL;
 
     //if root is null make z as root
    if (*root == NULL){
        z->color = 'B';
        (*root) = z;
    }
    else {
        struct node *y = NULL;
        struct node *x = (*root);
 
        // Follow standard BST insert steps to first insert the node
        while (x != NULL){
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (z->data > y->data){
            y->right = z;
        }
        else{
            y->left = z;
        }

        z->color = 'R';
 
        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.
        insertFixup(root,z);
    }
}
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
void rbDelete(){

}
void rbPrint(){

}

int main(){
    char name[NAME], source[2], dest[2];
    int date; 

    struct node *root = NULL;
    rbInsert(&root, 10);
    rbInsert(&root, 20);
    rbInsert(&root, 5);
    rbInsert(&root, 15);
    rbInsert(&root, 30);

    inorder(root);

    //input(name, source, dest, date);
    
    return 0;
}