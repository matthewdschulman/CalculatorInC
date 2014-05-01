/* lined list node definition will store commands */
typedef struct command_struct {
    char *instruction ;
    struct command_struct *next ;
} command ;

/* hash table that will store "commands" */
typedef struct hash_table_struct {
    int num_of_buckets ;        /* the size of the table */
    command **table ;  			/* table points to an array of pointers to commands */
} command_table ;

typedef struct struct_of_ints {
	int value ;
	struct struct_of_ints *next ;
} intStack ; 

//mappingfor Labels
typedef struct label_mapping_struct {
	char *label;
	int value; //this will be the location of the label in the command hash table
	struct label_mapping_struct *next;
} label_mapping ;

typedef struct hash_table_of_labels {
	int num_of_buckets ;        /* the size of the table */
    label_mapping **table ;  	/* table points to an array of pointers to label mappings */
} label_table ;

/* helper functions to manage hashtable */
command_table*  create_hash_table (int size) ;
unsigned int   mapCommand               (command_table *hashtable, command *prsn) ;
unsigned int   mapLabel               (label_table *hashtable, label_mapping *label) ;
command*        findCommand     		 (command_table *hashtable, command *prsn) ;
label_mapping*  findLabel (label_table *hashtable, label_mapping *label);
int            addCommand               (command_table *hashtable, command *prsn) ;
int addLabel (label_table *hashtable, label_mapping *label);
void           delete_table      (command_table *hashtable) ;
