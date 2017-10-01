//Francisco Rodriguez Cabral
#include <stdio.h>
#include <stdlib.h> //for malloc and calloc

int totalTokens(char* str,char delim);

char **mytoc(char *str, char delim){
  char *copyStr;//helper string to keep the current token to be stored
  char **tokenVec; //vector containing the tokens to be returned
  
  int counter = 0; //counter that keeps track of the current position in the string input
  int numOfTokens = totalTokens(str,delim);
  
  printf("numoftokens: %d",numOfTokens);
  
  tokenVec = (char **)calloc(numOfTokens+1, sizeof(char*));//allocate memory for tokens
  
  int charCounter = 0; //to store the length of each token
  int tokenPosition = 0; //to determine which token position we are at
  char * begin = str; //to contain beginning of str 
  
  for(;*begin != '\0'; begin++)//allocate enough memory for each character
    {
      if (*begin == delim)
	{
	  tokenVec[tokenPosition] = (char*)malloc(charCounter+1);
	  tokenPosition++;
	  charCounter = 0;
	}
      else
	charCounter++;
    }
  
  tokenPosition = 0;
  charCounter = 0;
  for(;*str != '\0'; str++)//copy string to vector
    {
      if(*str != delim)
	{
	  tokenVec[tokenPosition][charCounter] = *str;
	  charCounter++;
	}
      else
	{
	  tokenVec[tokenPosition][charCounter+1] = '\0';
	  charCounter = 0;
	  tokenPosition++;
	}
    }
  
  tokenVec[tokenPosition+1]; 

  //add the null character at the end of the token
  tokenVec[numOfTokens+1] = '\0';
  //return the array of strings
  
  return tokenVec;
}


int totalTokens(char* str,char delim)
{
  if (str == NULL)
    return 0;
  
  int numOfTokens = 0; //num of tokens contained in the input string
  for(;*str != '\0';str++) //for-loop will stop once the null character is reached
    { 
      if(*str == delim)//check wheter the delim character has been found or the last token has been reached
	numOfTokens++;
    }
  return numOfTokens+1;
}

//char *storeToken(char token[])
//{
// char *storedToken = NULL;
//  int lenght = 0;
  
//  while(token[lenght] != '\0')
//   {
//     lenght++;
//   }
// storedToken = (char*)calloc(lenght+1,sizeof(char));
// int i = 0;
// while(token[i] != '\0')
//   {
//    *(storedToken+i) = token[i];
//    i++;
//   }
// *(word + (i+1)) = '\0';
// return storedToken;
//}
