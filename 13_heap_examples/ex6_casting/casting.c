/*
 * casting.c
 */

int main ()
{
  int myint;
  short int myshort;
  unsigned char uchar;

  float myfloat;
  double mydouble;

  myint = 30456;
  myshort = (short int) myint;
  uchar = (unsigned char) myint;


  mydouble = 3.14159;

  myfloat = (float) mydouble;


  return 0;
}
