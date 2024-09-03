#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX_SIZE 100

int compute(int op1, int op2, char operator) {
    switch (operator) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '^': return pow(op1, op2);
        default: return 0;
    }
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int evaluatePostfix(char postfix[]) {
    int stack[MAX_SIZE];
    int top = -1;
    int operand1, operand2, result;
	int i;
    for (i = 0; postfix[i] != '\0'; i++) {
        char item = postfix[i];
        
        if (isOperator(item)) {
            operand2 = stack[top--];
            operand1 = stack[top--];
            result = compute(operand1, operand2, item);
            stack[++top] = result;
        } else {
            stack[++top] = item - '0'; 
        }
    }

    int netresult = stack[top];

    return netresult;
}



int main() {
    char postfix[MAX_SIZE];
    
    printf("Enter the postfix expression: ");
    scanf("%s", postfix);
    
    int result = evaluatePostfix(postfix);
    
    printf("Result of the postfix expression: %d\n", result);
    
    return 0;
}

