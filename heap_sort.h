#ifndef HEAPSORT_LIBH
#define HEAPSORT_LIBH

#ifdef __cplusplus
extern "C" {
#endif

  // Turn binary tree rooted at a[start] into a max-heap, assuming
  // that the left and right subtrees of a[start] are already
  // max-heaps. Loop implementation
  void maxHeapify(int a[], int start, int size);

  // Turn array a into a max-heap.
  void buildMaxHeap(int a[], int size);

  // Take a guess.
  void heapSort(int a[], int size);

  // Recursive implementation.
  void maxHeapifyRec(int a[], int start, int size);

#ifdef __cplusplus
}
#endif

#endif
