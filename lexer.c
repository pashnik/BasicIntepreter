#include "stdio.h"
#include "ctype.h"
#include "string.h"

unsigned int getToken(void);

void interpret(char *line);

int isSomething(char symbol);

int isGap(char symbol);

int haveCommand(const char *input);

enum tokenType {
    DIGIT, OPERATOR, VARIABLE, COMMAND, E_O_L
};
char *commands[] = {"input", "print", "let", "if", "goto"};
char *token_pointer; // глобальный указатель на текущий адрес символа
char arrayToken[5]; // содержание токена
int basicLineNumber[100]; // номер строки в BASIC

unsigned int getToken(void) {
    if (*token_pointer == '\n' || *token_pointer == '\0') return E_O_L; // провекра на конец строки
    while (isGap(*token_pointer)) ++token_pointer;
    if (isdigit(*token_pointer)) { // число
        unsigned int i = 0;
        while (!isSomething(*(token_pointer + 1))) {
            arrayToken[i] = *token_pointer;
            ++i;
            ++token_pointer;
        }
        ++token_pointer;
        return DIGIT;
    }
    if (strchr("+-*/=()", *token_pointer)) {
        arrayToken[0] = *token_pointer;
        ++token_pointer;
        return OPERATOR;
    }
    if (isalpha(*token_pointer)) { // команда или переменная
        if (isalpha(*(token_pointer + 1))) { // команда
            unsigned int i = 0;
            while (isalpha(*(token_pointer))) {
                arrayToken[i] = *token_pointer;
                ++i;
                ++token_pointer;
            }
            if (haveCommand(arrayToken)) {
                ++token_pointer;
                return COMMAND;
            } else return 404;
        } else { // переменная
            ++token_pointer;
            return VARIABLE;
        }
    }
    return 404; // ошибка
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
    unsigned int currentToken, i = 0;
    do {
        currentToken = getToken();
        /*
         * ?????????? WHAT IS THE NEXT STEP ???????????????
         */
    } while (currentToken != E_O_L);
}

int haveCommand(const char *input) {
    for (int j = 0; j < 5; ++j) {
        unsigned int sum = 0;
        char *current_command = commands[j];
        for (int i = 0; i < strlen(current_command); ++i) {
            if (input[i] == current_command[i]) sum++;
        }
        if (sum == strlen(current_command)) return 1;
    }
    return 0;
}
