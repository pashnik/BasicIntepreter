#ifndef STACK_H
#define STACK_H

void pushNumber(int number);

int popNumber(void);

char popOperand(void);

void pushOperand(char symbol);

void pushCall(int number);

int popCall(void);

int isEmpty(void);


#endif