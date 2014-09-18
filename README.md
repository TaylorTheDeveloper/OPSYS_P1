stallionShell
========
By David Perez and Taylor Brockhoeft
Submission Date: 09-17-14

Command Line interface for unix systems.

Currently, there are three built in commands:

  exit: Which exits the program with a status zero. 
  You can specify another exit code with the command, like this: exit 55. This will exit with an exit code of 55 instead of the default, 0.

  cd: Which changes directories. 
  In addition to being able to specify absolute and relative paths, you can also specify "." for the current working directory. ".." for the directory before the current working directory on the file system. And "-" to specify the past working directory.

  ioacct: Which is currently presumed to be broken. Proper usage would be:  ioacct <commands>. It is supposed to run the command just like any other command and read the read and write byte values and output these.

In addition to the built in commands, one can also execute binaries from anywhere in the file system as long as they are stored in $PATH. Programs such as ls, wc, and nano can be run.

To Build and Run stallionShell, simply type "make" in the project directory and all of the files will be built.

Further details about this project can be found in Report.docx.

Software files: 
shell.c
  Contains the shell code to run our shell.


Project Details:
http://www.cs.fsu.edu/~cop4610t/html_src/assignments/project1/writeup/shell.pdf

Project FAQ:
http://www.cs.fsu.edu/~cop4610t/html_src/assignments/project1/faq.html

useful links:
http://www.maths.cam.ac.uk/undergrad/catam/ccatsl/manual/node50.html
http://www.cplusplus.com/reference/cstring/strtok/


Known Issues:

Bugs/Issues (fixed ones specified)
Issue: calling functions after bad or unknown commands(i.e. la or
 valgrind if it's not installed)
User has to exit shell twice. I'm pretty sure this is because it is attempting to create a process and forking it. It wont find the command, so it wont execute it. The first time you enter exit, you leave the forked instance of the shell, since noting was able to execute and exit. Then, when you type exit again, then it will exit the program.

Issue(fixed): the shell does not work any more. Creates multiple child processes of the
 shell.
Resolved on 9/12. Was a simple while loop issue.

Issue: When trying to run a program that doesn't exist, the shell doesn't take in input properly. 9-16-14

Issue(fixed): with tokenize() and parsing 
Made us to decide to make certain variables global

Issue(fixed): with null termination args

Issue resolved by appending 'NULL' to end of imput

Issue(think it's fixed now): Must exit multiple times from shell.
Occasionally, for what we thing are a majority of issues with forked process, the user may need to exit the shell multiple times. We believe it's been fixed today. (9-17-14)

Issue: Occasionally commands that require a param get hung up, such as wc without a specified file
type “wc” and you'll see what I'm talking about.
Type “wc shell.c” and it works fine
not sure why this is an issue

Issue(fixed): Had an issue today(9-17-14) where the prompt wouldn't print out after executing a command.  This was caused by the process being forked and then waiting for new input before going back to the main while loop and printing the prompt.

Issue(fixed): In fixing the issue above, we created a new issue. When we call clear or ls or any other unix command after calling cd, which is built in. We have an issue where it wont take in any more input. However, cd will work indefinitely. We think that there are issues with CD closing. Our assumptions we're correct and we were able to quickly squish that bug.

Issue: ioacct, after being called will break the input stream. Thus, the user can no longer successfully enter commands. Also, we had a segmentation fault whenever we called fclose(file); on the file stream. We're thinking it's because for some reason the file isn't being opened properly, and then when we try to close the file stream there is nothing in memory to close, so a segmentation fault occurs. We noticed also after running it multiple times, a segfault occurs as well, after a few tries to run additional commands on the execution stream.

