/*
 * complex.c
 */

#include "complex.h"

complex add (complex num1, complex num2)
{
  complex out;

  out.x = num1.x + num2.x;
  out.y = num1.y + num2.y;

  return out;
}

complex sub (complex num1, complex num2)
{
  complex out;

  out.x = num1.x - num2.x;
  out.y = num1.y - num2.y;

  return out;
}

complex mpy (complex num1, complex num2)
{
  complex out;

  out.x = (num1.x * num2.x) - (num1.y * num2.y);
  out.y = (num1.x * num2.y) + (num1.y * num2.x);

  return out;
}


complex div (complex num1, complex num2)
{
  return ( mpy (num1, invert (num2)) );
}

// Return the complex conjugate of an input
complex conjugate (complex num)
{
  complex out;
  
  out.x =  num.x;
  out.y = -num.y;

  return out;
}

// Return the inverse of a number ie 1/num
complex invert (complex num)
{
  complex out;
  double s = ((num.x*num.x) + (num.y*num.y));

  out.x = num.x/s;
  out.y = -(num.y/s);

  return out;
}
