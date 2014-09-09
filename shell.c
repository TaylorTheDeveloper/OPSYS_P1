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
#define MAX_ARGS 20

//Search For Program Function

// Parse input
void parseInput(char *input) {
	char *argv[MAX_ARGS];  // Account for null string to execv
	const char* delims = " \n\r\t\v\f"; //Input delimiters
	char *token, *arg_array[MAX_TOKENS]; // Tokenized input
	int inputCounter =0;
	int i;

    token = strtok(input, delims);
    while(token != NULL) {
      arg_array[inputCounter] = malloc(strlen(token) + 1);
      strcpy(arg_array[inputCounter++], token);
      //printf("%s token\n", arg_array[inputCounter-1] );
      token = strtok(NULL, delims);
    }

    for(i = 0; i < inputCounter; i++){
    	//If built in
    	//If input redirect
    	//If output redirect
    	//If pipe
    	if(strcmp(arg_array[i],"exit")==0){//Built in Function
    		printf("%s\n", "exiting StallionShell");
    		for(i = 0; i < inputCounter; i++){
		        free(arg_array[i]); // Clean up mem before exit
		    }
    		exit(EXIT_SUCCESS);
    	}
    	else if(strcmp(arg_array[i],"cd")==0){//Built in Function
    		//need to store previos working directory
    		printf("%s\n", "change directory");
    		//If this eq ~ go home
    		//If this eq - go to pwd
    		if(arg_array[1]==NULL){
    			printf("%s: nullll.\n", argv[1]);//Why does this prevent segfault?
    		}
    		if(chdir(arg_array[1]) != 0){
        		printf("%s: No such file or directory.\n", arg_array[1]);
    		}
    	}
    	else if(strcmp(arg_array[i],"ioacct")==0){//Built in Function
    		printf("%s\n", "beep, beep, boop. beep");
    	}
    	else if(strcmp(arg_array[i],"bonus")==0){//Built in Function
    		printf("%s\n", "useful function here");
    	}
    	else{//Store Commands for program executions
    		argv[i] = malloc(strlen(arg_array[i]) + 1);
	        strcpy(argv[i], arg_array[i]);
	      	printf("%s stored\n", argv[i] );
    	}
    	

    }

}


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
	  
		}//End while loop
    return 0;
}