#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

typedef struct Stack_int{
    long long array[MAX];
    int top;
} stack_int;

typedef struct Stack_char{
    char array[MAX];
    int top;
} stack_char;

void push_int(stack_int* stack, long long x){
    stack->array[stack->top] = x;
    stack->top++;
}

void push_char(stack_char* stack, char c){
    stack->array[stack->top] = c;
    stack->top++;
}

long long pop_int(stack_int* stack){
    long long n = stack->array[stack->top - 1];
    stack->top--;
    return n;
}

char pop_char(stack_char* stack){
    char c = stack->array[stack->top - 1];
    stack->top--;
    return c;
}

long long calc(long long a, long long b, char op){
    long long c;
    switch (op){
        case '+':
            c = a + b;
            break;
        case '-':
            c = a - b;
            break;
        case '*':
            c = a * b;
            break;
        case '/':
            if (a > 0 && b > 0 || a < 0 && b < 0)
                c = a / b;
            else{
                if (a % b == 0)
                    c = a / b;
                else
                    c = a / b - 1;
            }
            break;
        case '%':
            c = a % b;
            break;
    }
    return c;
}

int main(){
    stack_int stack1;
    stack1.top = 0;
    stack_char stack2;
    stack2.top = 0;
    char ch, op;
    long long n = 0;
    long long a, b, c;
    int no_number = 0;
    while (scanf("%c", &ch) != EOF){
        if (ch >= '0' && ch <= '9'){
            n = 10 * n + (int) (ch - 48);
        }
        else if (ch == '+' || ch == '-'){
            if (no_number)
                no_number = 0;
            else{
                push_int(&stack1, n);
                n = 0;
            }
            while (stack2.top > 0 && stack2.array[stack2.top - 1] != '('){
                b = pop_int(&stack1);
                a = pop_int(&stack1);
                op = pop_char(&stack2);
                c = calc(a, b, op);
                push_int(&stack1, c);
            }
            push_char(&stack2, ch);
        }
        else if (ch == '*' || ch == '/' || ch == '%'){
            if (no_number)
                no_number = 0;
            else{
                push_int(&stack1, n);
                n = 0;
            }
            while (stack2.top > 0 && stack2.array[stack2.top - 1] != '(' && stack2.array[stack2.top - 1] != '+' && stack2.array[stack2.top - 1] != '-'){
                b = pop_int(&stack1);
                a = pop_int(&stack1);
                op = pop_char(&stack2);
                c = calc(a, b, op);
                push_int(&stack1, c);
            }
            push_char(&stack2, ch);
        }
        else if (ch == '(')
            push_char(&stack2, ch);
        else if (ch == ')'){
            if (no_number)
                no_number = 0;
            else{
                push_int(&stack1, n);
                n = 0;
            }
            while (stack2.top > 0 && stack2.array[stack2.top - 1] != '('){
                b = pop_int(&stack1);
                a = pop_int(&stack1);
                op = pop_char(&stack2);
                c = calc(a, b, op);
                push_int(&stack1, c);
            }
            pop_char(&stack2);
            no_number = 1;
        }
        else if (ch == '='){
            if (no_number)
                no_number = 0;
            else{
                push_int(&stack1, n);
                n = 0;
            }
            while (stack2.top > 0){
                b = pop_int(&stack1);
                a = pop_int(&stack1);
                op = pop_char(&stack2);
                c = calc(a, b, op);
                push_int(&stack1, c);
            }
            printf("Print: %lld\n", stack1.array[0]);
            n = 0;
        no_number = 1;
        }
    }
    return 0;
}
