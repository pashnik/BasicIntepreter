#include "stack.h"
#include "errors.h"

#define STACK_VAL 100 // stack length

int vsp = 0;
int value[STACK_VAL]; // numbers stack

int osp = 0;
char operands[STACK_VAL]; // operands stack

int nsp = 0;
int nestLevel[5]; // nesting 0level

void pushNumber(int number) {
    if (vsp < STACK_VAL) value[vsp++] = number;
    else errorExiting(FULL_STACK);
}

int popNumber(void) {
    if (vsp >= 0) return value[--vsp];
    else errorExiting(EMPTY_STACK);
    return 0;
}

void pushOperand(char symbol) {
    if (osp < STACK_VAL) operands[osp++] = symbol;
    else errorExiting(FULL_STACK);
}

char popOperand(void) {
    if (osp > 0) return operands[--osp];
    return 0;
}

int isEmpty(void) {
    if (osp > 0) return 0;
    else return 1;
}

void pushCall(int number) {
    if (nsp < 5) nestLevel[nsp++] = number;
    else errorExiting(FULL_STACK);
}

int popCall(void) {
    if (nsp > 0) return nestLevel[--nsp];
    else errorExiting(EMPTY_STACK);
    return 0;
}