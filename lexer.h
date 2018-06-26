#ifndef LEXER_H
#define LEXER_H

struct token *getTokens(char *line);

void reallocateMemory(unsigned int *size, const unsigned int *currentSize, struct token **tokens);

int isDelimiter(char symbol);

int getCommandType(char *command);

#endif