/* lined list node definition will store "people" */
typedef struct person_struct {
    char *lname ;
    char *fname ;
    struct person_struct *next ;
} person ;

/* hash table that will store "people" */
typedef struct hash_table_struct {
    int num_of_buckets ;        /* the size of the table */
    person **table ;  			/* table points to an array of pointers to persons */

} person_table ;

/* helper functions to manage hashtable */
person_table*  create_hash_table (int size) ;
unsigned int   map               (person_table *hashtable, person *prsn) ;
person*        find     		 (person_table *hashtable, person *prsn) ;
int            add               (person_table *hashtable, person *prsn) ;
void           delete_table      (person_table *hashtable) ;
void           print_table       (person_table *hashtable) ;
