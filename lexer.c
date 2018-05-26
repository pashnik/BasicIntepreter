#include "stdio.h"
#include "ctype.h"
#include "string.h"

int getToken(void);

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
    return 404; // ошибка
}

void execute(char *result_string) {
    token_pointer = result_string;
    for (int i = 0; i < 8; ++i) {
        printf("%d\n", getToken());
    }
}

int isGap(char symbol) {  // пробел
    if (symbol == ' ') return 1;
    return 0;
}

int isSomething(char symbol) {
    if (strchr("()=/*+- ", symbol)) return 1;
    return 0;
}