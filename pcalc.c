#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int isNumeric (const char * s);

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
    	//assume no command will be longer than 100 digits long
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
            		printf("Is an int: %d\n", curIntIfInt);
            	}
            }
            fclose( file );
        }
    }
}



int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}