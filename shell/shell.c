#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytoc.h"
#include "saferFork.h"
#include <string.h>

int main(int arcg, char **argv, char** envp){
  
  while(1){
    char *input = (char*)malloc(100);
    write(1,"$",1);
    //read user input
    read(0,input,100);
    //tokenize the command entered by the user using mytoc()
    char **command  = mytoc(input,' ');
    int child = saferFork();
    free(input);
    
    //If process is a child, run the command
    if(child == 0){
      int retVal = 0;
      //store the PATH variable when found
      char **path;
      //iterate through envp to look for PATH
       for(int i = 0; envp[i] != 0; i++){
	 //tokenize envp[i]
	path = mytoc(envp[i], '=');
        //if PATH is found, execute the command
	if(!strcmp(path[0],"PATH")){
	  retVal = execve(path[1],command,envp);
	  fprintf(stderr, "%s: exect returned %d\n", command[0],retVal);
	  
	}
	//free path in order to allow a new vector to be stored in case PATH is not found
	for(;*path != '\0';path++){
	  free(*path);
	}
       
       }	 
	  
    }
      
  }
  
  return 0;

}
  

