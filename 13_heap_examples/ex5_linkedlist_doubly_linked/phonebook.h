/*
 * phonebook.h : Declares functions used to implement a simple address book
 */

typedef struct list_elt_tag {
  char *name;
  int number;  
  struct list_elt_tag *prev, *next; // Pointers to the previous and next elements in the list
} list_elt;

list_elt *lookup (list_elt *first_elt, char *name);
list_elt *push (list_elt *first_elt, char *name, int number);
list_elt *delete (list_elt *first_elt, list_elt *elt);
