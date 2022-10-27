#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

int checkVal;

struct node{
    int data;
    struct node* next;
};

void insert(struct node **list, int x){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = x;
    newNode->next = NULL;

    if (*list == NULL){
        *list = newNode;
    }
    else{
        struct node *lastNode = *list;
        while (lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
    checkVal++;
}

void print(struct node *list){
    struct node *temp = list;

    while (temp){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void modByN(int arr[MAX], int n){
    struct node* temparr[n];
    for (int i = 0; i < n; i++){
        temparr[i] = NULL;
    }
    for (int j = 0; j < MAX; j++){
        int result = arr[j] % n;
        insert(&temparr[result], arr[j]);
    }
    for (int k = 0; k < n; k++){
        printf("%d: ", k);
        print(temparr[k]);
    }
}

int main(){
    int temp[MAX];
    int n;
    srand(time(NULL));
    for(int i = 0; i < 50; i++){
        temp[i] = rand()%1000;
        for (int j = 0; j < i-1; j++){
            if (temp[j] == temp[i]){
                i--;
                break;
            }
        }
    }

    modByN(temp, 5);
    modByN(temp, 7);
    modByN(temp, 13);   
    return 0;
}