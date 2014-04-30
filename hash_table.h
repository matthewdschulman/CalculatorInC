/* lined list node definition will store commands */
typedef struct command_struct {
    char *instruction ;
    struct command_struct *next ;
} command ;

/* hash table that will store "people" */
typedef struct hash_table_struct {
    int num_of_buckets ;        /* the size of the table */
    command **table ;  			/* table points to an array of pointers to commands */
} command_table ;

typedef struct struct_of_ints {
	int value ;
	struct struct_of_ints *next ;
} intStack ; 

/* helper functions to manage hashtable */
command_table*  create_hash_table (int size) ;
unsigned int   map               (command_table *hashtable, command *prsn) ;
command*        find     		 (command_table *hashtable, command *prsn) ;
int            add               (command_table *hashtable, command *prsn) ;
void           delete_table      (command_table *hashtable) ;
void           print_table       (command_table *hashtable) ;