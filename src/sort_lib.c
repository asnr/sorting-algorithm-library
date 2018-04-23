#include<stdlib.h>
#include<string.h>

#include "sort_lib.h"

// merge sort - second argument is a temporary storage array
// that must be at least size in length. Without this extra array,
// we would have to make O(size) calls to malloc/free.
// Should profile this to see what difference it makes.
void mSort(int a[], int temp[], int size);

void insertionSort(int a[], int size)
{
  int i, j, temp;

  for (i = 1; i < size; i++) {
    temp = a[i];
    j = i-1;

    while (j >= 0 && a[j] > temp) {
      a[j+1] = a[j];
      j--;
    }

    a[j+1] = temp;
  }

}

void mergeSort(int a[], int size)
{
  int* temp = malloc(size * sizeof(*temp));
  if (temp == NULL) exit(1);

  mSort(a, temp, size);
  free(temp);
}

void mSort(int a[], int temp[], int size)
{
  int sizeFirstHalf, i, j, k;

  if (size > 1) {
    sizeFirstHalf = size/2;

    // sort both halves
    mSort(a, temp, size/2);
    mSort(&a[sizeFirstHalf], temp, size - size/2);

    // merge the sorted halves
    i = 0; j = sizeFirstHalf;
    for (k = 0; k < size; k++) {
      if (i >= sizeFirstHalf) {
	temp[k] = a[j];
	j++;
      } else if (j >= size) {
	temp[k] = a[i];
	i++;
      } else if (a[i] <= a[j]) {
	temp[k] = a[i];
	i++;
      } else { // a[j] < a[j]
	temp[k] = a[j];
	j++;
      }
    }

    // copy merged array back to a[]
    memcpy(a, temp, size*(sizeof(*temp)));
  }
}

// Here we partition around the last elt., ie. a[size - 1]
int partition(int a[], int size)
{
  int leftIdx, pivot;
  int i, temp;

  leftIdx = 0;
  pivot   = a[size - 1];
  for (i = 0; i < size - 1; i++) {
    if (a[i] < pivot) {
      // Swap a[i] and a[leftIdx]
      temp       = a[leftIdx];
      a[leftIdx] = a[i];
      a[i]       = temp;
      leftIdx++;
    }
  }

  // Swap a[leftIdx] and a[size - 1]
  a[size - 1] = a[leftIdx];
  a[leftIdx]  = pivot;

  return leftIdx;
}

void quickSort(int a[], int size)
{
  int pivotIdx;

  if (size > 1) {
    pivotIdx = partition(a, size);
    quickSort(a, pivotIdx);
    quickSort(a + pivotIdx + 1, size - pivotIdx - 1);
  }
}
