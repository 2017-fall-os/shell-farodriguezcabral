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

  
    //while(child = )
      // free(input);
   
    if((pid = fork()) == 0) //If process is a child,try executing the command
      {
	int retVal = 0; //get return from execve to check for errors
	//char **path; //store the PATH variable when found
	
	//int i;
	
	//for(i = 0;envp[i] != (char*)0; i++) //iterate through envp to look for PATH
	
	//for(;*path != '\0';path++)//free path in order to allow a new vector to be stored in case PATH is not found
	//	printf("envp[%d] = \"\n", i);
	char **command  = mytoc(input,' '); //tokenize the command entered by the user using mytoc()
	char **path = mytoc(envp[26],'=');
	//	for(;*path!='\0';path++)
	//printf("path=\"%s\n",*path);
	      
	
	    // printf("envp[%d] = \"%s\"\n", i, envp[i]);
	    //char ** path = mytoc(envp[i], '='); //tokenize envp[i]
	    //printf("path[%d] = \"%s\"\n", i, path[i]);
	    
	    //if(!strcmp(path[0],"PATH")) //if PATH is found, execute the command
		//{
	   
		// break;
	    //}
        
	    //free(path);
	int lenght = numOfTokens(input);
	command[lenght+1] =  '\0'; 
	char *temp1 = strcat(command[0],path[1]);
	char * temp = strcat('\0',temp1);
	//	printf("path[] = \"%s\"\n",path[1]);
	retVal = execve(path[1],command,envp);
	fprintf(stderr, "%s: exect returned %d\n", command[0],retVal);
	//exec(path[1],command,envp);
	//	for(;*path != '\0';path++)//free path in order to allow a new vector to be stored in case PATH is not found
		  //free(*path);

      }
    wait(NULL);
    //else
    //while(wait(&status) > 0)
    //	write(1,"7",1);
     
      
  }
  return 0;
}
