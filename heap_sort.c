// Both assume that the topmost elt of the binary tree
// has index 0.
int left(int i)
{
  return(2*i+1);
}

int right(int i)
{
  return(2*i+2);
}

// Loop implementation. Superior, like elder siblings.
void maxHeapify(int a[], int start, int size)
{
  int l, r, max, temp;
  l = left(start); r = right(start);

  while (l < size) {
    if (a[start] < a[l])
      max = l;
    else
      max = start;

    if(r < size && a[max] < a[r])
      max = r;

    if(max != start) {
      temp = a[start];
      a[start] = a[max];
      a[max] = temp;
      start = max;
      l = left(max);
      r = right(max);
    } else // our tree is already a max-heap. 
      l = size;

  } // end while
}

void buildMaxHeap(int a[], int size)
{
  int i;

  if (size > 1)
    // the last node (ie. not a leaf) has index (size/2)-1. 
    for (i = (size/2) - 1; i >= 0; i--)
      maxHeapify(a, i, size);
}

void heapSort(int a[], int size)
{
  int i, temp;

  buildMaxHeap(a, size);

  for (i = size - 1; i > 0; i--) {
    temp = a[i];
    a[i] = a[0];
    a[0] = temp;
    maxHeapify(a, 0, i);
  }
}

// Recursive implementation. Marvel at its ugliness. 
void maxHeapifyRec(int a[], int start, int size)
{
  int l, r, max, temp;
  l = left(start); r = right(start);

  if (l < size) {
    // Find which is biggest: a[start], a[l] or a[r]
    if (a[start] < a[l])
      max = l;
    else
      max = start;

    if (r < size && a[max] < a[r])
      max = r;

    if (max != start) {
      temp = a[start];
      a[start] = a[max];
      a[max] = temp;
      maxHeapifyRec(a, max, size);
    } // if max == start, then our tree is already a max-heap.  
  }// end if
}
