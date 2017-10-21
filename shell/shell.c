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
    // char *argv[] = {"whoami",NULL};
    //char *env[] = {"PATH=/usr/local/sbin/:/usr/local"};

    char *inp = (char*)malloc(100);//store user input
    write(1,"$",1);
    read(0,inp,100); //read user input
    
    char **input = mytoc(inp,'\n') ;
    char **command = mytoc(input[0],' ');
    char *pathenv;
   
    for(int i = 0; envp[i] != '\0'; i++){ //look for PATH environment
      char **environment = mytoc(envp[i],'=');
      //  write(1,environment[0],5);
      //write(1,"&&",2);

      if(strcmp(environment[0],"PATH") == 0){//check if PATH has been found
	pathenv = environment[1];
      }
    }

    char **listOfPaths = mytoc(pathenv,':');
    
    int found;
    int cmdLength = tokenLen(command[0]);
    // write(1,listOfPaths[4],400);
    for(int i = 0; listOfPaths[i] != '\0'; i++){
      int pathLength = tokenLen(listOfPaths[i]);
      char *completePath = concat(listOfPaths[i],command[0],pathLength,cmdLength);
      struct stat sb;
      found = stat(completePath,&sb);//check if command exists on path
      if(found == 0){//if command exists, try executing it.
	int retval = execve(completePath,command,envp); 
	fprintf(stderr, "%s: exect returned %d\n",command[0],retval);

      }

      // int retval = execve("/bin/whoami",argv,envp); 
      //write(1,completePath,20);
       
    }
   
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
