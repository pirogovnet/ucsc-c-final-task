#ifndef student
#define student

#include "functions_nikolay_pirogov.h"

//structure definition for double linked list

typedef struct STUDENT Student;

struct STUDENT  { 

int  ID;
char    *Name; 
double  quiz[4];
double  midi; 
double  midii;
double  finall;
char    grade;
Student *pNext; //pointer pointing to next student in the list (node)
Student *pPrev; //pointer pointing to previous student in the list (node)
}; 

char student_grade_simple(double * , double  , double , double ); 

void listAllFromHeadDL(Student *);

int get_num_elem_DL(Student *);

void sort_linked_list(Student *);

void swap_student(Student *, Student *);

int comapare_string(char *, char *);

int comapare_student(Student *, Student *);

Student *createStudentDL(int, char ** ); 


// Create student function 
Student *createStudentDL(int studentID, char **tokens)

{
	Student *pStudent;

	double quiz[4];
	double  midi; 
    double  midii;
    double  finall;
	char  grade; 

	pStudent = (Student*) malloc(sizeof(Student));

	pStudent->ID = studentID;                 // ID
	//
	pStudent->Name=malloc(sizeof(char) *strlen(tokens[0]));   //dynamic memory allocation for name
	//
	strcpy(pStudent->Name, tokens[0]);       //NAME
	
	for (int i=0; i<4; i++ )
	    get_double_from_str(tokens,&quiz[i],i+1);        // 4 marks initialization

	get_double_from_str(tokens,&midi,5);
	get_double_from_str(tokens,&midii,6);
	get_double_from_str(tokens,&finall,7);
	
	for (int i=0; i<4; i++ )
	     pStudent->quiz[i] = quiz[i];        // 4 marks initialization

	pStudent-> midi  = midi; 
    pStudent-> midii = midii;
    pStudent-> finall = finall;
	
	pStudent->grade = student_grade_simple(quiz, midi,midii,finall);
	//grade = student_grade_simple(quiz, midi,midii,finall);
	//printf("pStudent->grade =%c\n",pStudent->grade);
	
	//grade = 'A';
	//printf("grade =%c\n",grade);
	
	
	pStudent->pNext = NULL;
	pStudent->pPrev = NULL;
	return pStudent;
}


//display all the sudents name in the list

void listAllFromHeadDL(Student *pFirst)
{
	printf("\n\nBeginning of the current list:\n");
	while (pFirst) //why check this?  How about if the list is empty
	{
		//printf("Student ID: %d, Name: %s\n", pFirst->ID, pFirst->Name);
		printf("Student ID: %d, Name: %s, ", pFirst->ID, pFirst->Name);
		for (int i=0; i<4;i++)
		  { printf("quiz[%d]=%.2f, ", i, pFirst->quiz[i]); }
		     
		printf("midi=%.2f, ", pFirst->midi);
		printf("midii=%.2f, ", pFirst->midii);
		printf("final=%.2f, ", pFirst->finall);
		printf("grade=%c\n", pFirst->grade);
		
		pFirst = pFirst->pNext;
	}
	printf("End of list. \n\n");
}


// Appends a STUDENT to the end of the list
void appendStudentDL(Student **, Student **, Student *);

void appendStudentDL(Student **pHead, Student **pTail, Student *pSTUDENT)
{
	if (*pHead == NULL) 
	{
		*pHead = pSTUDENT;
		pSTUDENT->pPrev = NULL;
	}
	else 
	{
		(*pTail)->pNext = pSTUDENT;
		pSTUDENT->pPrev = *pTail;
	}
	*pTail = pSTUDENT;
	pSTUDENT->pNext = NULL;
}



//display all the sudents name in the list
void listAllFromTailDL(Student *);

void listAllFromTailDL(Student *pLast)
{
	printf("\n\End of the current list:\n");
	while (pLast) //why check this?  How about if the list is empty
	{
		printf("Student ID: %d, Name: %s\n", pLast->ID, pLast->Name);
		
		pLast = pLast->pPrev;
	}
	printf("Beginning of list. \n\n");
}


