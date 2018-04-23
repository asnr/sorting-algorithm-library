#ifndef BINTREESORT_LIBH
#define BINTREESORT_LIBH

#ifdef __cplusplus
extern "C" {
#endif

// Binary tree that holds integers and sends equal nodes to the right
struct BinTree;

void addElt(int elt, struct BinTree** tree);

struct BinTree* makeTree(int contents[], int size);

void binaryTreeSort(int a[], int size);

void freeTree(struct BinTree** tree);

// Width is exponential in depth, so only for use with small trees. Really only
// works when all entries are single digits.
void elaboratePrintTree(const struct BinTree* tree);

void printTreeNode(const struct BinTree* node);

#ifdef __cplusplus
}
#endif

#endif
