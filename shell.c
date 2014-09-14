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
#include <unistd.h>
#include <sys/types.h>


//Global Constants
#define BUFFER_LENGTH 255
#define MAX_TOKENS 100
#define MAX_ARGS 20
//Derp
static char* args[MAX_ARGS];
static int argSize;
pid_t pid;
//Search For Program Function


// Parse input
void parseInput() {
	int inputCounter =0;
	int i;

    for(i = 0; i < inputCounter; i++){
    	//If built in
    	//If input redirect
    	//If output redirect
    	//If pipe
    	if(strcmp(args[i],"exit")==0){//Built in Function
    		printf("%s\n", "exiting StallionShell");
    		for(i = 0; i < inputCounter; i++){
		        free(args[i]); // Clean up mem before exit
		    }
    		exit(EXIT_SUCCESS);
    	}
    	else if(strcmp(args[i],"cd")==0){//Built in Function
    		//need to store previos working directory
    		printf("%s\n", "change directory");
    		//If this eq ~ go home
    		//If this eq - go to pwd
    		if(args[1]==NULL){
    			printf("%s: nullll.\n", args[1]);//Why does this prevent segfault?
    		}
    		if(chdir(args[1]) != 0){
        		printf("%s: No such file or directory.\n", args[1]);
    		}
    	}
    	else if(strcmp(args[i],"ioacct")==0){//Built in Function
    		printf("%s\n", "beep, beep, boop. beep");
    	}
    	else if(strcmp(args[i],"bonus")==0){//Built in Function
    		printf("%s\n", "useful function here");
    	}
        else{

        }

    }

}

//Tokenizes input, returns counter for # of arguments
void tokenize(char *input) {
    //char *argv[MAX_ARGS];  // Account for null string to execv
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
        if(inputCounter == MAX_ARGS){            
        printf("ERROR: To many Tokens!\nUse less than %d", MAX_ARGS);
        }
        args[i] = malloc(strlen(arg_array[i]) + 1);
        strcpy(args[i], arg_array[i]);
    }
    
    argSize = inputCounter;
}
//Clears all the global elements
void clearGlobals(){
   //free(args);
    int i;
    for(i =0; i< argSize;i++){
        free(args[i]);
    }
    argSize = 0;//Set back to Zero
    
}
//Exit Shell
void exitShell(){
    clearGlobals();
    exit(EXIT_SUCCESS);

}

//ChangeDirectory
void changeDirectory(){

    printf("%s\n", "change directory");
            if(argSize > 1){
    printf("%s\n", "gt1");
            //If this eq ~ go home
                if(args[1] == "~"){
                    //get home path, and go there
    printf("%s\n", "go home");

                }
                else if(args[1] == "-"){
            //If this eq - go to pwd
                    //get prior path, then go. Store Global.
    printf("%s\n", "go back to pwd");
                    
                }
            }

            if(chdir(args[1]) != 0){
                printf("%s: No such file or directory.\n", args[1]);
            }
}

static int runCommands( int input, int first, int last){
//Input, first,last will be used for pipes
    if (args[0] != NULL){
        if (strcmp(args[0], "exit") == 0) {
    printf(" %s", "Exiting StallionShell\n");
            exitShell();
        }
        else if (strcmp(args[0],"cd")==0){
    printf(" %s", "Change Directory\n");
            changeDirectory();
        }
    }
    return 0;
}

void processCommands()
{
    pid_t wpid;
    int status = 0;
	char * temp = getenv("PATH");  
    //printf("The path goes %s", temp);
    //int pathcount = 0;
    char * path;//[512];
    char * tpath;
    bool found = false;
    const char * delim = ":";
    pid = fork();
    if(pid == 0)
    {
        printf("Bitches in my child!\n");
        tpath = strtok(temp, delim);
        while(tpath != NULL)
        {
            //patharray[pathcount] = malloc(strlen(tpath)+1);
            //strcpy(patharray[pathcount++], tpath);
            //printf("%s\n", patharray[pathcount-1] );
            path = malloc(strlen(tpath) + strlen(args[0]) + 1); //allocating just enough so we can build our paths
            strcpy(path,tpath);
            strcat(path, "/");
            strcat(path,args[0]);
            printf("%s\n", path);

            if(execv(path,args) == -1)
            {
                printf("Tried %s but no dice\n", path);
                tpath = strtok(NULL, delim);
            }
        }
    }
    else if(pid > 0) 
    {
       while((wpid = wait(&status)) > 0)
       {
           printf("Waiting for my fuckasschild\n");
       }
    }
    else printf("FORRRRRKKKKK\n");
	//ultimate goal of finding the absolute path of the command and then running exec
}

int main(void) {
    	//Shell Variables
	bool run = true;
    char* inputTokens;
  	const char* userName = getenv("USER");
    const char* path = getenv("PATH");
	const char* shellName = "StallionShell";
    const char hostName[BUFFER_LENGTH];
    char input[BUFFER_LENGTH];
    //Current Work Directory
	char cwd[BUFFER_LENGTH];
    //Prior Work Directory
    char *pwd[BUFFER_LENGTH];
    int hostCheck;  
    //Derp  
    char* cmd;
    //gethostname(hostName,sizeof hostName );
    // if(hostCheck==-1){
    //     printf("ERROR: gethostname failed!\n");
    //       exit(EXIT_FAILURE);
    // }

    getcwd(cwd, BUFFER_LENGTH); 
    *pwd = cwd;//Past Working Directory is the the current one right now
        
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
//Derp
        cmd = input;
	    //Tokenize Input here
	    tokenize(input);
        //Print out tokens stuff
        int i=0;
        // for(i = 0; i < argSize; i++){
        //     printf("%s stored\n", args[i] );
        // }
        //Parse here

	    //Evaluate and execute input here
	  
    processCommands(); //DERP
    runCommands(0,0,0);
        //clearGlobals();
       // printf("%s\n", strlen(args[0]));
        clearGlobals();//Reset Global Data
        
        // for(i = 0; i < argSize; i++){
        //     printf("%s stored\n", args[i] );
        // }

		}//End while loop
    return 0;
}
