#ifndef ERRORS_H
#define ERRORS_H

#define COM_NAME "Wrong command name"
#define UNDEF_SYM "Undefined symbol"
#define OPEN_FILE "Error in opening file"
#define SYN_ERR "Syntax error"
#define FORMAT "Wrong file format"
#define GO_ERR "Wrong line number"

void errorExiting(char *errorType);

#endif
