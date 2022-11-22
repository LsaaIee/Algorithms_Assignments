#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NAME 10
#define MAX 30

char *removeSpace(char *str){
    int i = 0, j = 0;
    while (str[i]){
        if (str[i] != ' '){
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';

    return str;
}


int main(){
    char line[MAX], name[NAME], source[2], dest[2], temp[MAX];
    int date, i = 0;
    char *token;

    
    gets(line);
    removeSpace(line);
    printf("%s\n", line);
    token = strtok(line, ",");
    
    while (token != NULL){
        if (i == 0){
            strcpy(name, token);
        }
        else if (i == 1){
            strcpy(source, token);
        }
        else if (i == 2){
            strcpy(source, token);
        }
        else if (i == 3){
            date = atoi(token);
        }
        i++;
        token = strtok(NULL, ",");
    }
    
    printf("%s\n", name);
    printf("%c\n", source);
    printf("%c\n", dest);
    printf("%d", date);
    
    return 0;
}