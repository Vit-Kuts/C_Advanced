void btUpView(tree *root) {
  if (root == NULL) return;

#define MAX_HD 1000
  int first[MAX_HD * 2 + 1];
  for (int i = 0; i < MAX_HD * 2 + 1; i++) {
    first[i] = -1;
  }

  struct queue_node {
    tree *node;
    int hd;
    struct queue_node *next;
  };

  struct queue_node *head = NULL, *tail = NULL;

  struct queue_node *first_node =
      (struct queue_node *)malloc(sizeof(struct queue_node));
  first_node->node = root;
  first_node->hd = 0;
  first_node->next = NULL;
  head = tail = first_node;

  int min_hd = 0, max_hd = 0;

  while (head != NULL) {
    tree *node = head->node;
    int hd = head->hd;

    if (first[hd + MAX_HD] == -1) {
      first[hd + MAX_HD] = node->key;
      if (hd < min_hd) min_hd = hd;
      if (hd > max_hd) max_hd = hd;
    }

    if (node->left != NULL) {
      struct queue_node *new_node =
          (struct queue_node *)malloc(sizeof(struct queue_node));
      new_node->node = node->left;
      new_node->hd = hd - 1;
      new_node->next = NULL;
      tail->next = new_node;
      tail = new_node;
    }

    if (node->right != NULL) {
      struct queue_node *new_node =
          (struct queue_node *)malloc(sizeof(struct queue_node));
      new_node->node = node->right;
      new_node->hd = hd + 1;
      new_node->next = NULL;
      tail->next = new_node;
      tail = new_node;
    }

    struct queue_node *temp = head;
    head = head->next;
    free(temp);
  }

  for (int i = min_hd; i <= max_hd; i++) {
    if (first[i + MAX_HD] != -1) {
      printf("%d", first[i + MAX_HD]);
      if (i < max_hd) printf(" ");
    }
  }
}