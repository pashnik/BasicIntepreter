#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include "lexer.h"
#include "errors.h"
#include "instructions.h"
#include "token.h"

struct command {
    char name[7];
    enum commandType type;
} commands[] = {
        "input", INPUT,
        "print", PRINT,
        "let", LET,
        "if", IF,
        "goto", GOTO,
        "end", END,
        "gosub", GOSUB,
        "return", RETURN,
};

struct token *getTokens(char *line) {
    unsigned int size = 20;
    unsigned int tp = 0;
    struct token *tokens = (struct token *) malloc(size * sizeof(struct token));
    char commandBuffer[7] = {0};
    char digitBuffer[5] = {0};
    while (*line != '\0' && *line != '\n') {
        while (isspace(*line)) ++line;
        if (isdigit(*line)) {
            unsigned int dp = 0;
            while (!isDelimiter(*line) && !isalpha(*line)) {
                digitBuffer[dp] = *line;
                ++line;
                ++dp;
            }
            tokens[tp].type = DIGIT;
            tokens[tp].value = atoi(digitBuffer);
            --line;
            memset(digitBuffer, 0, sizeof(digitBuffer));
        } else {
            if (strchr("+-=*<>/", *line)) {
                tokens[tp].type = OPERATOR;
                tokens[tp].tokenContent = *line;
            } else {
                if (isalpha(*line)) {
                    if (isalpha(*(line + 1))) {
                        unsigned int ap = 0;
                        while (isalpha(*line)) {
                            commandBuffer[ap] = *line;
                            ++ap, ++line;
                        }
                        if (getCommandType(commandBuffer) < 0) errorExiting(COM_NAME);
                        tokens[tp].type = COMMAND;
                        tokens[tp].value = getCommandType(commandBuffer);
                        memset(commandBuffer, 0, sizeof(commandBuffer));
                    } else {
                        tokens[tp].type = VARIABLE;
                        tokens[tp].tokenContent = *line;
                    }
                } else {
                    if (*line == '"') {
                        ++line;
                        tokens[tp].type = QUOTE;
                        unsigned int lp = 0;
                        while (*line != '"') {
                            if (*line == '#') tokens[tp].quotesLine[lp] = '\n';
                            else tokens[tp].quotesLine[lp] = *line;
                            ++lp, ++line;
                        }
                        ++line;
                    } else {
                        if (*line == '(' || *line == ')') {
                            tokens[tp].type = BRACKET;
                            tokens[tp].tokenContent = *line;
                        } else {
                            if (*line == '#') {
                                tokens[tp].type = NEXT;
                                tokens[tp].tokenContent = *line;
                            } else {
                                errorExiting(UNDEF_SYM);
                            }
                        }
                    }
                }
            }
        }
        reallocateMemory(&size, &tp, &tokens);
        if (*(line + 1) == '\0' || *(line + 1) == '\n') {
            tokens[tp + 1].type = E0L;
        }
        ++tp, ++line;
    }
    return tokens;
}


void reallocateMemory(unsigned int *size, const unsigned int *currentSize, struct token **tokens) {
    if (*currentSize + 1 > *size) {
        *size = *size * 2;
        *tokens = (struct token *) realloc(*tokens, *size * sizeof(struct token));
    }
}

int isDelimiter(char symbol) {
    if (strchr("()=/*+- \n", symbol) || strchr("", symbol) || strchr("\"", symbol)) return 1;
    return 0;
}

int getCommandType(char *command) {
    for (int i = 0; i < 8; ++i) {
        if (!strcmp(commands[i].name, command)) return commands[i].type;
    }
    return -1;
}

