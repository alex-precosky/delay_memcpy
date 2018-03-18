#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "delaymemcpy.h"

#define MAX_ARRAY_SIZE 0x10000000 // 2^30=1GB

/* Arrays declared as global, as this allows program to use more
   memory. Aligned to page boundaries so other global variables don't
   end up in same page. */
unsigned char __attribute__ ((aligned (0x1000))) array[MAX_ARRAY_SIZE];
unsigned char __attribute__ ((aligned (0x1000))) copy[MAX_ARRAY_SIZE];

/* Initializes the array with a random set of values. */
void *random_array(void *array, size_t size) {
  
  int i;
  size /= sizeof(long);
  for (i = 0; i < size; i++)
    ((long *)array)[i] = random();
  
  return array;
}

/* Prints all values of the array */
void print_array(unsigned char *array, int size) {
  int i;
  for (i = 0; i < size; i++)
    printf("%02x ", array[i]);
  printf("\n");
}

int main(void) {
  srandom(time(NULL));

  initialize_delay_memcpy_data();
  /*
  printf("\nCopying one page of data, trigger copy via read dst...\n");*/
  random_array(array, 0x1000);
/*
  printf("Before copy: ");
  print_array(array, 20);
  
  delay_memcpy(copy, array, 0x1000);
  printf("After copy : ");
  print_array(array, 20); // Should not trigger copy
  printf("Destination: ");
  print_array(copy, 20);  // Triggers copy
  
  printf("\nCopying one page of data, trigger copy via write dst...\n");
  random_array(array, 0x1000);
  printf("Before copy: ");
  print_array(array, 20);
  
  delay_memcpy(copy, array, 0x1000);
  copy[0]++; // Triggers copy
  printf("After copy : ");
  print_array(array, 20);
  printf("Destination: ");
  print_array(copy, 20);
  
  printf("\nCopying one page of data, trigger copy via write src...\n");
  random_array(array, 0x1000);
  printf("Before copy: ");
  print_array(array, 20);
  
  delay_memcpy(copy, array, 0x1000);
  array[0]++; // Triggers copy
  printf("After copy : ");
  print_array(array, 20);
  printf("Destination: ");
  print_array(copy, 20);
  
  printf("\nCopying two pages of data...\n");
  random_array(array, 0x2000);
  printf("Before copy: ");
  print_array(array, 20);
*/

  random_array(array, 0x2000);
  delay_memcpy(copy, array, 0x2000);
  printf("After copy : ");
  print_array(array, 20);
  printf("Destination: ");
  print_array(copy, 20);  // Triggers copy of first page only
  printf("2nd page:\nAfter copy : ");
  print_array(array + 0x1800, 20);
  printf("Destination: ");
  print_array(copy + 0x1800, 20);  // Triggers copy of second page
  
  printf("\nCopying unaligned page of data...\n");
  random_array(array, 0x2000);
  printf("Before copy: ");
  print_array(array + 0x400, 20);
  
  delay_memcpy(copy + 0x400, array + 0x400, 0x1000);
  printf("After copy : ");
  print_array(array + 0x400, 20);
  printf("Destination: ");
  print_array(copy + 0x400, 20);  // Triggers copy of first page only

  /* MORE TESTS COME HERE */
  
  return 0;
}
