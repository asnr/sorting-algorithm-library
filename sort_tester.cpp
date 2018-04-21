/*

  Test bed for sort functions.
  
  Takes one argument, which determines which sort function will be tested.

  Input is the file "in" of sequences of integers. (See below for format of
  input file.)
  
  Correctness of library sort functions is tested by comparing with the standard
  template sort function. Output is to the console; no output => sort function
  agrees with STL sort function.

*/

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

extern "C"{
#include "heap_sort.h"
#include "sort_lib.h"
#include "binary_tree_sort.h"
}

// Maximum size of the array to be sorted
const int MAX_SIZE = 1000;

char mergeSortOption[]     = "merge"; // Default option
char insertionSortOption[] = "insertion";
char quickSortOption[]     = "quick";
char heapSortOption[]      = "heap";
char binaryTreeOption[]    = "binaryTree";

// Prints array a to standard out.
void printArray(int a[], int size);

// check returns a boolean: true if the arrays are equal up to and including
// index [size - 1], 0 otherwise.
// Arrays a and b must be at least size in length
bool check(int a[], int b[], int size);


// Takes one argument, which selects which sorting algorithm will be tested.
int main ( int argc, char *argv[] )
{
  int i, j, size, numArrays;
  int a[MAX_SIZE], b[MAX_SIZE];
  
  void (*sortFunction)(int*, int);
  
  // Select the sort function that will be tested
  if (argc <= 1)
    sortFunction = &mergeSort;
  else if (!strcmp(argv[1], mergeSortOption))
    sortFunction = &mergeSort;
  else if (!strcmp(argv[1], insertionSortOption))
    sortFunction = &insertionSort;
  else if (!strcmp(argv[1], quickSortOption))
    sortFunction = &quickSort;
  else if (!strcmp(argv[1], heapSortOption))
    sortFunction = &heapSort;
  else if (!strcmp(argv[1], heapSortOption))
    sortFunction = &binaryTreeSort;
  else
    sortFunction = &mergeSort;
    

  /* Input is a sequence of integer arrays. The first line of "in" should be
  the number n of arrays it contains, followed by n pairs of lines. The first
  of each pair is a single number k_i and the second is a sequence of k_i
  space-separated integers. */
  FILE *input = fopen("in", "r");

  fscanf(input, "%d", &numArrays);

  for (i = 0; i < numArrays; i++) { // for each array in input

    // get ith array
    fscanf(input, "%d", &size);
    for (j = 0; j < size; j++) {
      fscanf(input, "%d", a+j);
      b[j] = a[j];
    }
    // sort ith array
    (*sortFunction)(a, size);
    std::sort(b, b+size);
    // check correctness
    if (!check(a, b, size)) {
      printf("Array %d not properly sorted:\n", i+1);
      printArray(a,size);
      printArray(b,size);
    }
  }
    
  fclose(input);
  return 0; 
}

void printArray(int a[], int size)
{
  int i;
  for (i = 0; i < size; i++)
    printf("%d ", a[i]);
  printf("\n");
}

bool check(int a[], int b[], int size)
{
  bool check = true;

  for (int i = 0; i < size; i++)
    if(a[i] != b[i])
      check = false;

  return check;
}
