#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME 10
#define MAX 30

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

void rbInsert(){

}
void rbDelete(){

}
void rbPrint(){

}

int main(){
    char name[NAME], source[2], dest[2];
    int date; 

    input(name, source, dest, date);
    
    return 0;
}