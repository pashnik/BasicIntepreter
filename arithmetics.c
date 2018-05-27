int doArithmetic(int firstDigit, int secondDigit, const char *operator) {
    switch (*operator) {
        case '+':
            return firstDigit + secondDigit;
        case '-':
            return firstDigit - secondDigit;
        case '/':
            return firstDigit / secondDigit;
        case '*':
            return firstDigit * secondDigit;
        default:
            break;
    }
    return 0;
}