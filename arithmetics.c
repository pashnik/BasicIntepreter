#include <ctype.h>
#include <memory.h>
#include "stdio.h"
#include "stdlib.h"
#include "stack.h"

#define ISNUMBER '0' // сигнал, что обнаружено число

int doArithmetic(int firstDigit, int secondDigit, const char *operator) {
    switch (*operator) {
        case '+':
            return firstDigit + secondDigit;
        case '-':
            return firstDigit - secondDigit;
        case '/':
            return firstDigit / secondDigit;
        case '*':
            return firstDigit * secondDigit;
        default:
            break;
    }
    return 0;
}


void toOPN(char *line) { // преобразование выражений в обратную польскую запись (АЛГОРИТМ СОРТИРОВОЧНОЙ СТАНЦИИ)

}

void calculateOPN(char *line) { // разбить на две функции (АЛГОРИТМ ВЫЧИСЛЕНИЯ ВЫРАЖЕНИЙ ОБРАТНОЙ ПОЛЬСКОЙ ЗАПСИИ)
    int type;
    int op2 = 0;
    char charBuffer[100] = {0};
    while (*line != 0) {
        if (*line == ' ') ++line;
        if (isdigit(*line)) {
            unsigned int i = 0;
            while (isdigit(*line)) {
                charBuffer[i] = *line;
                ++line;
                ++i;
            }
            type = ISNUMBER;
        } else type = *line;
        switch (type) {
            case ISNUMBER:
                push(atoi(charBuffer));
                memset(charBuffer, 0, sizeof(charBuffer));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0) {
                    push(pop() / op2);
                } else perror("Div on zero");
                break;
            default:
                perror("Unknown command");
                break;
        }
        ++line;
    }
    printf("%d", pop());
}