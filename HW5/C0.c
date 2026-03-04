#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000

int main() {
  char N[MAX_LEN + 1];

  scanf("%s", N);

  int len = strlen(N);

  int found[10][10][10] = {0};
  int count = 0;

  for (int i = 0; i < len - 2; i++) {
    for (int j = i + 1; j < len - 1; j++) {
      for (int k = j + 1; k < len; k++) {
        if (N[i] != '0') {
          int a = N[i] - '0';
          int b = N[j] - '0';
          int c = N[k] - '0';

          if (!found[a][b][c]) {
            found[a][b][c] = 1;
            count++;
          }
        }
      }
    }
  }

  printf("%d\n", count);

  return 0;
}