#include "stdio.h"
#include "ctype.h"
#include "string.h"

#define MAX_LENGTH 254

int getToken(void);

void interpret(char *line);

int isSomething(char symbol);

int isGap(char symbol);

enum tokenType {
    DIGIT, OPERATOR, VARIABLE, COMMAND, E_O_L
};

char *token_pointer; // глобальный указатель на текущий адрес символа
char currentToken[50];

int getToken(void) {
    if (*token_pointer == '\n' || *token_pointer == '\0') return E_O_L; // провекра на конец строки
    while (isGap(*token_pointer)) ++token_pointer;
    if (isdigit(*token_pointer)) {
        unsigned int i = 0;
        while (!isSomething(*(token_pointer + 1))) {
            currentToken[i] = *token_pointer;
            i++;
            ++token_pointer;
        }
        ++token_pointer;
        return DIGIT;
    }
    if (strchr("+-*/=()", *token_pointer)) {
        ++token_pointer;
        return OPERATOR;
    }

    if (isalpha(*token_pointer)) { // команда или переменная
        if (isalpha(*(token_pointer + 1))) { // команда
            unsigned int i = 0;
            while (isalpha(*(token_pointer + 1))) {
                currentToken[i] = *token_pointer;
                i++;
                ++token_pointer;
            }
            ++token_pointer;
            return COMMAND;
        } else {
            ++token_pointer;
            return VARIABLE;
        }
    }

    return 404; // ошибка
}

void execute(char *fileName) {
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

int isGap(char symbol) {  // пробел
    if (symbol == ' ') return 1;
    return 0;
}

int isSomething(char symbol) {
    if (strchr("()=/*+- ", symbol) || strchr("", symbol)) return 1;
    return 0;
}

void interpret(char *line) {
    token_pointer = line;
    for (int i = 0; i < 8; ++i) {
        printf("%d", getToken());
    }
}
