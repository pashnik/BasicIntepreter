#include <stdlib.h>
#include "stdio.h"
#include "ctype.h"
#include "string.h"

unsigned int getToken(void);

int doArithmetic(int firstDigit, int secondDigit, const char *operator);

void interpret(char *line);

void whichCommand(void);

int getValue(const char *symbol);

int isSomething(char symbol);

int isGap(char symbol);

int haveCommand(const char *input);

void com_input(void);

void com_print(void);

void com_let(void);

void com_if(void);

void com_goto(void);

void com_put(void);

enum tokenType {
    DIGIT, OPERATOR, VARIABLE, COMMAND, E_O_L, QUOTES
};
char *commands[] = {"input", "print", "let", "if", "goto", "put"};
char *token_pointer; // глобальный указатель на текущий адрес символа
char *var; // указатель на переменную
char *oper; // указатель на оператор
char tokenContent[100]; // содержание токена (число или команда)
int basicLineNumber[100]; // номер строки в BASIC
int variables[26] = {0};

unsigned int getToken(void) {
    if (*token_pointer == '\n' || *token_pointer == '\0') return E_O_L; // провекра на конец строки
    while (isGap(*token_pointer)) ++token_pointer;
    if (isdigit(*token_pointer)) { // число
        unsigned int i = 0;
        while (!isSomething(*(token_pointer))) {
            tokenContent[i] = *token_pointer;
            ++i;
            ++token_pointer;
        }
        ++token_pointer;
        return DIGIT;
    }
    if (strchr("+-*/=", *token_pointer)) {
        oper = token_pointer;
        ++token_pointer;
        return OPERATOR;
    }
    if (isalpha(*token_pointer)) { // команда или переменная
        if (isalpha(*(token_pointer + 1))) { // команда
            unsigned int i = 0;
            while (isalpha(*(token_pointer))) {
                tokenContent[i] = *token_pointer;
                ++i;
                ++token_pointer;
            }
            if (haveCommand(tokenContent)) {
                ++token_pointer;
                return COMMAND;
            } else return 404;
        } else { // переменная
            var = token_pointer;
            ++token_pointer;
            return VARIABLE;
        }
    }
    if (*token_pointer == '"') {
        token_pointer++;
        unsigned int i = 0;
        while (*token_pointer != '"') {
            tokenContent[i] = *token_pointer;
            ++i;
            ++token_pointer;
        }
        return QUOTES;
    }
    return 404; // ошибка
}

int isGap(char symbol) {  // пробел
    if (symbol == ' ') return 1;
    return 0;
}

int isSomething(char symbol) { // разделители
    if (strchr("()=/*+- ", symbol) || strchr("", symbol)) return 1;
    return 0;
}

void interpret(char *line) {
    token_pointer = line;
    unsigned int currentToken = getToken(), i = 0;
    if (currentToken != DIGIT) {  // проверка на номер строки
        perror("Wrong format");
    } else {
        basicLineNumber[i] = atoi(tokenContent);
    }
    currentToken = getToken();
    if (currentToken != COMMAND) { // после номера строки всегда идет команда
        perror("Wrong format, must be a command");
    } else {
        whichCommand();
    }
}

int haveCommand(const char *input) {
    for (int j = 0; j < 6; ++j) {
        unsigned int sum = 0;
        char *current_command = commands[j];
        for (int i = 0; i < strlen(current_command); ++i) {
            if (input[i] == current_command[i]) sum++;
        }
        if (sum == strlen(current_command)) return 1;
    }
    return 0;
}

int getValue(const char *symbol) { // получение значения переменной по имени
    return variables[(int) *symbol - 'a'];
}

int comparison(char *first, const char *second) {
    for (int i = 0; i < strlen(first); ++i) {
        if (first[i] != second[i]) return 0;
    }
    return 1;
}

void whichCommand(void) { // определение команды и выполнение действий
    unsigned int command = 0;
    for (unsigned int i = 0; i < 6; ++i) {
        if (comparison(tokenContent, commands[i])) command = i;
    }
    switch (command) {
        case 0:
            com_input();
            break;
        case 1:
            com_print();
            break;
        case 2:
            com_let();
            break;
        case 3:
            com_if();
            break;
        case 4:
            com_goto();
            break;
        case 5:
            com_put();
            break;
        default:
            break;
    }
}

void com_input(void) {

}

void com_print(void) {
    unsigned currentToken = getToken();
    if (currentToken == QUOTES) { // строка в кавычках
        currentToken = getToken();
        while (currentToken != QUOTES) {
            printf("%c", *tokenContent);
            currentToken = getToken();
        }
    } else { // переменные
        if (currentToken != VARIABLE) perror("Must have a variable");
        else {
            while (currentToken != E_O_L) {
                int value = getValue(var);
                printf("%d ", value);
                currentToken = getToken();
            }
        }
    }
}

void com_let(void) {
    unsigned int currentToken = getToken();
    if (currentToken != VARIABLE) perror("Must be a variable");
    else {
        char *mainVar = var;
        getToken();
        if (*oper != '=') perror("Must be an equal sign");
        else {
            currentToken = getToken();
            if (currentToken != VARIABLE) perror("Must be a variable");
            else {
                char *first_var = var;
                currentToken = getToken();
                if (currentToken != OPERATOR) perror("Must be an operator");
                else {
                    char *op = oper;
                    currentToken = getToken();
                    if (currentToken != DIGIT) perror("Must be a digit");
                    else {
                        int second_digit = atoi(tokenContent);
                        variables[(int) *mainVar - 'a'] = doArithmetic(getValue(first_var), second_digit, op);
                        if (getToken() != E_O_L) perror("MUST BE THE END OF LINE");
                    }
                }
            }
        }
    }
}

void com_if(void) {
}

void com_goto(void) {

}

void com_put(void) {
    unsigned int currentToken = getToken();
    if (currentToken != VARIABLE) perror("Must be a variable");
    else {
        char *mainVar = var;
        getToken();
        if (*oper != '=') perror("Must be an equal sign");
        else {
            currentToken = getToken();
            if (currentToken != DIGIT) perror("Must be a digit");
            else {
                int digit = atoi(tokenContent);
                variables[(int) *mainVar - 'a'] = digit;
                if (getToken() != E_O_L) perror("MUST BE THE END OF LINE");
            }
        }
    }
}