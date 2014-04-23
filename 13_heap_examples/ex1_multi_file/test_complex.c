/*
 * test_complex.c : Test the routines defined in complex.c
 */

#include <stdio.h>
#include "complex.h"




void print_complex (complex num1)
{
  printf (" %8.3f + %8.3f i ", num1.x, num1.y); 
}




int main (int argc, char **argv)
{
  complex a, b, c;
  complex c_array[5]; // Note that we can create arrays of structs very easily

  a.x = 3.0;  a.y = 4.0;
  b.x = 7.0;  b.y = -9.0;

  printf ("a = "); print_complex (a); printf ("\n\n");
  printf ("b = "); print_complex (b); printf ("\n\n");

  c = add (a, b);
  printf (" a + b = "); print_complex(c); printf ("\n");

  c = sub (a, b);
  printf (" a - b = "); print_complex(c); printf ("\n");

  c = mpy (a, b);
  printf (" a * b = "); print_complex(c); printf ("\n");

  c = div (a, b);
  printf (" a / b = "); print_complex(c); printf ("\n");
}
