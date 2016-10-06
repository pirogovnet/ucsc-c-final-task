#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <assert.h>


#include "student_nikolay_pirogov.h"
#include "functions_nikolay_pirogov.h"

/*
   C Final Project
   Nikolay Pirogov 
*/



char * getString (char *);
int  read_file_to_DL(char *,  Student **, Student **, Student ** );
int  write_res_file (int , char *,  char *,  Student *); 
void write_res_to_display (char *,  char *, Student *);



////// MAIN 


int main (int argc, char* argv[])

{
	
struct STUDENT *pStudent, *pHead, *pTail;
int id=0;

  if ( argc != 3 ) /* argc should be 3 for correct execution */
    {
        /*  argv[0] - the program name */
        printf( "usage: %s filename1 filename2\n", argv[0] ); return 0;
    }
	
	   
		  id=read_file_to_DL(argv[1], &pStudent, &pHead, &pTail);
		  
		  sort_linked_list(pHead);

		  write_res_file(id, argv[1], argv[2], pHead);
 
		  write_res_to_display(argv[1], argv[2], pHead);
		  
	
   	//listAllFromHeadDL(pHead);
	printf("\n\n");       
	printf("\nPress enter key to continue...");
	getchar();       
		
	return 0;
}


//Dynamic memory allocation for string
char * getString (char *str)
{
	
	char *pStr;
	pStr= (char *) malloc (sizeof(char) * (strlen(str)+1)); 
	if (pStr==NULL)
	{
		printf("Not enough memory to allocate %s\n", str);
		return NULL;
	}
	strcpy(pStr, str);
	
	return pStr; 
	
}

// Write result to file 
int  write_res_file (int id, char *argv1, char *argv2,  Student *pFirst)
{
	FILE *file_out = fopen( argv2, "w" );
	
    if ( file_out == 0 )
        {
            printf( "Could not open file to write %s\n",argv2); return 0; 
        }

	fprintf(file_out, "Letter grade for %d students given in %s file is:\n", id, argv1);
	
	while (pFirst) //why check this?  How about if the list is empty
	{
		/*
		printf("Name: %s, ", pFirst->Name);
		printf("grade=%c\n", pFirst->grade);
		*/
		
		if(strlen(pFirst->Name) >=15)
		{
			fprintf(file_out, "%s:\t\tgrade=%c\n", pFirst->Name, pFirst->grade);
		}
		if(strlen(pFirst->Name) <15)
		{
			fprintf(file_out, "%s:\t\t\tgrade=%c\n", pFirst->Name, pFirst->grade);
		}
		
		
		pFirst = pFirst->pNext;
	}
	 
	 
	 fclose( file_out );
} 


// Write result to display 
void write_res_to_display (char *argv1, char *argv2,  Student *pFirst)

