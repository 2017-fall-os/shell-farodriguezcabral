Shell Lab
Francisco Rodriguez Cabral

In order to run the program, use the "make" command to create a ./shell executable file.

When testing the shell witht he testShell.sh script provided, I could not see if it succeeded.
However, when I manually entered the commands, they succeeded both with a given path and not given path.

For instance, when executing ./shell, the prompt was displayed and when I typed in ls or whoami,
the shell displayed the contents of the directory and the current user respectively. The same output was displayed when I entered the commands providing a path (i.e. typing /bin/ls and /bin/whoami).

Also, I was able to implement the creation of a child process using the saferFork.c program provided in the repository
and waiting for such a child process until it finished excuting the commands. 

Note: For this lab I received assistance from Erick Duarte for implementing the tokenizer.
He has already taken the OS class on previous semesters.
