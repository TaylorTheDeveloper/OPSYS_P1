
void redirectCommands(bool inout){

	    printf("ERROR: redirect!\n");
//In is 1(true), out is 0(false)
char *cmd = malloc(80 * sizeof(char));
char *binPath = malloc(80 * sizeof(char));
strcpy(binPath, "/bin/");
char *redirect = malloc(80 * sizeof(char));

int i = 1;
while(i < argSize){
	printf("\n%s", args[i]);
	i++;
	//args[i] = strtok(NULL, " \0");
	}

strcpy(cmd, args[0]);
strcpy(redirect,  args[2]);
strcat(binPath, cmd);

//check to see if file exists for input redirection
if(inout == true){
	if( access(redirect, F_OK) == -1){
	printf("File doesn't exist\n");
	return;
	}
}

int pid = fork();
	if (pid == -1) {
		perror("fork");
		_exit(1);
	}
	else if (pid >= 0 && inout == true) {
		if(pid == 0){
		int fd0 = open(redirect, O_RDONLY, 0);
		dup2(fd0, STDIN_FILENO);
		close(fd0);
		execv(binPath, args);
		//exit(EXIT_FAILURE);
		}
		else if(pid > 0){
		waitpid(pid, 0, 0);
		}	
	}
	else if (pid >= 0 && inout == false) {
		if(pid == 0){
		int fd0 = creat(redirect, 0644);
		dup2(fd0, STDOUT_FILENO);
		close(fd0);
		execv(binPath, args);
		//exit(EXIT_FAILURE);
		}
		else if(pid > 0){
		waitpid(pid, 0, 0);
		}	
	}
};