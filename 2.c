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

int hashFunc1(int arr[MAX]){
    int temparr[LENGTH]; //hash table
    int linearProbing = 0; //(h'k+i)%LENGTH
    double probeCount1 = 0;
    double avgCount1 = 0;
    int clusterCount1 = 0;
    
    for (int i = 0; i < LENGTH; i++){
        temparr[i] = -1;
    }

    for (int j = 0; j < MAX; j++){
        int result = arr[j]%LENGTH; //h'(k) = k%m
        int k = 0;
        while (temparr[(result+k)%LENGTH] != -1){
            k++;
            probeCount1++;
            clusterCount1++;
        }
        linearProbing = (result+k)%LENGTH;
        temparr[linearProbing] = arr[j];
        probeCount1++;
    }
    print(temparr, LENGTH);
    avgCount1 = probeCount1/MAX;
    printf("\nAverage Number of probes: %.2f\n", avgCount1);
    printf("%d\n", clusterCount1);

    return clusterCount1;
}

int hashFunc2(int arr[MAX]){
    int temparr[LENGTH];
    double probeCount2 = 0;
    int quadraticProbing = 0;
    double avgCount2 = 0;
    int clusterCount2 = 0;
    
    for (int i = 0; i < LENGTH; i++){
        temparr[i] = -1;
    }

    for (int j = 0; j < MAX; j++){
        int result = arr[j]%LENGTH;
        int k = 0;
        while (temparr[(result+k+3*k*k)%LENGTH] != -1){
            k++;
            probeCount2++;
            clusterCount2++;
        }
        quadraticProbing = (result+k+3*k*k)%LENGTH;
        temparr[quadraticProbing] = arr[j];
        probeCount2++;
    }
    print(temparr, LENGTH);
    avgCount2 = probeCount2/MAX;
    printf("\nAverage Number of probes: %.2f\n", avgCount2);
    printf("%d\n", clusterCount2);

    return clusterCount2;
}

int hashFunc3(int arr[MAX]){
    int temparr[LENGTH];
    int doubleHashing = 0;
    double probeCount3 = 0;
    double avgCount3 = 0;
    int clusterCount3 = 0;
    
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
            clusterCount3++;
        }
        doubleHashing = (result1+k*result2)%LENGTH;
        temparr[doubleHashing] = arr[j];
        probeCount3++;
    }
    print(temparr, LENGTH);
    avgCount3 = probeCount3/MAX;
    printf("\nAverage Number of probes: %.2f\n", avgCount3);
    printf("%d\n", clusterCount3);

    return clusterCount3;
}

int compare(int clusterCount1, int clusterCount2, int clusterCount3){
    int maxCluster = 0;
    if (clusterCount1 > clusterCount2 && clusterCount1 > clusterCount3){
        maxCluster = clusterCount1;
    }
    else if (clusterCount2 > clusterCount1 && clusterCount2 > clusterCount3){
        maxCluster = clusterCount2;
    }
    else if (clusterCount3 > clusterCount1 && clusterCount3 > clusterCount2){
        maxCluster = clusterCount3;
    }
    return maxCluster;
}

int main(){
    int temp[MAX];
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
    printf("Randomly Generated Numbers:\n");
    print(temp, MAX);
    printf("\n\n");
    printf("Hash Table for Linear Probing:\n");
    int n1 = hashFunc1(temp);
    printf("\n\n");
    printf("Hash Table for Quadratic Probing:\n");
    int n2 = hashFunc2(temp);
    printf("\n\n");
    printf("Hash Table for Double Hashing:\n");
    int n3 = hashFunc3(temp);
    
    int max = compare(n1, n2, n3);
    printf("\nPrimary Cluster Length: %d", max);
}
