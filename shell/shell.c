#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mytoc.h"
#include "saferFork.h"
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
int tokenLen(const char *token);
char *concat(char *str,char *cmd,int lenght, int cmdLenght);

int main(int argc, char **argv, char** envp){
  
  while(1){
    char *input = (char*)malloc(100);//store user input
    write(1,"$",1);
    read(0,input,100); //read user input
    
    int status;
    // pid_t pid, wpid ; //Create a child process
    int pid = fork();
   
    if(pid == 0) //If process is a child,try executing the command
      {
	int retVal = 0; //get return from execve to check for errors
        
	char **command  = mytoc(input,' '); //tokenize the command entered by the user using mytoc()
	//write(1,envp[26],20);
	char **path = mytoc(envp[26],'=');
	char **path2 = mytoc(path[1],':');
	int cmdLenght = tokenLen(command[0]);
	for(int i = 0; path2[i] != '\0'; i++)
	  {
	    int lenght = tokenLen(path2[i]);
	    //  write(1,path2[i],20);
	    //write(1,":",1);
	    char *totalPath = concat(path2[i],command[0],lenght,cmdLenght+1);
	    write(1,totalPath,20);
	    write(1,":",1);
	    struct stat sb;
	  
	    if(stat(totalPath,&sb) == 0)
	      {
		retVal = execve(totalPath,command,envp);
		fprintf(stderr, "%s: exect returned%d\n",command[0],retVal);
	      }
	    //free(totalPath);
	  }
      }
  
    else
      waitpid(pid,&status,0);
	
  }
  return 0;
}

char *concat(char *str,char *cmd,int lenght, int cmdLenght){
  int totalLenght = lenght+cmdLenght;
  char *tmp = (char*)malloc(totalLenght+1);
  char *tempStr = tmp; //char destination d store in temp
  int i = 0;
  
  while (*str) //while there is stuff in source copy it to the destination
    {
      *tmp++ = *str++;
    }
  *tmp++ = '/';
  
  while (*cmd) //while there is stuff in source copy it to the destination
    {
      *tmp++ = *cmd++;
    }
  
  *tmp++ = '\0';//store null character
  return tempStr;

}
