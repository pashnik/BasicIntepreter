void calculate_RPN(char *line);

char *shunting_yard(const char *line);

int main(void) {
    //char *name = "/Users/air/ClionProjects/BasicIntepreter/newFile.txt";
    //execute(name);
    char *sec_line = "4 + 4 * (4 - 7) - 1";
    //calculate_RPN(shunting_yard(sec_line));

    calculate_RPN("2 2 +");
    return 0;
}

