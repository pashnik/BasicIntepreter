#include <stdlib.h>
#include "executer.h"
#include "stdio.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Wrong format!");
        exit(1);
    }
    char *name = argv[1];
    execute(name);
    return 0;
}

