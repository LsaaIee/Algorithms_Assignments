#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

struct items{
    int key;
    int value;
};

struct items* hashArray5[5];
struct items* hashArray7[7];
struct items* hashArray13[13];
struct items* dummyItem;
struct items* item;

int modFive(int key){
    return (key%5);
}

struct items *serch(int key){
    int hashIndex = modFive(key);
    while (hashArray5[hashIndex] != NULL){
        if (hashArray5[hashIndex]->key == key){
            return hashArray5[hashIndex];
        }
        ++hashIndex;
        hashIndex %= 5;
    }
    return NULL;
}

void insert(int key, int value){
    struct items *item = (struct items*)malloc(sizeof(struct items));
    item->value = value;
    item->key = key; 

    int hashIndex = modFive(key);

    while (hashArray5[hashIndex] != NULL && hashArray5[hashIndex]->key != -1){
        ++hashIndex;
        hashIndex %= 5;
    }
    hashArray5[hashIndex] = item;
}

void display() {
   int i = 0;
	
   for(i = 0; i < 5; i++) {
	
      if(hashArray5[i] != NULL)
         printf(" (%d,%d)",hashArray5[i]->key, hashArray5[i]->value);
      else
         printf(" ~~ ");
   }
	
   printf("\n");
}

int main(){
    dummyItem = (struct items*)malloc(sizeof(struct items));
    dummyItem->key = -1;
    dummyItem->value = -1;
    srand(time(NULL));
    int temp[MAX];

    for (int i = 0; i < MAX; i++){
        temp[i] = rand()%1000;
    }
    display();
    return 0;
}