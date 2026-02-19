#include <stdint.h>
#include <stdio.h>

int main() {
  uint32_t N;

  scanf("%u", &N);

  uint32_t count = 0;
  uint32_t mask = 0;

  for (int pos = 0; pos < 32; pos++) {
    mask = 1 << pos;

    uint32_t value = N & mask;

    if (value != 0) {
      count++;
    }
  }
  printf("%d\n", count);

  return 0;
}