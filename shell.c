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
#define MAX_TOKENS 100
#define BUILTIN_EXIT "exit"
#define BUILTIN_CD "cd"
#define BUILTIN_IOACCT "ioacct"
#define BUILTIN_USEFUL "somethinguseful"


// Parse input
void parseInput(char *input) {
	const char* delims = " \n\r\f\t\v"; //Input delimiters
	char *token, *token_array[MAX_TOKENS]; // Tokenized input
	int inputCounter =0;

    token = strtok(input, delims);
    
    while(token != NULL) {
      token_array[inputCounter] = malloc(strlen(token) + 1);
      strcpy(token_array[inputCounter++], token);
      printf("%s token\n", token );
      token = strtok(NULL, delims);
    }
}

// void checkBuiltIn(char *input[]){
// 		char *cmd = input[0];
// 		switch(cmd){
// 	    	case BUILTIN_CD: printf("%s\n", "cd");
// 	    	break;
// 	    	case BUILTIN_IOACCT: printf("%s\n", "ioacct");
// 	    	break;
// 	    	case BUILTIN_USEFUL:printf("%s\n", "somethinguseful");
// 	    	break;
// 	    	case BUILTIN_EXIT:printf("%s\n", "Exiting StallionShell v0.1");
// 	    	exit(EXIT_SUCCESS);
// 	    	break;
// 	    }
// }

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
	    exit(EXIT_FAILURE);
	  	}
	  	// Grab user input, output error if NULL
	  	// http://www.cplusplus.com/reference/cstdio/fgets/
	    if(fgets(input, BUFFER_LENGTH, stdin) == NULL){
	      printf("ERROR: fgets failed!\n");
	      exit(EXIT_FAILURE);
	    };

	    //Parse Input here
	    parseInput(input);

	    //Evaluate and execute input here
	  
	}
    return 0;
}