#include <ctype.h>
#include <memory.h>
#include <stdlib.h>
#include "stdio.h"
#include "stack.h"

#define ISNUMBER '0' // сигнал, что обнаружено число
#define is_operator(c) ((c) == '+' || (c) == '-' || (c) == '/' || (c) == '*' || (c) == '!' || (c) == '%' || (c) == '=')

int prioritization(char symbol);

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


char *shunting_yard(const char *line) { // (АЛГОРИТМ СОРТИРОВОЧНОЙ СТАНЦИИ)
    char outputLine[100] = {0}; // выходная строка
    char *outputLine_pointer = outputLine;
    const char *currentLine = line;
    char sc;
    char c;
    char *strEnd = (char *) (line + strlen(line));
    while (currentLine < strEnd) {
        c = *currentLine;
        if (c != ' ') {
            if (isdigit(c)) {
                *outputLine_pointer = c;
                ++outputLine_pointer;
            } else if (is_operator(c)) {
                while (1) {
                    sc = pop_char();
                    if (is_operator(sc) && (prioritization(c)) <= (prioritization(sc))) {
                        *outputLine_pointer = sc;
                        ++outputLine_pointer;
                    } else break;
                }
                push_char(sc);
                push_char(c);
            } else if (c == '(') {
                push_char(c);
            } else if (c == ')') {
                while (1) {
                    sc = pop_char();
                    if (sc == '(') {
                        break;
                    } else {
                        *outputLine_pointer = sc;
                        ++outputLine_pointer;
                    }
                }
            }
        }
        ++currentLine;
    }
    while (!isEmpty_char()) {
        sc = pop_char();
        *outputLine_pointer = sc;
        ++outputLine_pointer;
    }
    return &outputLine[0];
}

void calculate_RPN(char *line) { // (АЛГОРИТМ ВЫЧИСЛЕНИЯ ВЫРАЖЕНИЙ ОБРАТНОЙ ПОЛЬСКОЙ ЗАПСИИ)
    int type;
    int op2 = 0;
    while (*line != 0) {
        if (*line == ' ') ++line;
        if (isdigit(*line)) {
            type = ISNUMBER;
        } else type = *line;
        switch (type) {
            case ISNUMBER:
                push((atoi(line)));
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

int prioritization(const char symbol) {
    switch (symbol) {
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            break;
    }
    return 0;
}