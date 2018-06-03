#include <memory.h>
#include <stdlib.h>
#include "stdio.h"
#include "lexer.h"

#define MAX_LENGTH 254
#define MAX_LINES 100

char *loadedProgram[MAX_LINES];

int labels[100] = {0};

int global_Index; // индекс main loop

unsigned int i;

void safeLabels();

void execute(char *fileName) { // построчное считывание из файла и запись двумерный массив
    FILE *file;
    char *str_pointer;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening file");
    while (1) {
        str_pointer = calloc(MAX_LENGTH + 1, sizeof(char));
        str_pointer = fgets(str_pointer, MAX_LENGTH, file);
        if (!str_pointer) break;
        loadedProgram[i] = str_pointer;
        ++i;
    }

    safeLabels(); // запоминание номеров строк BASIC

    for (global_Index = 0; global_Index < i; ++global_Index) { // main loop
        interpret(loadedProgram[global_Index]);
    }
}

int getIndex(int lineNumber) { // получение индекса массива labels по номеру строки
    for (int j = 0; j < i; ++j) {
        if (labels[j] == lineNumber) return j;
    }
    return -1;
}

void safeLabels() {
    char bufferNumber[2];
    for (int l = 0; l < i; ++l) {
        bufferNumber[0] = loadedProgram[l][0];
        bufferNumber[1] = loadedProgram[l][1];
        labels[l] = atoi(bufferNumber);
        memset(bufferNumber, 0, sizeof(bufferNumber));
    }
}




