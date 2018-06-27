#include <stdlib.h>
#include <memory.h>
#include "ctype.h"
#include "token.h"
#include "lexer.h"
#include "errors.h"
#include "interpreter.h"
#include "instructions.h"
#include "stdio.h"
#include "stack.h"

int getArithmeticResult(struct token *tokens);

int *getTotalLines(void);

int *getLabels(void);

void interpret(char **loadedProgram) {
    int totalLines = *getTotalLines();
    for (mainLoop = 0; mainLoop < totalLines; ++mainLoop) {
        char *currentLine = loadedProgram[mainLoop];
        struct token *tokens = getTokens(currentLine);
        if (tokens[0].type != DIGIT || tokens[1].type != COMMAND) errorExiting(SYN_ERR);
        whichCommand(tokens[1].value, tokens + 2);
    }
}

void whichCommand(int commandType, struct token *tokens) {
    switch (commandType) {
        case INPUT:
            commandInput(tokens);
            break;
        case PRINT:
            commandPrint(tokens);
            break;
        case LET:
            commandLet(tokens);
            break;
        case IF:
            commandIf(tokens);
            break;
        case GOTO:
            commandGoto(tokens);
            break;
        case END:
            commandEnd();
            break;
        case GOSUB:
            commandGosub(tokens);
            break;
        case RETURN:
            commandReturn();
            break;
        default:
            break;
    }
}

void commandInput(struct token *tokens) {
    do {
        if ((*tokens).type == QUOTE) {
            for (int i = 0; i < strlen((*tokens).quotesLine); ++i) {
                printf("%c", (*tokens).quotesLine[i]);
            }
            memset((*tokens).quotesLine, 0, sizeof((*tokens).quotesLine));
            ++tokens;
        }
        if ((*tokens).type != VARIABLE) errorExiting(SYN_ERR);
        int scannedValue;
        scanf("%d", &scannedValue);
        setValue((*tokens).tokenContent, scannedValue);
        ++tokens;
    } while ((*tokens).type != E0L);
}

void commandPrint(struct token *tokens) {
    do {
        if ((*tokens).type == QUOTE) {
            for (int i = 0; i < strlen((*tokens).quotesLine); ++i) {
                printf("%c", (*tokens).quotesLine[i]);
            }
            memset((*tokens).quotesLine, 0, sizeof((*tokens).quotesLine));
        } else {
            if ((*tokens).type == NEXT) printf("\n");
            else {
                if ((*tokens).type == VARIABLE)
                    printf("%d", getValue((*tokens).tokenContent));
                else errorExiting(SYN_ERR);
            }
        }
        ++tokens;
    } while ((*tokens).type != E0L);
}

void commandLet(struct token *tokens) {
    if ((*tokens).type != VARIABLE || (*(tokens + 1)).tokenContent != '=') errorExiting(SYN_ERR);
    setValue((*tokens).tokenContent, getArithmeticResult(tokens + 2));
}

void commandIf(struct token *tokens) {
    int checkComparison = 0, firstValue, secondValue;
    firstValue = getValueVarOrDigit(*tokens);
    if (firstValue < 0) errorExiting(SYN_ERR);
    ++tokens;
    if ((*tokens).type == OPERATOR) {
        while ((*tokens).type == OPERATOR) {
            checkComparison += getComparisonSign((*tokens).tokenContent);
            ++tokens;
        }
    }

    secondValue = getValueVarOrDigit(*tokens);
    if (secondValue < 0) errorExiting(SYN_ERR);
    if (getResult(checkComparison, firstValue, secondValue)) {
        ++tokens;
        if ((*tokens).type == COMMAND && (*tokens).value == GOTO) commandGoto(tokens + 1);
        else errorExiting(SYN_ERR);
    }

}

void commandGoto(struct token *tokens) {
    if ((*tokens).type != DIGIT) errorExiting(SYN_ERR);
    int gotoIndex = getIndex((*tokens).value, *getTotalLines());
    if (gotoIndex == -1) errorExiting(GO_ERR);
    mainLoop = gotoIndex - 1;
}

void commandEnd() {
    exit(0);
}

void commandGosub(struct token *tokens) {
    if ((*tokens).type != DIGIT) errorExiting(SYN_ERR);
    int goSubIndex = getIndex((*tokens).value, *getTotalLines());
    if (goSubIndex == -1) errorExiting(GO_ERR);
    pushCall(mainLoop);
    mainLoop = goSubIndex - 1;
}

void commandReturn() {
    int returnedIndex = popCall();
    mainLoop = returnedIndex;
}

int getValue(char symbol) {
    return variables[tolower(symbol) - 'a'];
}

void setValue(char symbol, int value) {
    variables[tolower(symbol) - 'a'] = value;
}

int getIndex(int lineNumber, int currentLines) { // binary search
    int *labels = getLabels();
    int low = 0;
    int high = currentLines - 1;
    while (low <= high) {
        int middle = (low + high) / 2;
        if (lineNumber == labels[middle]) return middle;
        else if (lineNumber > labels[middle]) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}

int getComparisonSign(char symbol) {
    switch (symbol) {
        case '>':
            return 1;
        case '<':
            return 2;
        case '=':
            return 4;
        default:
            return -1;
    }
}

int getResult(int intermediate, int firstValue, int secondValue) {
    switch (intermediate) {
        case 1:
            if (firstValue > secondValue) return 1;
            return 0;
        case 2:
            if (firstValue < secondValue) return 1;
            return 0;
        case 4:
            if (firstValue == secondValue) return 1;
            return 0;
        case 5:
            if (firstValue >= secondValue) return 1;
            return 0;
        case 6:
            if (firstValue <= secondValue) return 1;
            return 0;
        case 3:
            if (firstValue != secondValue) return 1;
            return 0;
        default:
            return 0;
    }
}

int getValueVarOrDigit(struct token currentToken) {
    switch (currentToken.type) {
        case VARIABLE:
            return getValue(currentToken.tokenContent);
        case DIGIT:
            return currentToken.value;
        default:
            break;
    }
    return -1;
}
