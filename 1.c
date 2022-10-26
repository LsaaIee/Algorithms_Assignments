#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

typedef struct{
    char* key;
    int* value;
} items;


int modFive(int arr[MAX]){
    return (key%5);
}


int main(){
    srand(time(NULL));
    int count = 0;
    int temp[MAX];
    for (int i = 0; i < MAX; i++){
        temp[i] = rand()%1000;
    }
    return 0;
}