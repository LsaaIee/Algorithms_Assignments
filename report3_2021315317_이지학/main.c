#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME 10
#define MAX 30

int main(){
    char name[NAME], source[2], dest[2], temp[MAX];
    int date, i = 0;

    while (scanf("%10[^,], %1[^,], %1[^,], %d", name, source, dest, &date) == 4){
        printf("%s\n", name);
        printf("%s\n", source);
        printf("%s\n", dest);
        printf("%d", date);
        break;
    }    
    
    return 0;
}