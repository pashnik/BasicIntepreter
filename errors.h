#ifndef ERRORS_H
#define ERRORS_H

#define COM_NAME "Wrong command name"
#define UNDEF_SYM "Undefined symbol"
#define OPEN_FILE "Error in opening file"
#define SYN_ERR "Syntax error"
#define FORMAT "Wrong file format"
#define GO_ERR "Wrong line number"
#define FULL_STACK "Can't push, stack is full"
#define EMPTY_STACK "Can't pop, stack is empty"
#define DIV_ZERO "Division on zero"
#define BASIC_LN "Number of lines should be in ascending order"

void errorExiting(char *errorType);

#endif
