#include <ctype.h>
#include <memory.h>
#include <stdlib.h>
#include "stdio.h"
#include "stack.h"
#include "arithmetics.h"
#include "lexer.h"

#define IS_NUMBER '0' // сигнал, что обнаружено число
#define IS_VARIABLE 'a'
#define is_operator(c) ((c) == '+' || (c) == '-' || (c) == '/' || (c) == '*' || (c) == '!' || (c) == '%' || (c) == '=')


int doArithmetic(char *line) {
    return calculate_RPN(shunting_yard(line));
}

char *shunting_yard(char *line) { // (АЛГОРИТМ СОРТИРОВОЧНОЙ СТАНЦИИ)
    char outputLine[100] = {0}; // выходная строка
    char *out = outputLine;
    char *outputLine_pointer = outputLine;
    const char *currentLine = line;
    char sc;
    char c;
    char *strEnd = line + strlen(line);
    while (currentLine < strEnd) {
        c = *currentLine;
        if (c != ' ') {
            if (isdigit(c)) {
                while (isdigit(*currentLine)) {
                    *outputLine_pointer = *currentLine;
                    ++outputLine_pointer;
                    ++currentLine;
                }
                *outputLine_pointer = ' ';
                ++outputLine_pointer;
                --currentLine;
            } else if (isalpha(c)) {
                *outputLine_pointer = *currentLine;
                *(outputLine_pointer + 1) = ' ';
                outputLine_pointer = outputLine_pointer + 2;
            } else if (is_operator(c)) {
                while (1) {
                    sc = pop_char();
                    if (is_operator(sc) && (prioritization(c)) <= (prioritization(sc))) {
                        *outputLine_pointer = sc;
                        *(outputLine_pointer + 1) = ' ';
                        outputLine_pointer = outputLine_pointer + 2;
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
                        *(outputLine_pointer + 1) = ' ';
                        outputLine_pointer = outputLine_pointer + 2;
                    }
                }
            }
        }
        ++currentLine;
    }
    while (!isEmpty_char()) {
        sc = pop_char();
        *outputLine_pointer = sc;
        *(outputLine_pointer + 1) = ' ';
        outputLine_pointer = outputLine_pointer + 2;
    }
    return out;
}

int calculate_RPN(char *line) { //(АЛГОРИТМ ВЫЧИСЛЕНИЯ ВЫРАЖЕНИЙ ОБРАТНОЙ ПОЛЬСКОЙ ЗАПСИИ)
    char charBuffer[100];
    char newChar[100] = {0};
    int type;
    int op2 = 0;
    while (*line != 0) {
        if (*line == ' ') ++line;
        if (isalpha(*line)) {
            type = IS_VARIABLE;
        } else if (isdigit(*line)) {
            unsigned int i = 0;
            while (isdigit(*line)) {
                newChar[i] = *line;
                ++line;
                ++i;
            }
            type = IS_NUMBER;
        } else type = *line;
        switch (type) {
            case IS_VARIABLE:
                push(getValue(*line));
                break;
            case IS_NUMBER:
                push(atoi(newChar));
                memset(newChar, 0, sizeof(newChar));
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
                break;
        }
        ++line;
    }
    return pop();
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

int getComparisonSign(char symbol) {
    switch (symbol) {
        case '>':
            return 1;
        case '<':
            return 2;
        case '=':
            return 4;
        default:
            return -1;
    }
}
