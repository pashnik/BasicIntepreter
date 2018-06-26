#ifndef TOKEN_H
#define TOKEN_H

#define M_LENGTH 245

enum tokenType {
    DIGIT, OPERATOR, VARIABLE, COMMAND, QUOTE, E0L, BRACKET, NEXT
};

struct token {
    enum tokenType type;
    union {
        char tokenContent;
        char quotesLine[M_LENGTH];
        int value;
    };
};

#endif