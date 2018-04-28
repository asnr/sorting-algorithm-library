#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "red_black_tree_sort.h"

enum Colour {
  RED,
  BLACK
};

struct RedBlackTree {
  int data;
  enum Colour colour;
  struct RedBlackTree *parent, *left, *right;
};

bool isRoot(struct RedBlackTree *tree) {
  return tree->parent == NULL;
}

bool isBlack(struct RedBlackTree *tree) {
  return tree == NULL || tree->colour == BLACK;
}

bool isRed(struct RedBlackTree *tree) {
  return !isBlack(tree);
}

bool isLeftChild(struct RedBlackTree *node, struct RedBlackTree *parent)
{
  return parent->left == node;
}

struct RedBlackTree* siblingOf(struct RedBlackTree *node, struct RedBlackTree *parent)
{
  return parent->left == node ? parent->right : parent->left;
}

struct RedBlackTree* allocateLeaf(int data, enum Colour colour, struct RedBlackTree *parent)
{
  struct RedBlackTree *leaf = malloc(sizeof (struct RedBlackTree));
  if (leaf == NULL) {
    printf("malloc error allocating leaf %d\n", data);
    exit(1);
  }
  leaf->data = data;
  leaf->colour = colour;
  leaf->parent = parent;
  leaf->left = NULL;
  leaf->right = NULL;
  return leaf;
}

// Precondition: node and parent are red, grandparent and aunt are black.
void rotate(struct RedBlackTree *node, struct RedBlackTree *parent, struct RedBlackTree **grandparent)
{
  struct RedBlackTree *oldGrandparent = *grandparent;
  struct RedBlackTree *newGrandparent;
  if (isLeftChild(parent, *grandparent)) {
    if (isLeftChild(node, parent)) {
      newGrandparent = parent;
      struct RedBlackTree *sibling = parent->right;
      newGrandparent->right = *grandparent;
      newGrandparent->colour = BLACK;
      oldGrandparent->left = sibling;
      oldGrandparent->colour = RED;
    } else {
      newGrandparent = node;
      newGrandparent->left = parent;
      newGrandparent->right = oldGrandparent;
      newGrandparent->colour = BLACK;
      parent->right = NULL;
      oldGrandparent->left = NULL;
      oldGrandparent->colour = RED;
    }
  } else {
    if (isLeftChild(node, parent)) {
      newGrandparent = node;
      newGrandparent->left = oldGrandparent;
      newGrandparent->right = parent;
      newGrandparent->colour = BLACK;
      parent->left = NULL;
      oldGrandparent->right = NULL;
      oldGrandparent->colour = RED;
    } else {
      newGrandparent = parent;
      struct RedBlackTree *sibling = parent->left;
      newGrandparent->left = oldGrandparent;
      newGrandparent->colour = BLACK;
      oldGrandparent->right = sibling;
      oldGrandparent->colour = RED;
    }
  }
  *grandparent = newGrandparent;
}

// Precondition: node and sibling are red, parent is black
void recolour(struct RedBlackTree *node)
{
  struct RedBlackTree *parent = node->parent;
  struct RedBlackTree *sibling = siblingOf(node, parent);
  node->colour = BLACK;
  sibling->colour = BLACK;
  if (!isRoot(parent)) {
    parent->colour = RED;
    struct RedBlackTree *grandparent = parent->parent;
    if (isRed(grandparent)) {
      recolour(grandparent);
    }
  }
}

void insert(struct RedBlackTree **tree, int elt)
{
  if (*tree == NULL) {
    *tree = allocateLeaf(elt, BLACK, NULL);
    return;
  }

  struct RedBlackTree *node = *tree;
  struct RedBlackTree *parent = NULL;
  struct RedBlackTree *grandparent = NULL;
  struct RedBlackTree **parentBranch = NULL;
  while (node != NULL) {
    if (elt <= node->data) {
      parentBranch = &(node->left);
    } else {
      parentBranch = &(node->right);
    }
    grandparent = parent;
    parent = node;
    node = *parentBranch;
  }

  *parentBranch = allocateLeaf(elt, RED, parent);

  if (isRed(parent)) {
    struct RedBlackTree *aunt = siblingOf(parent, grandparent);
    if (isBlack(aunt)) {
      rotate(node, parent, grandparent);
    } else {
      recolour(node);
    }
  }
}

static int toArray(struct RedBlackTree *tree, int a[], int nextIdx)
{
  if (tree == NULL) {
    return nextIdx;
  }

  nextIdx = toArray(tree->left, a, nextIdx);
  a[nextIdx] = tree->data;
  nextIdx++;
  nextIdx = toArray(tree->right, a, nextIdx);
  return nextIdx;
}

void redBlackTreeSort(int a[], int size)
{
  struct RedBlackTree *tree = NULL;
  for (int idx = 0; idx < size; idx++) {
    insert(&tree, a[idx]);
  }
  toArray(tree, a, 0);
}
