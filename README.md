OPSYS_P1
========

Command Line Interface

Project Details:
http://www.cs.fsu.edu/~cop4610t/html_src/assignments/project1/writeup/shell.pdf

Project FAQ:
http://www.cs.fsu.edu/~cop4610t/html_src/assignments/project1/faq.html

useful:
http://www.maths.cam.ac.uk/undergrad/catam/ccatsl/manual/node50.html
http://www.cplusplus.com/reference/cstring/strtok/


log: 
9/7/14: 
Basic Prompt I/O
9/9/14:
Exit, part of CD working now. Extended on parser. 
9/14/14
Got all of CD working, fixed hostname, couple other things repaired. Code cleaned up.
9/15/14
Had issue with commands not null terminating, got that fixed today.


Issues: 
-------------------------------------------------

   -Issues with calling functions after bad or unknown commands(i.e. la or
    something that doesn't exist): After an instance of something like that,
    the shell does not work any more. Creates multiple child processes of the
    shell.
   -Need to add & functionality so that commands run in the background,
   thinking of running an executable that has a while loop that prints shit
   out, and testing it with that
   -hostnameissue.
    const char* hostName[BUFFER_LENGTH];
    int hostCheck;
getHostName()
    // hostCheck = gethostname(hostName,BUFFER_LENGTH );
    // if(hostCheck==-1){
    //     printf("ERROR: gethostname failed!\n");
    //       exit(EXIT_FAILURE);
    // }
    out:
    shell.c: In function ‘main’:
shell.c:95:5: warning: passing argument 1 of ‘gethostname’ from incompatible pointer type [enabled by default]
     gethostname(hostName,BUFFER_LENGTH );
     ^
In file included from shell.c:14:0:
/usr/include/unistd.h:879:12: note: expected ‘char *’ but argument is of type ‘const char **’
 extern int gethostname (char *__name, size_t __len) __THROW __nonnull ((1));
            ^
   - Issue: When trying to run a program that doesnt exist, the shell doesnt take in input properly. 9-16-14

   - issue with tokenizing and parseing forces us to decide to make certain variables global

   - issue with null termination args, fixed

   - Issue with ioacct 9-17-14 while working
   *** Error in `./Shell': free(): invalid next size (fast): 0x0000000000c2f110 ***
Waiting for my child
*** Error in `./Shell': double free or corruption (top): 0x0000000000c2f110 ***
Aborted (core dumped)
        - Must exit multiple times from shell.
