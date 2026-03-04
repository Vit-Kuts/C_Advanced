#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000

int main() {
  char s1[MAX_LEN + 1];
  char s2[MAX_LEN + 1];

  scanf("%s", s1);
  scanf("%s", s2);

  int len1 = strlen(s1);
  int len2 = strlen(s2);

  int max1 = 0;

  for (int len = 1; len <= len1 && len <= len2; len++) {
    int match = 1;
    for (int i = 0; i < len; i++) {
      if (s1[i] != s2[len2 - len + i]) {
        match = 0;
        break;
      }
    }
    if (match) {
      max1 = len;
    }
  }

  int max2 = 0;
  for (int len = 1; len <= len1 && len <= len2; len++) {
    int match = 1;
    for (int i = 0; i < len; i++) {
      if (s1[len1 - len + i] != s2[i]) {
        match = 0;
        break;
      }
    }
    if (match) {
      max2 = len;
    }
  }

  printf("%d %d\n", max1, max2);

  return 0;
}