#include "executer.h"
#include "errors.h"

int main(int argc, char **argv) {
    if (argc != 2) errorExiting(FORMAT);
    char *name = argv[1];
    execute(name);
    return 0;

}