// Get student grade 

char student_grade_simple(double * quiz, double midi , double midii, double finall)

{
	float grade=0; 
	
		for (int i=0; i<4;i++)
		  { 
	        grade+=0.1 * quiz[i];
	      }
	
	grade+= 0.2*midi +0.15*midii+ 0.25* finall; 
	//printf("final grade=%.2f\n",grade);
	
	if (grade>=90) {return 'A'; }
	if (grade>=80 && grade<90) {return 'B'; }
	if (grade>=70 && grade<80) {return 'C'; }
	if (grade>=60 && grade<70) { return 'D'; }
	if (grade>=50 && grade<60) { return 'F'; }
	else {return 'Z';} 
	
}

// get  number of Elements in LL

int get_num_elem_DL(Student *pFirst)
{
	int i=0; 
	while (pFirst) //why check this?  How about if the list is empty
	{
		pFirst = pFirst->pNext;
		i++;
	}
	//printf("sudent.h: get_num_elem_DL: Number of elements in DL:%d\n", i);
	
	return i;
}



// Compare String

int comapare_string(char *str1, char *str2)
{
  int len1=strlen(str1);
  int len2=strlen(str2);
  //printf("student.h:comapare_string len1=%d, len2=%d\n", len1, len2);
  
  int lenMin=len1; 
  
  if  (lenMin>len2)
      {
		  lenMin=len2;
	  }
  
  for(int i=0;i<lenMin;i++)
	  {
		if(str1[i]==str2[i]) continue;
        if(str1[i]>str2[i])	 return 1; 
		if(str1[i]<str2[i])	 return 0; 
	 }
	 return 1;
}



// compare student 

int comapare_student(Student *pFirst, Student *pNext)
{
	// return 1 if next if bigger 
    char *strFirst=pFirst->Name;
    char *strNext= pNext->Name; 	
	
//	printf("student.h:comapare_student line1=%s, line2=%s\n", strFirst, strNext);
	int res=comapare_string(strFirst, strNext);
//	printf("student.h:comapare_student res=%d\n", res);
	return res;
}

//Swap
void swap_student(Student * pStart, Student *pNext)
{
	
	int      tmpID		=pStart->ID;
	char    *tmpName	=pStart->Name; 
	double  tmpQuiz[4]	={pStart->quiz[0],pStart->quiz[1],pStart->quiz[2],pStart->quiz[3]};  
	double  tmpMidi		=pStart->midi; 
	double  tmpMidii	=pStart->midii;
	double  tmpFinall	=pStart->finall;
	char    tmpGrade	=pStart->grade;

	pStart->ID		=pNext->ID;
	pStart->Name	=pNext->Name; 

	for (int i=0; i<4; i++ )
			 pStart->quiz[i] = pNext->quiz[i];        // 4 marks initialization

	pStart->midi	=pNext->midi; 
	pStart->midii	=pNext->midii;
	pStart->finall	=pNext->finall;
	pStart->grade	=pNext->grade;

	pNext->ID=tmpID;
	pNext->Name=tmpName; 

	for (int i=0; i<4; i++ )
			 pNext->quiz[i] = tmpQuiz[i];        // 4 marks initialization

	pNext->midi=tmpMidi; 
	pNext->midii=tmpMidii;
	pNext->finall=tmpFinall;
	pNext->grade=tmpGrade;
		
}

//Sort LL
void sort_linked_list(Student *pFirst)
{
	int num_elemnts=get_num_elem_DL(pFirst);
	
	
	int swapped, i;
    Student *pStart; 
    Student *pLast = NULL;
	
	if (num_elemnts<2) 
		   return;
	
	do
	{
		swapped=0;
		pStart=pFirst;
		
		while (pStart->pNext)
		{
			if (comapare_student (pStart, pStart->pNext) )
			{
				swap_student(pStart, pStart->pNext);
				swapped=1;
			}
			pStart= pStart->pNext;
		}
		//lptr = ptr1;
		
	} while(swapped);

}




#endif