#ifndef LEXER_H
#define LEXER_H

unsigned int getToken(void);

void interpret(char *line);

void whichCommand(void);

int isSomething(char symbol);

int isGap(char symbol);

int haveCommand(const char *input);

void com_input(void);

void com_print(void);

void com_let(void);

void com_if(void);

void com_goto(void);

void com_return();

void com_goSub();

void com_end(void);

int getIndex(int lineNumber);

int getComparisonSign(char symbol);

int isVarOrDigit(unsigned int currentToken);

int getBoolRes(int intermediate, int firstValue, int secondValue);

int getValue(char symbol);

#endif