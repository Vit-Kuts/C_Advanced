#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LEN 20

struct list {
  char word[MAX_WORD_LEN];
  struct list *next;
};

struct list *add_to_list(struct list *head, const char *word) {
  struct list *new_node = (struct list *)malloc(sizeof(struct list));
  strcpy(new_node->word, word);
  new_node->next = NULL;

  if (head == NULL) {
    return new_node;
  }

  struct list *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_node;

  return head;
}

void swap_elements(struct list *a, struct list *b) {
  char temp[MAX_WORD_LEN];
  strcpy(temp, a->word);
  strcpy(a->word, b->word);
  strcpy(b->word, temp);
}

void sort_list(struct list *head) {
  if (head == NULL) return;

  int swapped;
  struct list *ptr1;
  struct list *lptr = NULL;

  do {
    swapped = 0;
    ptr1 = head;

    while (ptr1->next != lptr) {
      if (strcmp(ptr1->word, ptr1->next->word) > 0) {
        swap_elements(ptr1, ptr1->next);
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}

void print_list(struct list *head) {
  struct list *current = head;
  while (current != NULL) {
    printf("%s", current->word);
    if (current->next != NULL) {
      printf(" ");
    }
    current = current->next;
  }
  printf("\n");
}

void delete_list(struct list *head) {
  struct list *current = head;
  while (current != NULL) {
    struct list *temp = current;
    current = current->next;
    free(temp);
  }
}

int main() {
  char input[1000];
  struct list *head = NULL;

  fgets(input, sizeof(input), stdin);

  char *dot_pos = strchr(input, '.');
  if (dot_pos != NULL) {
    *dot_pos = '\0';
  }

  char *token = strtok(input, " \n");
  while (token != NULL) {
    head = add_to_list(head, token);
    token = strtok(NULL, " \n");
  }

  sort_list(head);
  print_list(head);
  delete_list(head);

  return 0;
}