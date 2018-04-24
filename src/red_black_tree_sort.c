#include <stdlib.h>
#include <stdio.h>

#include "red_black_tree_sort.h"

enum Colour {
  RED,
  BLACK
};

struct RedBlackTree {
  int data;
  enum Colour colour;
  struct RedBlackTree *left, *right;
};

void insert(struct RedBlackTree **tree, int elt) {
  if (*tree == NULL) {
    *tree = malloc(sizeof **tree);
    if (*tree == NULL) {
      printf("malloc error inserting elt %d\n", elt);
      exit(1);
    }
    (*tree)->data = elt;
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    (*tree)->colour = BLACK;
  }

  /* struct RedBlackTree **node = tree; */
  /* struct RedBlackTree **prevNode = tree; */
  /* while (*node != NULL) { */
  /*   if () */
  /* } */
}

static int toArray(struct RedBlackTree *tree, int a[], int nextIdx) {
  if (tree == NULL) {
    return nextIdx;
  }

  nextIdx = toArray(tree->left, a, nextIdx);
  a[nextIdx] = tree->data;
  nextIdx++;
  nextIdx = toArray(tree->right, a, nextIdx);
  return nextIdx;
}

void redBlackTreeSort(int a[], int size) {
  struct RedBlackTree *tree = NULL;
  for (int idx = 0; idx < size; idx++) {
    insert(&tree, a[idx]);
  }
  toArray(tree, a, 0);
}
