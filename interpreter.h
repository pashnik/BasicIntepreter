#ifndef BASIC_INTEPRETER
#define BASIC_INTEPRETER

void whichCommand(int commandType, struct token *tokens);

void commandInput(struct token *tokens);

void commandPrint(struct token *tokens);

void commandLet(struct token *tokens);

void commandIf(struct token *tokens);

void commandGoto(struct token *tokens);

void commandEnd();

void commandGosub(struct token *tokens);

void commandReturn();

int getValue(char symbol);

int getIndex(int lineNumber, int currentLines);

int getComparisonSign(char symbol);

int getResult(int intermediate, int firstValue, int secondValue);

int getValueVarOrDigit(struct token currentToken);

void setValue(char symbol, int value);

int variables[26] = {0};

int mainLoop;

#endif BASIC_INTEPRETER