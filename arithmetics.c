#include <ctype.h>
#include <stdlib.h>
#include "stdio.h"
#include "stack.h"
#include "arithmetics.h"
#include "token.h"

#define IS_NUMBER '0'
#define IS_VARIABLE 'a'

int getValue(char symbol);

int getArithmeticResult(struct token *tokens) {
    return calculateRPN(shuntingYard(tokens));
}

struct token *shuntingYard(struct token *tokens) { // (АЛГОРИТМ СОРТИРОВОЧНОЙ СТАНЦИИ) testing
    struct token *outTokens = (struct token *) malloc(100 * sizeof(struct token));
    struct token *outPointer = outTokens;
    char sc;
    while ((*tokens).type != E0L) {
        if ((*tokens).type == DIGIT) {
            (*outTokens).type = (*tokens).type;
            (*outTokens).value = (*tokens).value;
        } else if ((*tokens).type == VARIABLE) {
            (*outTokens).type = (*tokens).type;
            (*outTokens).tokenContent = (*tokens).tokenContent;
        } else if ((*tokens).type == OPERATOR) {
            while (1) {
                sc = pop_char();
                if (prioritization((*tokens).tokenContent) <= (prioritization(sc))) {
                    (*outTokens).type = OPERATOR;
                    (*outTokens).tokenContent = sc;
                    ++outTokens;
                } else break;
            }
            push_char(sc);
            push_char((*tokens).tokenContent);
            --outTokens;
        } else if ((*tokens).tokenContent == '(') {
            push_char((*tokens).tokenContent);
            --outTokens;
        } else if ((*tokens).tokenContent == ')') {
            while (1) {
                sc = pop_char();
                if (sc == '(') {
                    if ((*(tokens + 1)).type != E0L) {
                        --outTokens;
                    }
                    break;
                } else {
                    (*outTokens).type = OPERATOR;
                    (*outTokens).tokenContent = sc;
                    ++outTokens;
                }
            }
        }
        ++tokens, ++outTokens;
    }
    if ((*(outTokens - 1)).tokenContent == '\0') --outTokens;
    while (!isEmpty_char()) {
        sc = pop_char();
        if (sc != '\0') {
            (*outTokens).type = OPERATOR;
            (*outTokens).tokenContent = sc;
            ++outTokens;
        }
    }
    (*outTokens).type = E0L;
    return outPointer;
}

int calculateRPN(struct token *tokens) { //(АЛГОРИТМ ВЫЧИСЛЕНИЯ ВЫРАЖЕНИЙ ОБРАТНОЙ ПОЛЬСКОЙ ЗАПСИИ)
    int type;
    int op2 = 0;
    while ((*tokens).type != E0L) {
        if ((*tokens).type == VARIABLE) type = IS_VARIABLE;
        else if ((*tokens).type == DIGIT) type = IS_NUMBER;
        else type = (*tokens).tokenContent;
        switch (type) {
            case IS_VARIABLE:
                push(getValue((*tokens).tokenContent));
                break;
            case IS_NUMBER:
                push((*tokens).value);
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
        ++tokens;
    }
    return pop();
}

int prioritization(char symbol) {
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
