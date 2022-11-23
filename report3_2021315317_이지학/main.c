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
    // iterate until z is not the root and z's parent color is red
    while (z != *root && z->parent->color == 'R')
    {
        struct node *y;
 
        // Find uncle and store uncle in y
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;
 
        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (y->color == 'R')
        {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }
 
        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else if (y->color == 'B'){
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left && z == z->parent->left)
            {
                char ch = z->parent->color;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent);
            }

            // Left-Right (LR) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            if (z->parent == z->parent->parent->left && z == z->parent->right)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                leftRotate(root,z->parent);
                rightRotate(root,z->parent->parent);
            }
 
            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            if (z->parent == z->parent->parent->right && z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                leftRotate(root,z->parent->parent);
            }
 
            // Right-Left (RL) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            if (z->parent == z->parent->parent->right && z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent);
                leftRotate(root,z->parent->parent);
            }
        }
        else if (y == NULL && y->parent == *root){
            
        }
    }
    (*root)->color = 'B'; //keep root always black
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
        inorder(*root);
        printf("\n-------------------------------------------------------------------------------------\n");
        insertFixup(root,z);
    }
}
void rbDelete(){

}

void input(char name[], char source[], char dest[], int date){
    int i = 1;
    struct node *root = NULL;
    while (i != 4){
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

    struct node *root = NULL;
    rbInsert(&root, 1);
    rbInsert(&root, 2);
    rbInsert(&root, 3);

    inorder(root);
    
    //input(name, source, dest, date);
    
    return 0;
}