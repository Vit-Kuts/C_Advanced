#include <stdint.h>
#include <stdio.h>


int main() {
  uint32_t N;
  int K;

  scanf("%u %d", &N, &K);

  uint32_t mask;

  if (K == 32) {
    mask = 0xFFFFFFFF;
  } else {
    mask = (1 << K) - 1;
  }

  uint32_t result = N & mask;

  printf("%u\n", result);

  return 0;
}