#include <stdio.h>
#include <stdlib.h>

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
            	int curIntIfInt = atoi(curStr);
            	if (curIntIfInt != 0) {
            		printf("%d", curIntIfInt);
            	}
            }
            fclose( file );
        }
    }
}