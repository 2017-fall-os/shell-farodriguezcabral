//Francisco Rodriguez Cabral
#include <stdio.h>
#include <stdlib.h> //for malloc and calloc

char **mytoc(char *str, char delim){
  char *copyStr;//helper string to keep the current token to be stored
  char **tokenVec; //vector containing the tokens to be returned
  int numOfTokens = 0; //num of tokens contained in the input string
  int counter = 0; //counter that keeps track of the current position in the string input
  //while loop will stop once the null character is reached
  while(str[counter] != '\0'){
    //check wheter the delim character has been found or the last token has been reached
    if(str[counter] == delim || str[counter+1] == '\0')
      numOfTokens++;

    counter++;
  }
  //allocate memory for tokenVect according to the number of tokens in string
  tokenVec = (char **)calloc(numOfTokens+1, sizeof(char*));
  counter = 0; //make counter equal to zero so it can be reused to go again throuh the string
  
  int charCounter = 0; //to store the length of each token
  int tokenPosition = 0; //to determine which token position we are at
      
  while(str[counter] != '\0'){
    //check whether the delim character has been reached or the end of the string has been reached
    if(str[counter] == delim || str[counter+1] == '\0'){
      //if statement avoids missing out the last character of the string before the end of line
      if(str[counter+1] == '\0'){
	charCounter++;
	counter++;
       
      }      
      //allocate memory for the corresponding token position
      tokenVec[tokenPosition] = (char *)malloc(charCounter+1);//allocate memory for the token at
      //allocate memory for the copyStr which will hold the current token to be stored in the array
      copyStr = (char *)malloc(charCounter+1);
      //add the null character at the end of the copyStr
      copyStr[charCounter+1] = '\0';
      //counter to keep track of the current position on the token to copied
      int copyCounter = 0;
      while(charCounter > 0){
	//copy character by carachter from the input string to the copyStr
	copyStr[copyCounter] = str[counter-charCounter];
	
	charCounter--;
	copyCounter++;
      }

      //store the copied string into the array
      tokenVec[tokenPosition] = copyStr; 
      tokenPosition++;
     
    }
    else{
      charCounter ++;

    }
    counter++;  

  }
  //add the null character at the end of the token
  tokenVec[tokenPosition+1] = '\0';
  //return the array of strings
  return tokenVec;
}
