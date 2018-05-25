#include "stdio.h"

void getToken();

enum tokenType {
    DIGIT, OPERAND, VARIABLE, COMMAND, E_O_L
};

char *token_pointer; // глобальный указатель на текущий адрес символа

void getToken() {

}

void execute(char *result_string) {
    token_pointer = result_string;
}

