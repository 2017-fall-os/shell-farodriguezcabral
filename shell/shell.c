#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytoc.h"
#include "saferFork.h"
#include <string.h>

int main(int arcg, char **argv, char** envp){
  
  while(1){
    char *input = (char*)malloc(100);//store user input
    write(1,"$",1);
    read(0,input,100); //read user input
    char **command  = mytoc(input,' '); //tokenize the command entered by the user using mytoc()
    int child = saferFork(); //Create a child process
    free(input);
   
    if(child == 0) //If process is a child,try executing the command
      {
	int retVal = 0; //get return from execve to check for errors
	char **path; //store the PATH variable when found
	int i = 0;
	for(;envp[i] != 0; i++) //iterate through envp to look for PATH
	  { 
	    path = mytoc(envp[i], '='); //tokenize envp[i]
	    if(!strcmp(path[0],"PATH")) //if PATH is found, execute the command
	      break;
	    
	    for(;*path != '\0';path++)//free path in order to allow a new vector to be stored in case PATH is not found
	      free(*path);  
	  }
	
	retVal = execve(path[1],command,envp);
	fprintf(stderr, "%s: exect returned %d\n", command[0],retVal);
      }
  }
  return 0;
}
