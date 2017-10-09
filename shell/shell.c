#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytoc.h"
#include "saferFork.h"
#include <string.h>
#include <sys/wait.h>


int main(int argc, char **argv, char** envp){
  
  while(1){
    char *input = (char*)malloc(100);//store user input
    write(1,"$",1);
    read(0,input,100); //read user input
    
    int status;
    pid_t pid, wpid ; //Create a child process
    pid = fork();
   
    if(pid == 0) //If process is a child,try executing the command
      {
	int retVal = 0; //get return from execve to check for errors
        
	char **command  = mytoc(input,' '); //tokenize the command entered by the user using mytoc()
	int lenght = 0;
	for(;*command; command++){
	  lenght++;
	}
	char **path = mytoc(envp[26],'=');
	char * temp = strcat('\0',path[1]);
        command[lenght+1] = NULL;
	//printf("path[] = \"%s\"\n",path[1]);
	retVal = execve(temp,command,envp);
	fprintf(stderr, "%s: exect returned %d\n", command[0],retVal);

      }
    wait(NULL);
    else
      while(wait(&status) > 0)
  }
  return 0;
}
