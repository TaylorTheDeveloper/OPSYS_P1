#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Global Constants
#define BUFFER_LENGTH 80

void runshell(){
	//Shell Variables
	bool run = true;
  	const char* userName = getenv("USER");
	const char* shellName = "StallionShell";
	char cwd[BUFFER_LENGTH];

	  // Run Shell
	  while(run){
	  	// Update current directory
	    getcwd(cwd, BUFFER_LENGTH); 
	    if (cwd != NULL) {
	    // Print prompt if getcwd is successful
	    printf("%s@%s:%s $  ", userName, shellName, cwd);
	    run = false;//Temportary
	    }
	    else{
	    printf("ERROR: getcwd failed!\n");
	    exit(1);
	  	}
	  
	}

}

int main(void) {
    runshell();
    return 0;
}