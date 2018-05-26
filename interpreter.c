#include "stdio.h"

#define MAX_LENGTH 254

void interpret(char *line);

void execute(char *fileName) { // построчное считывание
    FILE *file;
    char str[MAX_LENGTH];
    char *str_pointer;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening file");
    while (1) {
        str_pointer = fgets(str, sizeof(str), file);
        if (str_pointer == NULL) break;
        interpret(str);
    }
}