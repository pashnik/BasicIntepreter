#include <stdio.h>

#define STACKVAL 100 // макисмальная длинна стека

int sp = 0;
int value[STACKVAL]; // стек для int

int sp_char = 0;
char char_value[STACKVAL]; // стек для char

void push(int number) {
    if (sp < STACKVAL) value[sp++] = number;
    else perror("Can't push, Stack is full");
}

int pop(void) {
    if (sp > 0) return value[--sp];
    else perror("Can't pop, Stack is empty");
    return 0;
}

void push_char(char symbol) {
    if (sp_char < STACKVAL) char_value[sp_char++] = symbol;
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