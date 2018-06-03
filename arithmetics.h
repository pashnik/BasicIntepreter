#ifndef ARITHMETICS_H
#define ARITHMETICS_H

int prioritization(char symbol);

char *shunting_yard(char *line);

int calculate_RPN(char *line);

int doArithmetic(char *line);

#endif