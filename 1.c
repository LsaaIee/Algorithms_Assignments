#include <stdio.h>
#include <time.h>
#define MAX 50

void fillArray(int arr[MAX]){
    srand(time(NULL));
    for (int i = 0; i < MAX; i++){
        arr[i] = rand()%1000;
    }
}

int main(){
    int* arr1[MAX];
    fillArray(arr1[MAX]);
    for (int i = 0; i < MAX; i++){
        printf("%d ", arr1[i]);
    }

    return 0;
}