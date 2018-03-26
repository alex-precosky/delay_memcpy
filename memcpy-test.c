#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "delaymemcpy.h"

#define MAX_ARRAY_SIZE 0x20000000 // 2^30=1GB

/* Arrays declared as global, as this allows program to use more
   memory. Aligned to page boundaries so other global variables don't
   end up in same page. */
unsigned char __attribute__ ((aligned (0x1000))) array[MAX_ARRAY_SIZE];
unsigned char __attribute__ ((aligned (0x1000))) copy[MAX_ARRAY_SIZE];
unsigned char __attribute__ ((aligned (0x1000))) copy2[MAX_ARRAY_SIZE];

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

  printf("array: 0x%x\n", array);
  printf("copy: 0x%x\n", copy);
  printf("copy2: 0x%x\n", copy2);

  /* printf("\nTest Case 1\n"); */
  /* printf("\nCopying one page of data, trigger copy via read dst...\n"); */
  /* random_array(array, 0x1000); */

  /* printf("Before copy: "); */
  /* print_array(array, 20); */
  
  /* delay_memcpy(copy, array, 0x1000); */
  /* printf("After copy : "); */
  /* print_array(array, 20); // Should not trigger copy */
  /* printf("Destination: "); */
  /* print_array(copy, 20);  // Triggers copy */
  
  /* printf("\nTest Case 2\n"); */
  /* printf("\nCopying one page of data, trigger copy via write dst...\n"); */
  /* random_array(array, 0x1000); */
  /* printf("Before copy: "); */
  /* print_array(array, 20); */
  
  /* delay_memcpy(copy, array, 0x1000); */
  /* copy[0]++; // Triggers copy */
  /* printf("After copy : "); */
  /* print_array(array, 20); */
  /* printf("Destination: "); */
  /* print_array(copy, 20); */
  
  /* printf("\nTest Case 3\n"); */
  /* printf("\nCopying one page of data, trigger copy via write src...\n"); */
  /* random_array(array, 0x1000); */
  /* printf("Before copy: "); */
  /* print_array(array, 20); */
  
  /* delay_memcpy(copy, array, 0x1000); */
  /* array[0]++; // Triggers copy */
  /* printf("After copy : "); */
  /* print_array(array, 20); */
  /* printf("Destination: "); */
  /* print_array(copy, 20); */


  /* printf("\nTest Case 4\n"); */
  /* printf("\nCopying two pages of data...\n"); */
  /* random_array(array, 0x2000); */
  /* printf("Before copy: "); */
  /* print_array(array, 20); */
 
  /* delay_memcpy(copy, array, 0x2000); */
  /* printf("After copy : "); */
  /* print_array(array, 20); */
  /* printf("Destination: "); */
  /* print_array(copy, 20);  // Triggers copy of first page only */
  /* printf("2nd page:\nAfter copy : "); */
  /* print_array(array + 0x1800, 20); */
  /* printf("Destination: "); */
  /* print_array(copy + 0x1800, 20);  // Triggers copy of second page */


  /* printf("\nTest Case 4. Copy unaligned two pages, access first page\n"); */
  /* printf("\nCopying unaligned page of data...\n"); */

  /* random_array(array, 0x2000); */
  /* printf("Before copy: "); */
  /* print_array(array + 0x400, 20); */
  
  /* delay_memcpy(copy + 0x400, array + 0x400, 0x1000); */
  /* printf("After copy : "); */
  /* print_array(array + 0x400, 20); */
  /* printf("Destination: "); */
  /* print_array(copy + 0x400, 20);  // Triggers copy of first page only */

  /* MORE TESTS COME HERE */
  /* random_array(array, 0x2000); */
  /* printf("\nTest Case 5. Copy unaligned two pages, access second page\n"); */
  /* printf("\nCopying unaligned page of data...\n"); */
  /* reset_pending_copy_slots(); */
  /* printf("Before copy: "); */
  /* print_array(array + 0x1300, 20); */
  
  /* delay_memcpy(copy + 0x400, array + 0x400, 0x1000); */
  /* printf("After copy : "); */
  /* print_array(array + 0x1300, 20); */
  /* printf("Destination: "); */
  /* print_array(copy + 0x1300, 20);  // Triggers copy of second page only */


  /* printf("\nTest Case 6. Copy a subset of one page all contained within one page\n"); */
  /* printf("\nCopying one page of data, trigger copy via write dst...\n"); */
  /* random_array(array, 0x1000); */
  /* printf("Before copy: "); */
  /* print_array(array+400, 20); */
  
  /* delay_memcpy(copy+400, array+400, 0x200); */
  /* copy[0]++; // Triggers copy */
  /* printf("After copy : "); */
  /* print_array(array+400, 20); */
  /* printf("Destination: "); */
  /* print_array(copy+400, 20); */


  printf("\nTest Case 7. Copy three pages, then access the middle destination page\n");
  random_array(array, 0x3000);
  printf("Before copy: ");
  print_array(array+0x1000, 20);
  
  delay_memcpy(copy, array, 0x3000);
  copy[0x1000]++; // Triggers copy
  printf("After copy : ");
  print_array(array+0x1000, 20);
  printf("Destination: ");
  print_array(copy+0x1000, 20);



/*  printf("\nDereferencing a null pointer\n");
  void* null_ptr = 0x0;
  print_array(null_ptr, 1);
*/

  /* printf("\nCopying A to B to C\n"); */
  /* random_array(array, 0x1000); */
  /* printf("Before copy: "); */
  /* print_array(array, 20); */
  /* delay_memcpy(copy, array, 0x1000); */
  /* delay_memcpy(copy2, copy, 0x1000); */
  /* printf("Destination C :"); */
  /* print_array(copy2, 20);  // should trigger two copies */
  /* printf("Destination B :"); */
  /* print_array(copy, 20); */

  /* printf("\nCopying A to B to C\n"); */
  /* random_array(array, 0x1000); */
  /* printf("Before copy: "); */
  /* print_array(array, 20); */
  /* delay_memcpy(copy, array, 0x1000); */
  /* delay_memcpy(copy2, copy, 0x1000); */
  /* copy[0]++; */
  /* printf("Destination B :"); */
  /* print_array(copy, 20); */
  /* printf("Destination C :"); */
  /* print_array(copy2, 20); */

}

