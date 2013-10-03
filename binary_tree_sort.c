#include <stdlib.h>
#include <stdio.h>

#include "binary_tree_sort.h"

struct BinTree {
  int data;
  struct BinTree *left, *right;
};


void addElt(int elt, struct BinTree** tree)
{
  // Find where elt fits
  while (*tree != NULL) {
    if ((*tree)->data <= elt)
      // elt is bigger than node data, send it to the right
      tree = &( (*tree)->right );
    else
      tree = &( (*tree)->left );
  }

  // Insert elt
  *tree = malloc(sizeof **tree);
  if (*tree == NULL) {
    printf("malloc error inserting elt %d\n", elt);
    exit(1);
  }
  (*tree)->data  = elt;
  (*tree)->left  = NULL;
  (*tree)->right = NULL;
}

struct BinTree* makeTree(int contents[], int size)
{
  int i;
  struct BinTree *tree = NULL;

  for (i = 0; i < size; i++)
    addElt(contents[i], &tree);

  return tree;
}

// Flattens the binary tree. Recursive implementation
void toArray(struct BinTree *tree, int a[], int* size)
{
  if (tree != NULL) {
    toArray(tree->left, a, size);
    a[(*size)] = tree->data;
    (*size)++;
    toArray(tree->right, a, size);
  } 
}

void binaryTreeSort(int a[], int size)
{
  struct BinTree *tree = makeTree(a, size);
  
  size = 0;
  toArray(tree, a, &size);
}

void freeTree(struct BinTree** tree)
{
  if (*tree != NULL) {
    freeTree( &( (*tree)->left ) );
    freeTree( &( (*tree)->right ) );
    free(*tree);
    *tree = NULL;
  }
}

// Helper functions for elaboratePrintTree
int treeDepth(const struct BinTree* tree)
{
  int ret = 0;
  int depthLeft, depthRight;
  if (tree != NULL) {
    depthLeft = treeDepth(tree->left);
    depthRight = treeDepth(tree->right);
    if (depthLeft < depthRight)
      ret = depthRight + 1;
    else
      ret = depthLeft + 1;
  }
  return ret;
}

void printRepeatChar(int reps, char c)
{
  int i;
  for (i = 0; i < reps; i++)
    printf("%c", c);
}

void printTreeNode(const struct BinTree* node)
{
  if (node == NULL)
    printf("N");
  else
    printf("%d", node->data);
}

void elaboratePrintTree(const struct BinTree* tree)
{
  int depth, border, i, j;
  const struct BinTree **level;
  
  depth = treeDepth(tree);
  level = malloc( 2^depth * sizeof(*level) );
  if (level == NULL) {
    printf("malloc fail in elaboratePrintTree\n");
    exit(1);
  }

  level[0] = tree;

  for (i = 0; i < depth; i++) {
    // set up this level
    for (j = ((1<<i)>>1)-1; j >= 0; j--) {
      if (level[j] == NULL)
    	level[j*2 + 1] = level[j*2] = NULL;
      else {
    	level[j*2 + 1] = (level[j])->right;
    	level[j*2]     = (level[j])->left;
      }
    }

    // print left border
    border = ((1<<(depth-i))>>1) - 1;
    printRepeatChar(border, ' ');
    
    // print nodes of level i
    printTreeNode(level[0]);
    for (j = 1; j < 1<<i; j++) {
      printRepeatChar( (1<<(depth-i)) - 1, ' ');
      printTreeNode(level[j]);
    }

    // Print right border
    printRepeatChar(border, ' ');
    printf("\n");
  }
}
