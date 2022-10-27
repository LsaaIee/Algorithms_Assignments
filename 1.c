#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

int checkVal;

struct node{
    int data;
    struct node* next;
};
struct node *lst = NULL;

void insert(struct node **list, int x){
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = x;
    newNode->next = NULL;

    if (lst == NULL){
        lst = newNode;
    }
    else{
        struct node *lastNode = lst;
        while (lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
    checkVal++;
}

void print(int n, int temparr[n]){
    struct node *temp = lst;

    while (temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void modByN(int arr[MAX], int n){
    struct node* temparr[n];
    for (int i = 0; i < n; i++){
        temparr[i] = NULL;
    }
    for (int j = 0; j < MAX; j++){
        int result = arr[j]%n;
        insert(&temparr[result], arr[j]);
        printf("%d -> ", temparr[j]);
    }
    printf("NULL");
}

int main(){
    struct node *lst = NULL;

    int temp[MAX];
    int n;
    srand(time(NULL));
    for(int i = 0; i < 60; i++){
        temp[i] = rand()%1000;
        for (int j = 0; j < i-1; j++){
            if (temp[j] == temp[i]){
                i--;
                break;
            }
        }
    }
    modByN(&temp[MAX], 5);
    return 0;
}