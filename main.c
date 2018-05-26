#include <stdio.h>
#include "interpreter.h"

#define MAX_LINE 200

char *readFile(char *fileName);

int main(void) {
    char *name = "/Users/air/ClionProjects/BasicIntepreter/newFile.txt";
    execute(readFile(name));
    return 0;
}

char *readFile(char *fileName) {  /*Возможно динамическое выделение памяти для строки < 255 символа*/
    FILE *file;
    char line[MAX_LINE] = {};
    char *line_pointer = line;
    int symbol;
    unsigned int i = 0;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening");
    else {
        do {
            symbol = fgetc(file);
            *(line_pointer + i) = (char) symbol;
            i++;
        } while (symbol != EOF);
    }
    fclose(file); // численное значение окончания строки = -1
    return line_pointer;
}
