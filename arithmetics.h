#ifndef ARITHMETICS_H
#define ARITHMETICS_H

int prioritization(char symbol);

struct token *shuntingYard(struct token *tokens);

int calculateRPN(struct token *tokens);

#endif
