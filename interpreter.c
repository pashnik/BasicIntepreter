#include <memory.h>
#include <stdlib.h>
#include "stdio.h"

#define MAX_LENGTH 254

void interpret(char *line);

char loadedProgram[100][MAX_LENGTH] = {0};

int labels[100] = {0};

void execute(char *fileName) { // построчное считывание
    char line[MAX_LENGTH];
    unsigned int i = 0;
    FILE *file;
    char str[MAX_LENGTH];
    char *str_pointer;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening file");
    while (1) {
        str_pointer = fgets(str, sizeof(str), file);
        if (str_pointer == NULL) break;
        for (int j = 0; j < strlen(str); ++j) {
            loadedProgram[j][i] = str[j];
        }
        ++i;
    }

    for (int k = 0; k < 50; ++k) {
        line[k] = loadedProgram[k][1];
    }

    char number[1];  /* жесть полная */

    for (int l = 0; l < 2; ++l) {
        number[0] = loadedProgram[0][l];
        number[1] = loadedProgram[1][l];
        labels[l] = atoi(number);
        memset(number, 0, sizeof(number));
    }

    //interpret(line);
}



