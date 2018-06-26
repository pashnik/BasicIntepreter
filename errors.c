#include <stdio.h>
#include <stdlib.h>

void errorExiting(char *errorType) {
    perror(errorType);
    exit(1);
}