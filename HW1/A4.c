#include <stdint.h>
#include <stdio.h>

int main() {
  uint32_t N;
  int K;

  scanf("%u %d", &N, &K);

  uint32_t max_value = 0;

  for (int pos = 0; pos <= 32 - K; pos++) {
    uint32_t mask;
    if (K == 32) {
      mask = 0xFFFFFFFF;
    } else {
      mask = ((1 << K) - 1) << pos;
    }

    uint32_t value = (N & mask) >> pos;

    if (value > max_value) {
      max_value = value;
    }
  }

  printf("%u\n", max_value);

  return 0;
}