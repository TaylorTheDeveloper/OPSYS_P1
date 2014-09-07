/* Project 1: Unix Shell (myshell.c)
 * Fall 2014
 * COP4610, Andy Wang
 * Authors: Taylor Brockhoeft
 *			David Perez
 *
 * Stallion Shell
 */

 #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Global Constants
#define BUFFER_LENGTH 255



int main(void) {
    	//Shell Variables
	bool run = true;
  	const char* userName = getenv("USER");
	const char* shellName = "StallionShell";
	char cwd[BUFFER_LENGTH];
	char input[BUFFER_LENGTH];

	  // Run Shell
	  while(run){
	  	// Update current directory, output error if NULL
	    getcwd(cwd, BUFFER_LENGTH); 
	    if (cwd != NULL) {
	    // Print prompt if getcwd is successful
	    printf("%s@%s:%s $  ", userName, shellName, cwd);
	    
	    }
	    else{
	    printf("ERROR: getcwd failed!\n");
	    exit(1);
	  	}
	  	// Grab user input, output error if NULL
	  	// http://www.cplusplus.com/reference/cstdio/fgets/
	    if(fgets(input, BUFFER_LENGTH, stdin) == NULL){
	      printf("ERROR: fgets failed!\n");
	      exit(1);
	    };
	    printf("%s\n", input);

	    //Parse Input here

	    //Evaluate and execute input here
	  
	}
    return 0;
}