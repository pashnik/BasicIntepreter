#include <stdio.h>

#define STACKVAL 100 // макисмальная длинна стека

int sp = 0;
int value[STACKVAL]; // стек

void push(int number) {
    if (sp < STACKVAL) value[sp++] = number;
    else perror("Can't push, Stack is full");
}

int pop(void) {
    if (sp > 0) return value[--sp];
    else perror("Can't pop, Stack is empty");
    return 0;
}