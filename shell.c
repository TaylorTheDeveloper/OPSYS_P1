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
#include <time.h>
#include <sys/types.h>

//Global Constants
#define BUFFER_LENGTH 256
#define MAX_TOKENS 100
#define MAX_ARGS 20

//Global Variables
static char previousDir[BUFFER_LENGTH];
static char* args[MAX_ARGS];
static int argSize;
static bool background;
static bool redirect;
pid_t pid;

//Tokenizes input, returns counter for # of arguments
void tokenize(char *input) {
   const char* delims = " \n\r\t\v\f"; // Input delimiters
    char *token, *arg_array[MAX_TOKENS]; // Tokenized input
    int inputCounter =0;// Initilize inputCounter
    int i;

    token = strtok(input, delims);
    while(token != NULL) {
      arg_array[inputCounter] = malloc(strlen(token) + 1);
      strcpy(arg_array[inputCounter++], token);
      token = strtok(NULL, delims);
    }

    for(i = 0; i < inputCounter; i++){
        if(inputCounter == MAX_ARGS){            
        printf("ERROR: To many Tokens!\nUse less than %d", MAX_ARGS);
        }
        args[i] = malloc(strlen(arg_array[i]) + 1);
        strcpy(args[i], arg_array[i]);///make sure this null terminates
    }
    args[i] = NULL;
    argSize = inputCounter;
}

//Clears all the global elements
void clearGlobals(){
    int i;
    for(i =0; i< argSize;i++){
        free(args[i]);
    }
    argSize = 0;//Set back to Zero
    
    background = false;
    redirect = false;
}

//Exit Shell
void exitShell(){
    if(argSize > 1){
        int val = atoi(args[1]);
        clearGlobals();
        exit(val);
    }
    else{
        clearGlobals();        
        exit(EXIT_SUCCESS);
    }
}

//ChangeDirectory
void changeDirectory(){
    //Variables
    const char* homedir = getenv("HOME");
    char previousDirClone[BUFFER_LENGTH];
    strncpy(previousDirClone, previousDir, BUFFER_LENGTH);
    getcwd(previousDir, BUFFER_LENGTH);

    if(argSize > 1){
        if(strcmp(args[1], "~") == 0){//go home
            chdir(homedir);
        }
        else if(strcmp(args[1], "-") == 0){//go to prior path
            //printf("%s\n", "go back to pwd");
            if (chdir(previousDirClone) == -1){
                printf("%s: No such file or directory.\n", "Previous Working Directory");
            }
        }
        else if(chdir(args[1]) != 0){ //Change to specified directory
        printf("%s: No such file or directory.\n", args[1]);                  
        }
    }
    else{//Go home if nothing specified
            chdir(homedir);
    }


}

static int runCommands(){

    if (args[0] != NULL){
    //Built In commands
        if (strcmp(args[0], "exit") == 0) {
        //printf(" %s", "Exiting StallionShell\n");
            exitShell();
        }
        else if (strcmp(args[0],"cd")==0){
        //printf(" %s", "Change Directory\n");
            changeDirectory();
        }
        else if (strcmp(args[0],"ioacct")==0){
        //printf(" %s", "ioacct\n");
            
        }
    }
    return 0;
}

void processCommands(){
    pid_t wpid;
    int status = 0;
	char * temp = getenv("PATH");  ///make a copy
    char * path;//[512];
    char * tpath;
    bool found = false;
    const char * delim = ":";
    pid = fork();

    if(pid == 0){
        printf("Stuff in child!\n");
        tpath = strtok(temp, delim);
        while(tpath != NULL){
            path = malloc(strlen(tpath) + strlen(args[0]) + 1); //allocating just enough so we can build our paths
            strcpy(path,tpath);///does this null terminate?
            strcat(path, "/");
            strcat(path,args[0]);

            if(execv(path,args) == -1){
                tpath = strtok(NULL, delim);
            }
        }
    }
    else if(pid > 0){
       while((wpid = wait(&status)) > 0){
           printf("Waiting for my child\n");
       }
    }
    else printf("FORRRRRKKKKK\n");
	//ultimate goal of finding the absolute path of the command and then running exec
}

int main(void) {
    //Shell Variables
	bool run = true;
    background = false;
    redirect = false;
  	const char* userName = getenv("USER"); //Username
    const char* path = getenv("PATH"); // Path Variable
	const char* shellName = "StallionShell"; //Stallion Shell, oh yeah baby!
    char input[BUFFER_LENGTH]; //Command Input
	char cwd[BUFFER_LENGTH]; //Current Work Directory
    char hostName[BUFFER_LENGTH];

    gethostname(hostName,BUFFER_LENGTH );
    getcwd(previousDir, BUFFER_LENGTH); //Past Working Directory is the the current one right now
   
	  // Run Shell
	  while(run){

	  	// Update current directory, output error if NULL
	    getcwd(cwd, BUFFER_LENGTH); 
	    if (cwd != NULL) {
	    // Print prompt if getcwd is successful
	    printf("%s@%s:%s $  ", userName, hostName, cwd);
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

	    //Tokenize Input here
	    tokenize(input);
        //Print out tokens stuff
        int i=0;
	    //Evaluate and execute input here
	  
        processCommands(); //DERP
        runCommands();
        clearGlobals();//Reset Global Data

		}//End while loop
    return 0;
}
