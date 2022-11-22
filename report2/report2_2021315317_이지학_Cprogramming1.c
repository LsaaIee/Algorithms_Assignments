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
    int count[n];
    int result = 0;
    int min = 1000;
    int max = 0;
    double avg = 0;
    int total = 0;
    for (int i = 0; i < n; i++){
        temparr[i] = NULL;
        count[i] = 0;
    }
    for (int j = 0; j < MAX; j++){
        int result = arr[j]%n;
        insert(&temparr[result], arr[j]);
        count[result]++;
    }
    for (int k = 0; k < n; k++){
        printf("%d: ", k);
        print(temparr[k]);
        
        if (count[k] > max){
            max = count[k];
        }
        if (count[k] < min){
            min = count[k];
        }
        total += count[k];
        avg = total/n;
        printf("\n");
    }
    printf("The shortest chain's length: %d\n", min);
    printf("The longest chain's length: %d\n", max);
    printf("The average length of chains: %.2f\n\n", avg);
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