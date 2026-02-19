#include <stdio.h>

int main() {
  int N;
  scanf("%d", &N);

  if (N <= 0) {
    return 0;
  }

  int max_value;
  int count = 1;

  scanf("%d", &max_value);

  for (int i = 1; i < N; i++) {
    int current;
    scanf("%d", &current);

    if (current > max_value) {
      max_value = current;
      count = 1;
    } else if (current == max_value) {
      count++;
    }
  }

  printf("%d\n", count);

  return 0;
}