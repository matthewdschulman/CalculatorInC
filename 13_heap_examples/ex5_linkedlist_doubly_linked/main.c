/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phonebook.h"

#define MAX_LINE_LENGTH 200

void print_list (list_elt *first_elt)
{
  list_elt *elt = first_elt;

  while (elt) {
    printf ("%s : %d\n", elt->name, elt->number);
    elt = elt->next;
  }
}

int main ()
{
  char input[MAX_LINE_LENGTH];
  char name[MAX_LINE_LENGTH];
  int number;
  list_elt *first_elt = NULL;

  while (1) {
    printf ("Enter command (add name number, delete name, list, quit) : \n");

    fgets (input, MAX_LINE_LENGTH, stdin);

    // Check for add command
    if (sscanf (input, "add %s %d", name, &number) == 2) {
      if (lookup (first_elt, name) == NULL) {
	first_elt = push (first_elt, name, number);
      } else {
	printf ("That name is already in the list\n");
      }
    }

    // Check for delete command
    if (sscanf (input, "delete %s", name) == 1) {
      first_elt = delete (first_elt, lookup (first_elt, name));
    }

    // Check for list command
    if (input[0] == 'l') {
      print_list (first_elt);
    }

    // check for quit command
    if (input[0] == 'q') {
      while (first_elt) {
	first_elt = delete (first_elt, first_elt);
      }

      exit (0);
    }

  }

  return 0;
}
