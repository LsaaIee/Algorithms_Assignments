#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 30
#define LENGTH 37

void print(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
}

void hashFunc1(int arr[MAX]){
    int temparr[LENGTH]; //hash table
    int linearProbing = 0; //(h'k+i)%LENGTH
    int probeCount1 = 0;
    
    for (int i = 0; i < LENGTH; i++){
        temparr[i] = -1;
    }

    for (int j = 0; j < MAX; j++){
        int result = arr[j]%LENGTH; //h'(k) = k%m
        int k = 0;
        while (temparr[(result+k)%LENGTH] != -1){
            k++;
            probeCount1++;
        }
        linearProbing = (result+k)%LENGTH;
        temparr[linearProbing] = arr[j];
        probeCount1++;
    }
    print(temparr, LENGTH);
    printf("\n%d\n", probeCount1);
}

void hashFunc2(int arr[MAX]){
    int temparr[LENGTH];
    int probeCount2 = 0;
    int quadraticProbing = 0;
    
    for (int i = 0; i < LENGTH; i++){
        temparr[i] = -1;
    }

    for (int j = 0; j < MAX; j++){
        int result = arr[j]%LENGTH;
        int k = 0;
        while (temparr[(result+k+3*k*k)%LENGTH] != -1){
            k++;
            probeCount2++;
        }
        quadraticProbing = (result+k+3*k*k)%LENGTH;
        temparr[quadraticProbing] = arr[j];
        probeCount2++;
    }
    print(temparr, LENGTH);
    printf("\n%d\n", probeCount2);
}

void hashFunc3(int arr[MAX]){
    int temparr[LENGTH];
    int doubleHashing = 0;
    int probeCount3 = 0;
    
    for (int i = 0; i < LENGTH; i++){
        temparr[i] = -1;
    }
    for (int j = 0; j < MAX; j++){
        int result1 = arr[j]%LENGTH;
        int result2 = 1+(arr[j]%(LENGTH-1));
        int k = 0;
        while (temparr[(result1+k*result2)%LENGTH] != -1){
            k++;
            probeCount3++;
        }
        doubleHashing = (result1+k*result2)%LENGTH;
        temparr[doubleHashing] = arr[j];
        probeCount3++;
    }
    print(temparr, LENGTH);
    printf("\n%d\n", probeCount3);
}

int main(){
    int temp[MAX];
    int n;
    srand(time(NULL));
    for(int i = 0; i < MAX; i++){
        temp[i] = rand()%1000;
        for (int j = 0; j < i-1; j++){
            if (temp[j] == temp[i]){
                i--;
                break;
            }
        }
    }
    print(temp, MAX);
    printf("\n\n");
    hashFunc1(temp);
    printf("\n\n");
    hashFunc2(temp);
    printf("\n\n");
    hashFunc3(temp);
    printf("\n\n");
}
