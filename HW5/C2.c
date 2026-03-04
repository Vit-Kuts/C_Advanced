#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

int stack[MAX];
int top = -1;

void push(int x) { stack[++top] = x; }

int pop() { return stack[top--]; }

int main() {
  char s[100];

  while (scanf("%s", s) == 1) {
    int len = strlen(s);

    if (s[len - 1] == '.') {
      s[len - 1] = '\0';

      if (isdigit(s[0])) {
        push(atoi(s));
      } else if (strlen(s) == 1 && strchr("+-*/%", s[0])) {
        int b = pop();
        int a = pop();
        switch (s[0]) {
          case '+':
            push(a + b);
            break;
          case '-':
            push(a - b);
            break;
          case '*':
            push(a * b);
            break;
          case '/':
            push(a / b);
            break;
          case '%':
            push(a % b);
            break;
        }
      }
      break;
    } else {
      if (isdigit(s[0])) {
        push(atoi(s));
      } else if (strlen(s) == 1 && strchr("+-*/%", s[0])) {
        int b = pop();
        int a = pop();
        switch (s[0]) {
          case '+':
            push(a + b);
            break;
          case '-':
            push(a - b);
            break;
          case '*':
            push(a * b);
            break;
          case '/':
            push(a / b);
            break;
          case '%':
            push(a % b);
            break;
        }
      }
    }
  }

  printf("%d\n", pop());
  return 0;
}