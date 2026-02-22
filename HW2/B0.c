#include <stddef.h>
#include <stdint.h>


typedef struct list {
  uint64_t address;
  size_t size;
  char comment[64];
  struct list *next;
} list;

uint64_t findMaxBlock(list *head) {
  if (head == NULL) {
    return 0;
  }

  size_t max_size = head->size;
  uint64_t max_adress = head->address;

  list *current = head->next;
  while (current != NULL) {
    if (current->size > max_size) {
      max_size = current->size;
      max_adress = current->address;
    }
    current = current->next;
  }
  return max_adress;
}