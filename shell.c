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

/*
This routine replaces a character within a character 
array with another character.
Cite: 
https://www.daniweb.com/software-development/c/threads/461567/replacing-a-character-with-another-character-in-given-string 
*/
strreplace(char s[], char chr, char repl_chr){
     int i=0;
     while(s[i]!='\0'){
           if(s[i]==chr){
               s[i]=repl_chr;
           }  
           i++; 
     }
    puts(s);
    return 0;
}
/*
This routine checks for the & symbol, 
which tells the system to run the process in the background.
If found, it will erase the symbol and set the background variable to true.
*/
void backgroundCheck(char *input){
    char * pch;

    pch=strchr(input,'&');
    while (pch!=NULL){
      //  printf ("found at %d\n",pch-input+1);
        background = true;
        pch=strchr(pch+1,'&');
        strreplace(input,'&',' ');
    }

    if(background){
        printf ("background set\n\n");

    }

}
/*
This routine tokenizes the input. Stores Values Globally for both the input array and the size of that array.
Maximum of 20 input tokens.
*/
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

/*
This routine is to be called at the end of each cycle of the shell. It cleans up the global memory and resets all values
*/
void clearGlobals(){
    int i;
    for(i =0; i< argSize;i++){
        free(args[i]);
    }
    argSize = 0;//Set back to Zero

    background = false;
    redirect = false;
}

/*
This routine exits the command line.
If there is a specified argument for a specific error code,
then the user can type something like:
exit 55
and the program will exit with code 55 instead of code 0, which is default.
*/
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

/*
Change directory handles all the change directory commands.
In addition to ".", "..", and "~". The user can also go to 
thier previous working directory with "-".

If it fails, it will output an error message.
*/
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
                printf("%s: No such file or directory.\n", "pwd");
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
/*
ioacct
Executes the rest of the command line operand as if it were entered directly on
the shell command line. Once execution of the command line completes, it will
print the number I/O bytes read and written. ioacct does not have to work
with background processes, pipes, or input/output redirection.
*/
void ioacct(){
        int pid = getpid();
        char processFileName[BUFFER_LENGTH];
        char* ioArgs[BUFFER_LENGTH];
        int ioArgSize = 0;
        char ioInfo[BUFFER_LENGTH];
        int ioValue;
      
        sprintf(processFileName, "/proc/%d/io", pid); // Create pid file
        FILE* file = fopen(processFileName, "r"); // Open File to be read
      
        // execute command as normal
        // remove "ioacct" from command, create new command array
        int i;
        for (i = 1; i < argSize; ++i){
            ioArgs[i-1] = args[i];
            ++ioArgSize;
        }

        // now reprocess the command
       // handleCommand(truncatedCommand, truncatedSize);
        ioacctProcessCommands(ioArgs);
      
        // then read "read_bytes" and "write_bytes" and write values out
        while (fscanf(file, "%s %d", ioInfo, &ioValue) != EOF)
        {
            if (strcmp(ioInfo, "read_bytes:") == 0)
            {
                printf("bytes read: %d\n", ioValue);
            }
            else if (strcmp(ioInfo, "write_bytes:") == 0)
            {
                printf("bytes written: %d\n", ioValue);
            }
        }
      
        fclose(file); // close the file
}

/*
Run commands will run built in commands for us.
*/
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
            ioacct();
            
        }
    }
    return 0;
}
void ioacctProcessCommands(char** ioargs){
    pid_t wpid;
    int status = 0;
    char * temp = getenv("PATH"); 
    char * path;//[512];
    char * tpath;
    bool found = false;
    const char * delim = ":";
    pid = fork();

    if(pid == 0){
        printf("Stuff in child!\n");
        tpath = strtok(temp, delim);
        while(tpath != NULL){
            path = malloc(strlen(tpath) + strlen(ioargs[0]) + 1); //allocating just enough so we can build our paths
            strcpy(path,tpath);
            strcat(path, "/");
            strcat(path,ioargs[0]);

            if(execv(path,ioargs) == -1){
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

void processCommands(){
    pid_t wpid;
    int status = 0;
	char * temp = getenv("PATH"); 
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
            strcpy(path,tpath);
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

        backgroundCheck(input);

        printf("%s\n\n",input);
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
