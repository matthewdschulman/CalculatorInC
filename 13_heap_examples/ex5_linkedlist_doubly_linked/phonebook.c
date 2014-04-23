/*
 * phonebook.c
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "phonebook.h"

/* 
 * lookup - finds a person by name in the list, returns NULL if not found
 */

list_elt *lookup (list_elt *first_elt, char *name)
{
  list_elt *elt = first_elt;

  // Iterate down the linked list
  while (elt != NULL) {
    // Compare the name using strcmp
    if (strcmp (name, elt->name) == 0)
      return elt;
    elt = elt->next;
  }

  /* If you didn't find it return NULL */
  return NULL;
}

/* 
 * Creates a new list element and pushes it on the front of the list
 * returns a pointer to the newly created element.
 */

list_elt *push (list_elt *first_elt, char *name, int number)
{
  list_elt *elt;

  // Allocate a new list element with malloc
  elt = malloc (sizeof(*elt));


  // If malloc fails end the program
  if (elt == NULL) {
    printf ("Couldn't allocate a new list element\n");
    exit (1);
  }

  // Allocate space to store the name
  elt->name = malloc(strlen(name) + 1);

  // If malloc fails end the program
  if (elt->name == NULL) {
    printf ("Couldn't allocate a new name\n");
    exit (1);
  }

  // Copy the name
  strcpy (elt->name, name);

  elt->number = number;
  
  elt->prev = NULL;
  elt->next = first_elt;

  if (first_elt != NULL)
    first_elt->prev = elt;

  // return the pointer to the new list_elt
  return elt;
}

/*
 * delete : Deletes an element from the list returns a pointer to the new
 * first element of the list which may just be the old first element.
 */

list_elt *delete (list_elt *first_elt, list_elt *elt)
{
  list_elt *prev, *next;

  if (elt == NULL || first_elt == NULL) return first_elt;

  prev = elt->prev;
  next = elt->next;

  /* First we fix the pointers of the next and previous elements */
  if (prev)
    prev->next = elt->next;

  if (next)
    next->prev = elt->prev;

  // Free the space we allocated for the name
  free (elt->name);

  // Free the space we allocated for the list element
  free (elt);

  // Check if elt was the first element in the list
  if (elt == first_elt)
    return next;
  else
    return first_elt;
}
