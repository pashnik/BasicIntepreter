#include <stdio.h>
#include "stack.h"

#define STACK_VAL 100 // макисмальная длинна стека

int sp = 0;
int value[STACK_VAL]; // стек для int

int sp_char = 0;
char char_value[STACK_VAL]; // стек для char

int sp_goSub = 0;
int goSub_value[5]; // уровень вложенности

void push(int number) {
    if (sp < STACK_VAL) value[sp++] = number;
    else perror("Can't push, Stack is full");
}

int pop(void) {
    if (sp > 0) return value[--sp];
    else perror("Can't pop, Stack is empty");
    return 0;
}

void push_char(char symbol) {
    if (sp_char < STACK_VAL) char_value[sp_char++] = symbol;
    else perror("Can't push, Stack is full");
}

char pop_char(void) {
    if (sp_char > 0) return char_value[--sp_char];
    return 0;
}

int isEmpty_char(void) {
    if (sp_char > 0) return 0;
    else return 1;
}

void push_goSub(int number) {
    if (sp_goSub < 5) goSub_value[sp_goSub++] = number;
    else perror("Can't push, Stack is full");
}

int pop_goSub(void) {
    if (sp_goSub > 0) return goSub_value[--sp_goSub];
    else perror("Can't pop, Stack is empty");
    return 0;
}