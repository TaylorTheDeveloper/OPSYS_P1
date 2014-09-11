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


Issues: 
-------------------------------------------------

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
