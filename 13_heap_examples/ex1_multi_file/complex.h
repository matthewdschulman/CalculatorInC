/*
 * complex.h : A header file defining some data structures and 
 *             routines for dealing with complex numbers
 */

/*
 * Here we define a new type called complex to represent complex numbers. 
 * This type has two fields called x and y
 * both of these are double precision numbers.
 * Note the use of typedef to define a new type called complex
 */

typedef struct {
  // represents the complex number x + iy
  double x, y;
} complex;

// Declare routines that perform arithmetic operations on complex numbers
// Note that in ANSI C functions can return structures, 
//  some older variants of C do not allow this.

complex add (complex num1, complex num2);
complex sub (complex num1, complex num2);
complex mpy (complex num1, complex num2);
complex div (complex num1, complex num2);
complex conjugate (complex num1);
complex invert (complex num1);
