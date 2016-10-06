#ifndef functions
#define functions


#define MY_NAME "Nikolay Pirogov"
#define TRUE 1
#define FALSE 0
#include <stdlib.h>

//Function to clear the buffer
void ClearInputBuffer ();

void ClearInputBuffer()
{
    while (getchar() != '\n');
}


// Remove spaces from string
void RemoveSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}


// Remove EOL from string
void RemoveEOL(char* source)
{
  char* pos;
  
   if ((pos=strchr(source, '\n')) != NULL)
    *pos = '\0';

    if ((pos=strchr(source, '\r')) != NULL)
    *pos = '\0';
}



// Function to conver string to char 
double get_double_from_str (char **,    double *, int );

double get_double_from_str (char **arr, double * num1, int position)
{
	
    char* tmp=arr[position];
	char* end;
	
//	printf("get_double_from_str tmp=%s\n", tmp); 
    RemoveSpaces(tmp);
	RemoveEOL(tmp);
  
	double num2=  (double)strtod(&tmp[0], &end);
		
//	printf("get_double_from_str num2=%.2f\n", num2); 
	
	if (*tmp== '\0')
	{
	  printf("fail due to empty string\n"); return FALSE;
	}
	if (end == tmp || *end != '\0')
	{
	  printf("fail - the following characters are not part of a double:%s\n", end); return FALSE;
	}	
	
	*num1=num2;
	return TRUE;
}


//Function to get number of delimeter chars in string 

int delim_count (char *line,  char delim)        // get pointer to line and delim char, return number of parse symbols +1 

{

 char* tmp  = line; 
 char* last_delim = 0; 
 int   count      = 0;

	
 while (*tmp)
    {
        if (delim == *tmp)
        {
            count++;
            last_delim = tmp;
        }
        tmp++;
    }

	//printf("delim_count: count=%d\n", count);
	if (count==0) return 0; 
    
	return count+1;
} 

//Function to get number of tokens  in string 

int  token_count (char *line,  char delim)        // get pointer to line and parse char, return number of parse symbols 

{
	char **ap, *inputstring;
	const char *delim2=&delim;
	int tokens_count=0;
	int token_len=10;                            // not quite accurate - need to re-do with dynamic  memory allocation 
	char **arr2;

    /*  get maximum number of tokens we may have    */   	  

	int   count      = 0;
	count = delim_count(line,delim);

	//printf("parse_str: count=%d\n", count); 

    arr2= malloc( count * sizeof(char *) );      //allocate memory for maximum possible delimeters 
    if (arr2 == NULL)
        exit(1);

    for(int i=0;i<count;i++)
		{
		arr2[i]=malloc( token_len * sizeof(char *) );
		}	 
	 
	 
	inputstring=strdup(line);
     
           for (ap = arr2; (*ap = strsep(&inputstring, delim2)) != NULL;)
                   if (**ap != '\0')
				   {    tokens_count++; 
                        if (++ap >= &arr2[count]) 
							break;
				   }  
    
	free(arr2); //will not use this array any more 
	return 		tokens_count; 		   
	
}


//Function to return array of tokens

char**  parse_str (char *line, char delim)   

{
	/* http://www.manpagez.com/man/3/strsep/ */
	
	char **ap, *inputstring;
	const char *delim2=&delim;
	int token_len=10;            // not quite accurate - need to re-do with dynamic  memory allocation 
	char **arr2;

    /*  get maximum number of tokens we may have    */   	  

	int   count      = 0;
	count = delim_count(line,delim);

	//printf("parse_str: count=%d\n", count); 

    arr2= malloc( count * sizeof(char *) );      //allocate memory for maximum possible delimeters 
    if (arr2 == NULL)
        exit(1);

    for(int i=0;i<count;i++)
		{
		arr2[i]=malloc( token_len * sizeof(char *) );
		}	

	  inputstring=strdup(line);
      int tokens_count=0;
           for (ap = arr2; (*ap = strsep(&inputstring, delim2)) != NULL;)
                   if (**ap != '\0')
				   {    tokens_count++; 
                        if (++ap >= &arr2[count]) 
							break;
				   }        
    	
/*		
	printf("parse_str:tokens_count=%d\n",tokens_count);
	for (int i=0; i<tokens_count;i++)
	{
		printf("parse_str:token=%s\n",arr2[i]);
	}	
		
//*/		
    // free(arr2);  --  cannot free memory here 
    return arr2; 
	
}		

#endif
