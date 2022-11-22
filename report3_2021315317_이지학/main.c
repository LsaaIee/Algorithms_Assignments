#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME 10
#define MAX 30

int main(){
    char line[MAX], name[NAME], source[2], dest[2]
    int date, i, j, ctr;
    char token[MAX][MAX];
    
    scanf("%[^\n]", line);
    printf("%s\n", line);
    int len = strlen(line);

    j = 0; ctr = 0;
    for (i = 0; i < len; i++){
        if ((line[i] == ' ') || line[i] == '\0'){
            token[ctr][j] = '\0';
            ctr++;
            j = 0;
        }
        else {
            token[ctr][j] = line[i];
            j++;
        }

        date = atoi(line);
    }

    for (i = 0; i < ctr; i++){
        printf("%s\n", token[i]);
    }
    printf("%d", date);

    return 0;
}