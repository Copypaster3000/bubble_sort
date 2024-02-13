//bsort3.c
//A string version
//Assignment one
//Drake Wheeler
//CS299

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Swap two int array elements
//
void swap(int* a, int i, int j)
{
  if (i != j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }
}

// Print an int array of size n
//
void printArray(int* array, int n)
{
  for (int i = 0; i < n; ++i) //Loops for size of array
  {
    //Unpacks chars stored in element of int* array, stores them in variables
    char first = (char)(array[i] >> 16);
    char second = (char)(array[i] >> 8);
    char third = (char)array[i];
    printf("%c%c%c ", first, second, third); //Prints chars stored in current array element
  }
  printf("\n");

  return;
}

// Bubble sort a range [low,high) of an int array
//
void bsort(int* a, int low, int high)
{
  if (high - low > 1) 
    for (int i = low; i < high; i++)
      for (int j = i+1; j < high; j++) 
      {
        //Store the chars of each string being compared in a variable 
        int char1_i = (a[i] >> 16) & 0xFF;
        int char2_i = (a[i] >> 8) & 0xFF;
        int char3_i = a[i] & 0xFF;
        int char1_j = (a[j] >> 16) & 0xFF;
        int char2_j = (a[j] >> 8) & 0xFF;
        int char3_j = a[j] & 0xFF;

        //If i string comes before j string alphabetically, it swaps them
        if(char1_i > char1_j || (char1_i == char1_j && char2_i > char2_j) ||(char1_i == char1_j && char2_i == char2_j && char3_i > char3_j)) 
          swap(a, i, j);
      }
  return;
}

//Gets the size of the array from the user and returns it
int get_array_size(void)
{
  int size;

  printf("Enter the size of the array you would like randomly generated and then sorted: ");

  scanf("%d", &size);


  return size;
}

//Creates an array of size size and fills it with random strings of 3 chars
int* create_array(int size)
{
  int* array = malloc(size * sizeof(int)); //allocate memory for array of pointer to char arrays

  for(int i = 0; i < size; ++i) //Loops through each pointer in array of pointers
  {
    array[i] = pack_chars();
  }

  return array;   
}


int pack_chars(void)
{
  //Generate three random lowercase letters
  unsigned char a = 'a' + (rand() % 26);
  unsigned char b = 'a' + (rand() % 26);
  unsigned char c = 'a' + (rand() % 26);

  return (a<<16) | (b<<8) | c; //Pack the chars into an int

}

// Test the bsort() routine
// 
int main()
{
  int* array;
  int size;
  srand(time(NULL)); //seed random number generator

  size = get_array_size();
  
  if(size < 1) //Exits program if array is not a positive integer
  {
    printf("Array size must be greater than 0.\nProgram ended.\n");
    return 0;
  }

  array = create_array(size);

  printf("Pre sort: ");
  printArray(array, size);
  bsort(array, 0, size);
  printf("Post sort: ");
  printArray(array, size);

  return 0;
}