{
	
	 printf("Letter grade has been calculated for students listed in input file:%s and written to\n", argv1);
  	 printf("output file:%s\n", argv2);
  	 printf("\nHere is the class averages:\n");
	 
	 printf("\t\t Q1\t Q2\t Q3\t Q4\t MidI\t MidII\t Final\n");
	 
	 double  avgQ1,avgQ2,avgQ3,avgQ4, avgMidI, avgMidII,avgFinal; 
//	 double minQ1,minQ2,minQ3,minQ4, minMidI, minMidII,minFinal; 
//	 double maxQ1,maxQ2,maxQ3,maxQ4, maxMidI, maxMidII,maxFinal; 
	 
	  double minQ1=pFirst->quiz[0];
	  double minQ2=pFirst->quiz[1];
	  double minQ3=pFirst->quiz[2];
	  double minQ4=pFirst->quiz[3];
	  double minMidI=pFirst->midi;
	  double minMidII=pFirst->midii;
	  double minFinal=pFirst->finall;
	  
	  double maxQ1=0;
	  double maxQ2=0;
	  double maxQ3=0;
	  double maxQ4=0;
	  double maxMidI=0;
	  double maxMidII=0;
	  double maxFinal=0;
	 
	 int id=0; 
	 
	 
	while (pFirst) //why check this?  How about if the list is empty
	{
		avgQ1+=		pFirst->quiz[0];
		avgQ2+=		pFirst->quiz[1];
		avgQ3+=		pFirst->quiz[2];
		avgQ4+=		pFirst->quiz[3];
		avgMidI+=	pFirst->midi;
		avgMidII  +=	pFirst->midii;
		avgFinal+=	pFirst->finall;
		
		if(minQ1>pFirst->quiz[0]) {minQ1=pFirst->quiz[0];}
		if(minQ2>pFirst->quiz[1]) {minQ2=pFirst->quiz[1];}
		if(minQ3>pFirst->quiz[2]) {minQ3=pFirst->quiz[2];}
		if(minQ4>pFirst->quiz[3]) {minQ4=pFirst->quiz[3];}
		if(minMidI>pFirst->midi) {minMidI=pFirst->midi;}
		if(minMidII>pFirst->midii) {minMidII=pFirst->midii;}
		if(minFinal>pFirst->finall) {minFinal=pFirst->finall;}
		
		if(maxQ1<pFirst->quiz[0]) {maxQ1=pFirst->quiz[0];}
		if(maxQ2<pFirst->quiz[1]) {maxQ2=pFirst->quiz[1];}
		if(maxQ3<pFirst->quiz[2]) {maxQ3=pFirst->quiz[2];}
		if(maxQ4<pFirst->quiz[3]) {maxQ4=pFirst->quiz[3];}
		if(maxMidI<pFirst->midi) {maxMidI=pFirst->midi;}
		if(maxMidII<pFirst->midii) {maxMidII=pFirst->midii;}
		if(maxFinal<pFirst->finall) {maxFinal=pFirst->finall;}
		
				
		pFirst = pFirst->pNext;
		id++;
	}
	 
	    avgQ1/=id;
		avgQ2/=id;
		avgQ3/=id;
		avgQ4/=id;
		avgMidI/=id;
		avgMidII/=id;
		avgFinal/=id;
	 
	 
	 printf("Average:\t");
	 printf("%.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n", avgQ1,avgQ2,avgQ3,avgQ4, avgMidI, avgMidII,avgFinal);
	 printf("Minimum:\t");
	 printf("%.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n", minQ1,minQ2,minQ3,minQ4, minMidI, minMidII,minFinal);
	 printf("Maximum:\t");
	 printf("%.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\t %.2f\n", maxQ1,maxQ2,maxQ3,maxQ4, maxMidI, maxMidII,maxFinal); 
	
}


// Reading file to Linked List

int  read_file_to_DL(char *argv,  Student **pStudent, Student **pHead, Student **pTail )

{

char line[128];
char *pline; 
char delim=',';  
char **tokens = NULL;
int id=0; 


FILE *file_in = fopen( argv, "r" );

 if ( file_in == 0 )
        {
            printf( "Could not open file %s\n",argv); return -1;
        }
	
 while (fgets(line, sizeof(line), file_in))
		  {

   	        if (line[0]!='/') 
			  {

				  pline=getString(line);
 				  int token_num=token_count (pline, delim);  
				    // printf("main: token_num found %d\n", token_num); 
					
					tokens=malloc(sizeof(char*) * token_num);
					
					if (tokens==NULL)
						{
							printf("Not enough memory to allocate tokens\n");
							break;
						}
					
					
   					tokens=parse_str(pline, delim);
					/*
					 for (int j=0; j < token_num; j++)
					  {
						  printf ("main:tokens[%d]=%s\n", j, tokens[j]);
					  }
					*/  
           
                    if(id==0) 
					{
					  *pStudent = *pHead = *pTail = createStudentDL(id, tokens);
					} 					
					
					if (id>0)
					{
					  *pStudent = createStudentDL(id, tokens);
	                  appendStudentDL(pHead, pTail, *pStudent);
					}
					id++;
 				    
			  }  // endif if line is not commented 
			  

		  } // end of reading while 
		  
		  fclose( file_in );
		  return id; 
}