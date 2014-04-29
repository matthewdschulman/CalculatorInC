#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#import <netinet/in.h>

int isNumeric (const char * s);
/*int pop (struct node **item, int *p);
void push(struct node** item, int data);*/

int main ( int argc, char *argv[] )
{

	//check that the user input is correct
    if ( argc != 2 ) /* argc should be 2 */
    {
    	//error...
    	printf("Error with the user input. Try again. Make sure to have one command line argument.");
    }

    else 
    {
    	struct struct_of_ints {
			int value ;
			struct struct_of_ints *next ;
		} ;

		// allocate 1 element list to represent the stack of calculator ints
		struct struct_of_ints *stackOfInts = 
			malloc (sizeof (struct struct_of_ints) ) ;

		char curStr[100];
        // Open up the user's selected input file
        FILE *file = fopen(argv[1], "r");

        if (file == 0)
        {
            printf("Could not open file\n");
        }
        else 
        {
            // read in strings
            while  ((fgets(curStr, 100, file)) != NULL )
            {
            	//truncate the curStr to remove spaces             	
				int i = 0;
				int j = strlen ( curStr ) - 1;
				int k = 0;				 
				while ( isspace ( curStr[i] ) && curStr[i] != '\0' )
				    i++;				 
				while ( isspace ( curStr[j] ) && j >= 0 )
				    j--;				 
				while ( i <= j )
				    curStr[k++] = curStr[i++];				 
				curStr[k] = '\0';

				//check if the curStr is numeric
				int checkIfInt = isNumeric(curStr);
            	int curIntIfInt = atoi(curStr);
            	if (checkIfInt != 0) {
            		//push on to top of stack (i.e. front of linked list)
            		//create new with the current value
            		//function call: pushToFrontOfStack(struct_of_ints, curIntIfInt);
            		//first check if the list is empty
            		if (!stackOfInts->value) {
						//list is empty
						stackOfInts->value = curIntIfInt;
						stackOfInts->next = NULL;
					}
					else {
						//list has elements. add cur int to front of linked list
						struct struct_of_ints *curNode = 
							malloc (sizeof (struct struct_of_ints) ) ;
						curNode->value = curIntIfInt;
						curNode->next = stackOfInts;
						stackOfInts = curNode;
					}

            		printf("Is an int: %d\n", curIntIfInt);            		
            	}
            }
            fclose( file );
            printf ("stackOfInts[0]=%d\n", stackOfInts->value ) ;
			printf ("stackOfInts[1]=%d\n", stackOfInts->next->value ) ;
			printf ("stackOfInts[2]=%d\n", stackOfInts->next->next->value ) ;
			printf ("stackOfInts[3]=%d\n", stackOfInts->next->next->next->value ) ;
			printf ("stackOfInts[4]=%d\n", stackOfInts->next->next->next->next->value ) ;
        }
    }
}

//void pushToFrontOfStack(struct struct_of_ints)

int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}