#include "ex_linked_list.h"

/* Hash table for struct_of_ints type */
typedef struct hash_table_struct {
    int num_of_buckets ;        /* the size of the table */
    struct_of_ints **table ;  	/* the actual hash table: points to an array of pointers to struct_of_ints */
    							/* behaves like a 2D array */

} hash_table ;


hash_table*    create_hash_table (int size) ;
unsigned int   map               (hash_table *hashtable, int value) ;
struct_of_ints*find     		 (hash_table *hashtable, int value) ;
int            add               (hash_table *hashtable, int value) ;
void           delete_table      (hash_table *hashtable) ;
void           print_table       (hash_table *hashtable) ;

