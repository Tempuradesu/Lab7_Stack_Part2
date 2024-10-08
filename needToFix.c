#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define MAX 100

int top = -1;
char stack[MAX];

void push(char data) {
    if (top < MAX - 1) {
        stack[++top] = data;
    } else {
        printf("Stack overflow\n");
    }
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    } else {
        return stack[top--];
    }
}


int order(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}


int isOp(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}


void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i++];
        } else if (infix[i] == '(') {
            push(infix[i++]);
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            top--; // Remove '(' from stack
            i++;
        } else if (isOp(infix[i])) {
            while (top != -1 && order(stack[top]) >= order(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i++]);
        }
    }
    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}


int compute(int op1, int op2, char op) {
    switch (op) {
        case '^' : return pow(op1, op2);
        case '*' : return op1 * op2;
        case '/' : return op1 / op2;
        case '+' : return op1 + op2;
        case '-' : return op1 - op2;
        default  : return 0;
    }
}


int evaluate(char postfix[]) {
    int stack[MAX], i, op1, op2, ans;
    top = -1; // Reset top for the integer stack
    for (i = 0; postfix[i] != '\0'; i++) {
        char item = postfix[i];
        if (isOp(item)) {
            op2 = pop();  // Right operand
            op1 = pop();  // Left operand
            ans = compute(op1, op2, item);
            push(ans);
        } else {
            push(item - '0'); // Convert to number and push to stack
        }
    }
    return pop(); // The final result will be the only element left in stack
}

int main() {
    char infix[MAX];
    char postfix[MAX];
    printf("Enter infix: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    int result = evaluate(postfix);
    printf("Result: %d\n", result);

    return 0;
}
