#include <memory.h>
#include <stdlib.h>
#include "stdio.h"
#include "executer.h"
#include "errors.h"
#include "lexer.h"
#include "token.h"


#define MAX_LENGTH 254
#define M_LINE 100

void interpret(char **loadedProgram);

char **loadedProgram;

int *labels;

int lp = 0;

void execute(char *fileName) {
    unsigned int minLines = M_LINE;
    FILE *file;
    char *strPointer;
    file = fopen(fileName, "r");
    if (file == NULL) errorExiting(OPEN_FILE);
    loadedProgram = (char **) malloc(minLines * sizeof(char *));
    while (1) {
        strPointer = (char *) malloc(MAX_LENGTH * sizeof(char));
        strPointer = fgets(strPointer, MAX_LENGTH, file);
        if (!strPointer) break;
        if (lp > minLines) {
            minLines += M_LINE;
            loadedProgram = (char **) realloc(loadedProgram, minLines);
        }
        loadedProgram[lp] = strPointer;
        ++lp;
    }
    labels = calloc(minLines, sizeof(int));
    safeLabels(lp);
    interpret(loadedProgram);
}

void safeLabels(const int lp) {
    for (int i = 0; i < lp; ++i) {
        int currentLineNumber = getTokens(loadedProgram[i])[0].value;
        labels[i] = currentLineNumber;
    }
}

int *getLabels(void) {
    return labels;
}

int *getTotalLines(void) {
    return &lp;
}




