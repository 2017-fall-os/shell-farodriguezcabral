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
int exitShell(char *input);
int numberOfTokens(char *tokens, char delim);

int main(int argc, char **argv, char** envp){
  int exitshell = 1;
  while(exitshell){
    // char *argv[] = {"whoami",NULL};
    //char *env[] = {"PATH=/usr/local/sbin/:/usr/local"};

    char *inp = (char*)malloc(100);//store user input
    write(1,"$",1);
    int bytesread = read(0,inp,100); //read user input
    if(bytesread == 0) exit(0);
    exitshell = exitShell(inp);
    char **input = mytoc(inp,'\n');
    char **command;
    
   
    if(input[0][0] == '/'){ //check if a path has been given
      
      int lastToken = numberOfTokens(input[0],'/');//get position of command on given path
      command = mytoc(input[0],'/');//tokenize the given path to get the command to be executed
      char **cmd = mytoc(command[lastToken-1],' '); //create a vector of pointers containing the command
     
      struct stat sb;
      int found = stat(input[0],&sb);//check if command exists on path
      
      if(found == 0){//if command exists, try executing it.
	int retval = execve(input[0],cmd,envp); 
	fprintf(stderr, "%s: exect returned %d\n",command[0],retval);
      }
    }

  
    command = mytoc(input[0],' ');
    
    char *pathenv;
   
    for(int i = 0; envp[i] != '\0'; i++){ //look for PATH environment
      char **environment = mytoc(envp[i],'=');
      

      if(strcmp(environment[0],"PATH") == 0){//check if PATH has been found
	pathenv = environment[1];
      }
    }

    char **listOfPaths = mytoc(pathenv,':');
    
    int found;
    int cmdLength = tokenLen(command[0]);
   
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
//concatante the command entered to its corresponding path in case a path was not given
char *concat(char *str,char *cmd,int lenght, int cmdLenght){
  
  int totalLenght = lenght+cmdLenght;
  char *tmp = (char*)malloc(totalLenght+1);
  char *tempStr = tmp; //char destination d store in temp
  int i = 0;
  
  while (*str){ //while there is stuff in source copy it to the destination
    *tmp++ = *str++;
  }
  *tmp++ = '/';
  
  while (*cmd){ //while there is stuff in source copy it to the destination
    *tmp++ = *cmd++;
  }
  
  *tmp++ = '\0';//store null character
  return tempStr;
}

//exitShell function checks if "exit" has been entered by user in order to terminate shell
int exitShell(char *input){

  char * exit = "exit";
  int terminate = 1;
  for(int i = 0; input[i] != '\0' && exit[i] != '\0'; i++){
    if(input[i] == exit[i]){
      terminate = 0;
    }
    else{
      terminate = 1;
      break;
    } 
  }
  return terminate;
}
