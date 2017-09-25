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
    
    
    if(child == 0){
      int retVal = 0;
     
      char **path;
       for(int i = 0; envp[i] != 0; i++){
      
	path = mytoc(envp[i], '=');
        
	if(!strcmp(path[0],"PATH")){
	  retVal = execve(path[1],command,envp);
	  fprintf(stderr, "%s: exect returned %d\n", command[0],retVal);
	  
	}
	for(;*path != '\0';path++){
	  free(*path);
	}
       
       }	 
	  
    }
      
  }
  
  return 0;

}
  

