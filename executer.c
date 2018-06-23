#include <memory.h>
#include <stdlib.h>
#include "stdio.h"
#include "lexer.h"
#include "executer.h"

#define MAX_LENGTH 254
#define M_LINE 100

char **loadedProgram;

int *labels;

int globalIndex; // индекс main loop

int currentLines;

void execute(char *fileName) { // построчное считывание из файла и запись двумерный массив
    unsigned int minLines = M_LINE;
    FILE *file;
    char *str_pointer;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening file");
    loadedProgram = (char **) malloc(minLines * sizeof(char *));
    while (1) {
        str_pointer = (char *) malloc(MAX_LENGTH * sizeof(char));
        str_pointer = fgets(str_pointer, MAX_LENGTH, file);
        if (!str_pointer) break;
        if (currentLines > minLines) {
            minLines += M_LINE;
            loadedProgram = (char **) realloc(loadedProgram, minLines);
        }
        loadedProgram[currentLines] = str_pointer;
        ++currentLines;
    }
    labels = calloc(minLines, sizeof(int));
    safeLabels(); // запоминание всех номеров у строк BASIC
    for (globalIndex = 0; globalIndex < currentLines; ++globalIndex) { // main loop
        interpret(loadedProgram[globalIndex]);
    }
}

int getIndex(int lineNumber) { // binary search
    int low = 0;
    int high = currentLines - 1;
    while (low <= high) {
        int middle = (low + high) / 2;
        if (lineNumber == labels[middle]) return middle;
        else if (lineNumber > labels[middle]) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}

void safeLabels() {
    char bufferNumber[2];
    for (int l = 0; l < currentLines; ++l) {
        bufferNumber[0] = loadedProgram[l][0];
        bufferNumber[1] = loadedProgram[l][1];
        labels[l] = atoi(bufferNumber);
        memset(bufferNumber, 0, sizeof(bufferNumber));
    }
}




