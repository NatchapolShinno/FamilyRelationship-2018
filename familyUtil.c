#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "abstractNetwork.h"
#include "networkBuilder.h"
#include "abstractStack.h"
#include "abstractQueue.h"
#include "abstractFamily.h"
#include "abstractConnect.h"

/**
 *   -1 mean there is no relation available
 *   -2 mean relation have still need to validate
 *    0 GrandFather,GrandMother
 *    1 Aunt,Uncle
 *    2 Father,Mother
 *    3 Husband,Wife
 *    4 Brother,Sister
 *    5 Son,Daughter
 *    6 GrandSon,GrandDaughter */

int combineRelation[7][7] = { {-1 , -1 , -1 ,  -1 , -1 ,  0 ,  0 } , {-1 , -1 , -1 ,  -1 ,  1 ,  4 ,  5 }, 
                               {-1 ,  0 ,  0 ,  -1 ,  2 ,  3 ,  5 }, { 0 ,  1 ,  2 ,  -1 , -1 , -1 , -1 },
                               {-1 ,  1 ,  1 ,  -1 ,  4 ,  5 ,  6 }, { 1 , -1 ,  4 ,   5 ,  6 ,  6 , -1 },
							   {4 ,  4 ,  5 ,  -1 ,  6 , 6 , -1 } };

/** Each relationship it has a sequence.
 *    0 GrandFather
 *	  1	GrandMother
 *    2 Aunt
 *	  3 Uncle
 *    4 Father
 *    5 Mother
 *    6 Husband
 *    7 Wife
 *    8 Brother
 *    9 Sister
 *    10 Son 
 *	  11 Daughter
 *    12 GrandSon 
 *	  13 GrandDaughter 
 */
char * relationSequence[15] = {"grandfather", "grandmother","uncle", "aunt","father", "mother",
                               "husband","wife","brother", "sister","son", "daughter","grandson","granddaughter"};

/** Check illegal character when we input gender
  @answer - Input of user
  @return if it correct return 1 but if it false return 0
*/
int checkInputGender(char * answer)
{
	if ((strcasecmp(answer,"M") == 0)||(strcasecmp(answer,"F") == 0))
		return 1;
	else 
		return 0;
}

/** Find the gender of person if him/her doesn't has gender
	and Validate the illegal gender.
	@name - person who want to check
	@genderInput - gender that user input
	@genderInput == "N" if don't know gender
	@return 1 - Male
			0 - Female 
*/
int findGenderOfPerson(char name[],char genderInput[])
{
	void * genderFromVertex;	/*Store the data from findVertex*/
	char input[8];
	char answer[8];				/*Answer that user input the gender*/
	int check = 0;				/*check the answer*/
	genderFromVertex = findVertex(name);
	

	if ((strcasecmp(genderInput,"N") == 0)&& (genderFromVertex != NULL))
	{
		genderFromVertex = findVertex(name);
	
		strcpy(answer,genderFromVertex);
	}
	else if (genderFromVertex != NULL)
	{
		if (strcasecmp(genderFromVertex, genderInput) != 0)
		{
			printf("\n\t!! Invalid Gender, Please Try Again !!\n" );
			return -1;
		}
	}
	else if ((strcasecmp(genderInput,"F") == 0)|| (strcasecmp(genderInput,"M") == 0))
	{
		strcpy(answer,genderInput);
	}
	else if (strcasecmp(genderInput,"N") == 0)
	{	
		while (check != 1)
		{
			printf("\n\t-> Is %s Female or Male (Enter M or F) : ", name);
			fgets(input,sizeof(input),stdin);
			sscanf(input,"%s",answer);
			check = checkInputGender(answer);
		}
		if (strcasecmp(answer,"M") == 0)
			printf("\n\t\t\t< %s is Male >\n\n",name );
		else	
			printf("\n\t\t\t< %s is Female >\n\n",name );
	}
	if (strcasecmp(answer,"M") == 0)
		return 1;
	else 
		return 0;
}

/** Find the return relationship of each relation
	@relationSequence - relation that user input
	@gender - gender that we know via reasoning of relation
	@return - return the relation sequence

*/
int findReturnRelationshipSequence(int relationSequence, char * gender)
	{
		char checkGender;
		if (strcasecmp(gender,"M") == 0)
			checkGender = 'M';
		else
			checkGender = 'F';

		if (relationSequence == 7) 				/*Input 7 - Wife*/
			relationSequence = 6;				/*Return 6 - Husband*/
		else if (relationSequence == 6)			/*Input 6 - Husband*/
			relationSequence = 7;				/*Return 7 - Wife*/
		else if (relationSequence == 8)			/*Input 8 - Brother*/
		{
			if (checkGender == 'M')				
			 	relationSequence = 8;			/*If Male Return 8 - Brother*/
			else if (checkGender == 'F')		
				relationSequence = 9;			/*If Female Return 9 - Sister*/
		}
		else if (relationSequence == 9)			/*Input 9 - Sister*/
		{
			if (checkGender == 'M')
			 	relationSequence = 8;			/*If Male Return 8 - Brother*/
			else if (checkGender =='F')
				relationSequence = 9;			/*If Female Return 9 - Sister*/
		}		
		else if ((relationSequence == 2) || (relationSequence == 3))		/*Input 2 - Aunt, 3- Uncle */
		{
			if (checkGender == 'M')
			 	relationSequence = 12;			/*If Male Return 12 - Grandson*/
			else if (checkGender =='F')
				relationSequence = 13;			/*If Female Return 13 - Granddaughter*/
		}
		else if ((relationSequence == 4) || (relationSequence ==5))			/*Input 4 - Father, 5 - Mother */
		{
			if (checkGender == 'M')
			 	relationSequence = 10;			/*If Male Return 10 - Son*/
			else if (checkGender == 'F')
				relationSequence = 11;			/*If Female Return 11 - Daughter*/
		}
		else if ((relationSequence == 0) || (relationSequence == 1))		/*Input 0 - Grandfather, 1 - Grandmother */
		{
			if (checkGender == 'M')				
			 	relationSequence = 12;			/*If Male Return 12 - Grandson */
			else if (checkGender == 'F')
				relationSequence = 13;			/*In Female Retrun 13 - Granddauhter */
		}
		else if ((relationSequence == 10) || (relationSequence == 11))		/*Input 10 - son, 11 - daughter */
		{
			if (checkGender == 'M')
				relationSequence = 4;			/*If Male Return 4 - Father*/
			else if(checkGender == 'F')		
				relationSequence = 5;			/*If Female Return 5 - Mother*/
		}
		else if ((relationSequence == 12) || ( relationSequence == 13))		/*Input 12 - Grandson, 13 - Granddauhter */
		{
			if ( checkGender == 'M' )
				relationSequence = 0;			/*If Male Return 0 - Grandfather */
			else if ( checkGender == 'F' )
				relationSequence = 1;			/*If Female Retrun 1 - Grandmother */
		}
		return relationSequence;		/*Return the relation sequence*/
	}

/** Dump the information in to reload file
	@Vertex - VERTEX (name) (gender)
	@EDGE - EDGE (name1) (name2) (relationship in sequence)
*/
void dumpNetworkReloadFile(char type[],char person1[],char person2[],int relationSequence)
{
	FILE * pReloadFile = NULL;
	pReloadFile = fopen("backupFile.txt","a");
	
	if (strcasecmp(type, "Edge") == 0)
	{
		/* Dump the relationship between 2 person
		 "EDGE John Marry 6" */
		fprintf(pReloadFile, "EDGE %s %s %d\n",person1,person2,relationSequence);
		
	}
	else if (strcasecmp(type, "VERTEX") == 0)
	{
		/*Dump the information of person
		"VERTEX John M" */
		fprintf(pReloadFile, "VERTEX %s %s\n",person1,person2);
	}
	fclose(pReloadFile);
}

/**Find the sequence of relationship.
  *Sequence of relationships is the number of each relation and odd number is Female, Even is Male.
  *In each relation has a number thus
  *"father" - 0, "mother" - 1, "son" - 2, "daughter" - 3, "brother" - 4, "sister" - 5, 
  *"husband" - 6, "wife" - 7, "uncle" - 8, "aunt" - 9, "grandfather" - 10, "grandmother" - 11,"grandson" - 12,"granddaughter - 13"
  @relationship Input of relationship
  @i Sequence of each relationship.
  @return i if it has sequence of relationship.
  @return -99 if not found relationship
  */
int checkSequenceOfRelationship(char *relationship)
	{
	int i = -1;  /*return the relation sequence*/
	for ( i = 0 ; i < 14; i++)
		{
			if (strcasecmp(relationship,relationSequence[i]) == 0)
				break;
		}
	return i;
	}

/** Show the option to user 
	@return - option that user input
*/
int getMenuOption()
{
 	int option = -1;  /*option that user select*/
	char input[32];

	while (option < 0)
		{
		 printf("*************************************************\n\n");
		 printf("\t    PLEASE SELECT AN OPTION : \n\n");
		 printf("     #1 : Add Relationship Between Two Person \n");
		 printf("     #2 : Ask Relationship in Family Tree\n");
		 printf("     #3 : Exit Program\n\n");
		 printf("*************************************************\n\n");

		printf(" -> Please Select Your Option : ");
		fgets(input,sizeof(input),stdin);
		sscanf(input,"%d",&option);
		

		if (option<0 || option>3)
			{
			printf("\nInvalid option : please enter 1-3\n\n");
			option = -1;
			}
		}

	printf("\n");
	return option;
}

int countSpace(char input[])
{
	int i = 0;
	int countSpaceVal = 0;

	for (i=0;i<strlen(input)-1;i++)
	{
	if (isspace(input[i]))
		countSpaceVal++;
	}

return countSpaceVal;
}


/** Ask the user to reload file
	@Yes - read the back up file and reload the graph
	@No - create the new graph
*/
void askToReloadFile(char * isReloadFile)
{
	FILE* pBackup = NULL;		/*Back Up file that use to reload */
	int bDirected = 0;			/*to create directed graph (1) */
    int maxVertices = 1000;		/*Max Vertices*/
    int retVal;					/* Check value*/
    char input[256];			

	if (strcasecmp(isReloadFile,"N")==0)
		{
		printf("\nCreate New Graph Process....\n\n");
		bDirected = 1; /*Directed Graph*/
		pBackup = fopen("backupFile.txt","w");
		fprintf(pBackup,"1000 1 \n");
	    if (!initGraph(maxVertices,bDirected))
		    printf("Error! Cannot initialize graph\n");
		else 
			printf("Create Graph Success\n\n");
		fclose(pBackup);
		}

	else
		{
		if ((isReloadFile[0] == 'Y') || (isReloadFile[0] == 'y'))
		    {
		    	/*Reload the graph*/
	          	retVal = readNetworkDefinition("backupFile.txt", 1);
	          	if (retVal == -1)
					{
					printf("Error: Failed Reading Data From Backup File\n");
					exit(0);
					}
				printf("\n\n\tFinished Reading Backup File !\n\n");
		    }
		
		}
}

/** Add person to the network if that person doesn't exist in network
	and dump the information of person into backUp file
	@person1 - name of the first person
	@person2 - name of the second person
	@genderPerson1 - gender of the first person
	@genderPerson2 - gender of the second person
*/
void addPersonToNetwork (char * person1, char * person2, char * genderPerson1, char* genderPerson2)
{
	int retVal ;		/*check that add successful or not*/
	void * check;		/*store the data of vertex*/

	check = findVertex(person1);
	if (check == NULL)
   	{
    	retVal = 0;
   		retVal = addVertex(person1,genderPerson1);
		if (retVal == 1) 
        {
		    printf("\t'%s' added into Family Tree\n",person1);
		    /*dump person1 into back up file with name and gender*/
		    dumpNetworkReloadFile("VERTEX",person1,genderPerson1,-99);

		}
		else 
      		printf("\tMemory allocation error or graph full!\n");
	}

	check = findVertex(person2);
   	if (check == NULL)
   	{
   		retVal = 0;
   		retVal = addVertex(person2,genderPerson2);
	    if (retVal == 1) 
		{
		    printf("\t'%s' added into Family Tree\n",person2);
		    /*dump person1 into back up file with name and gender*/
		    dumpNetworkReloadFile("VERTEX",person2,genderPerson2,-99);
		}
		else 
	        printf("\tMemory allocation error or graph full!\n");
	}
}

/** Create relation between 2 person and dump the relation into back up file
	@person1 - name of the first person
	@person2 - name of the second person
	@sequenceInRelationship - sequence of relationship between 2 persons
	@genderPerson1 - gender of the first person
	@genderPerson2 - gender of the second person
*/
void addRelationshipBetweenTwoPerson (char * person1, char * person2, int sequenceInRelationship, char * genderPerson1, char * genderPerson2)
{
	int retVal = 0;

	retVal = addEdge(person1,person2,sequenceInRelationship); 
  	if (retVal == 1) 
		{
	       	printf("\tAdded relationship from '%s' to '%s' with relationship %s\n",person1,person2,relationSequence[sequenceInRelationship]);
	       	dumpNetworkReloadFile("EDGE",person1,person2,sequenceInRelationship);
	       	sequenceInRelationship = findReturnRelationshipSequence(sequenceInRelationship,genderPerson2);

			retVal = addEdge(person2,person1,sequenceInRelationship); 
		  	if (retVal == 1) 
				{
		       	printf("\tAdded relationship from '%s' to '%s' with relationship %s\n",person2,person1,relationSequence[sequenceInRelationship]); 
		       	dumpNetworkReloadFile("EDGE",person2,person1,sequenceInRelationship);
		       	}
		    
       	}
}

/* this function will return count which is use ti validate also return relanum,
 * @relanum - value to specify relationship */

int getRelationNum(char* person1,char* person2,int * relanum )
{
	/* declare variables */
   char** adjacentKeys = NULL;  /* use to hold adjacent of first person */
   int count = 0;

   adjacentKeys = getAdjacentVertices(person1,&count);

   if( count == 0 )
   {
      printf(" '%s' has no relationship\n",person1);
   }
   else
   {
      for(int k=0;k<count;k++)
      {
         if( strcasecmp(adjacentKeys[k],person2) == 0 )
         {
            *relanum = findEdge(person1,adjacentKeys[k]);
         }
      }
   }
   free(adjacentKeys);
   return count;
}

/* this function will get person1 , person2 and relationValue then find gender of both person
   lastly add relation between them */
void addRelationOnTheWay(int relationValue,char* person1, char* person2)
{
	/* declare variables */
   char* genderF;                  /* first person's gender */
   char* genderS;                  /* second person's gender */
   void* genderFromVertex = NULL;
   int check = 99;

   	check = 99;
   	check = findGenderOfPerson(person1,"N");
   	if (check == 1)
   		genderF = "M";
   	else if (check == 0)
   		genderF = "F";
   	check =99;
   	check = findGenderOfPerson(person2,"N");
   	if (check == 1)
   		genderS = "M";
   	else if (check == 0)
   		genderS = "F";


  if( strcasecmp(genderF,"M") == 0 )
  {
     addRelationshipBetweenTwoPerson(person1,person2,2*relationValue,genderF,genderS);
  }
  else if(strcasecmp(genderF,"F") == 0)
  {
     addRelationshipBetweenTwoPerson(person1,person2,(2*relationValue)+1,genderF,genderS);
  }
}

/* this function will combine relation between first person and last person
   by using pop() 3 first person then group their relationship together then
   pop until loop is over by the way this function will add relation on path */
void combineRelationByStack(int pathCount)
{
	/* declare variables */
    int count = 0;
    int checkRelationship = 0;       /* use to check relation between person */
    int relationValue = 0;           /* combined relation */
    int axis[2] = {0};               /* hold relationship of both x and y axis */
    char **vertexKey = NULL;
    char** adjacentKeys = NULL;
    int i = 0;

    vertexKey = calloc(pathCount,sizeof(char*));
   if( pathCount >= 3 )
   {
      for(int round = 0; round<pathCount; round++)
      {
          vertexKey[round] = pop();

          /* if we pop 2 or 3 time we will merge relation together 
             and add relation from first and third person */
          if( ( round == 1 ) || ( round == 2 ) )
          {
            count = getRelationNum(vertexKey[round-1],vertexKey[round],&checkRelationship);

              if( ( ( round == 1 ) || ( round == 2 ) ) &&  ( count != 0 ) )
              {
                 for(int i = 0;i<7;i++ )
                 {
                     if(   ( strcasecmp(relationSequence[checkRelationship],relationSequence[2*i]) == 0 )
                        || ( strcasecmp(relationSequence[checkRelationship],relationSequence[2*i+1]) == 0 ) )
                     {
                         axis[round-1] = i;
                         break;
                     }
                 }

                if( round == 2 )
                {

                   if( combineRelation[axis[0]][axis[1]] == -1 )
                   {
                       printf("There Is No Relationship Available !\n");
                   }
                   else
                   {
                      /** relation from first person to third person **/
                      relationValue = combineRelation[axis[0]][axis[1]];
                      addRelationOnTheWay(relationValue,vertexKey[0],vertexKey[2]);
                   }
                }
              }
          }
          /* we will use relationValue from before and then continue to pop one person
             and link relationhip from first and current person */
          if( round > 2 )
          {
                 count = getRelationNum(vertexKey[round-1],vertexKey[round],&checkRelationship);

                 if( count != 0 )
                 {
                    for(i = 0;i<7;i++ )
                    {
                       if(   ( strcasecmp(relationSequence[checkRelationship],relationSequence[2*i]) == 0 )
                          || ( strcasecmp(relationSequence[checkRelationship],relationSequence[2*i+1]) == 0 ) )
                          {
                              axis[1] = i;
                          }
                    }
                 }

                 relationValue = combineRelation[relationValue][axis[1]];
                 if( relationValue == -1 )
                 {
                 	printf("There Is No Relation Available.\n");
                 }
                 else
                 {
                    addRelationOnTheWay(relationValue,vertexKey[0],vertexKey[round]);
                 }

          }
      }
   }
   stackClear();
   free(vertexKey);
   free(adjacentKeys);
}


/** Print the relationship between 2 person
	@keystring1 - name of first person
	@keystring2 - name of second person
	@return 1 if relation has exist
*/
int printRelationship(char * keystring1,char * keystring2)
{
	char** adjacentKeys = NULL;
	int i = 0;							/*counter*/
	int count = -1;						/*store the number of adjacent key*/
	int checkRelationship = -2;			/*store the relation sequence that return from findEdge*/
	int exist = 0; 						/*check if it doesn't has relation return 0*/

    adjacentKeys = getAdjacentVertices(keystring1,&count);
    if (count == 0)
		   	printf(" '%s' has no relationship\n",keystring2);
    else if (count < 0)
	   		printf(" '%s' does not exist in Family Tree\n",keystring1);
	else
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	      if (strcasecmp(adjacentKeys[i],keystring2) == 0)
	      	{
		      checkRelationship = findEdge(keystring1,adjacentKeys[i]);
		      printf("\n\n\t\t|  %s",keystring1);
              printf(" %s ", relationSequence[checkRelationship]);
              printf("%s  | \n\n",adjacentKeys[i]);
              exist = 1;
		      free(adjacentKeys[i]);
	      	}
	      }
	   free(adjacentKeys);
				   }
	return exist;
}

/** Create the relationship via reasoning system
	@person1 - name of first person
	@person2 - name of second person
*/
void makeRelationshipsReasoningSystem(char * person1, char * person2)
{
	int count = 0; /*store variable of the stackSize*/
	int i = 0; /*counter*/
	
	i = printRelationship(person1,person2);
	if (i != 1)
	{	
		
		isReachablePrintPath(person1,person2);
	
		count = stackSize();
		if (count == 0)
			printf("\tNo relationship between %s and %s \n",person1,person2 );
		else if (count > 2)
		{	
			if (count > 2)
				combineRelationByStack(count);
			printRelationship(person1,person2);
		}


	}

}

/** Check input of user 
	@person - name of person
	@relationship - relation between 2 person
	@return if it all correct return 1
	@retrun - wrong return 0
*/
int checkInputRelation(char * person1,char * relationship,char *person2)
{
	int bOk = 99; /*use to check the illegal character and return the function*/
	int i; /*counter*/

	for ( i = 0; i < 14; ++i)
	{
		if(strcasecmp(relationship,relationSequence[i]) == 0)
		{
			bOk = 1;
			break;
		}
		else 
			bOk = 0;
	}

	for ( i = 0; i < strlen(person1) ; i++)
	{
		if(ispunct(person1[i]) != 0)
		{
			bOk = 0;
			break;
		}
		else if (isdigit(person1[i]) != 0)
		{
			bOk = 0;
			break;	
		}
	}

	for ( i = 0; i < strlen(person2) ; i++)
	{
		if(ispunct(person2[i]) != 0)
		{
			bOk = 0;
			break;
		}
		else if (isdigit(person2[i]) != 0)
		{
			bOk = 0;
			break;	
		}
	}

	for ( i = 0; i < strlen(relationship) ; i++)
	{
		if(ispunct(relationship[i]) != 0)
		{
			bOk = 0;
			break;
		}
		else if (isdigit(relationship[i]) != 0)
		{
			break;
			bOk = 0;	
		}
	}
	return bOk;
}
/** Check the Illegal relationship by chec from adjacent
	@focusPoing - the vertex that you want to check
	@return - result value
*/
int checkIllegal(char* focusPoint)
{
	char** adjacentKeys = NULL;
	int i = 0;						/*counter*/
	int count = 0;					/*counter*/
	int edgeValue = 0;				/*weigt of each weight and that is relation sequence*/
	int countGrandFather = 0;		/*counter of granfather */
	int countFather = 0; 			/*counter of father*/
	int countHusband = 0;			/*counter of husband*/
	int countGrandMother =0;		/*counter of grand mother*/
	int countWife = 0;				/*counter of wife*/
	int countMother = 0;			/*couuter of mother*/
	int retVal = 0;					/*result value that use to return the value*/

	adjacentKeys = getAdjacentVertices(focusPoint,&count);
  
	if (count > 0)
	   {
	    
	   for (i = 0; i < count; i++)
	      {
	      	edgeValue = findEdge(focusPoint,adjacentKeys[i]);

	      if(edgeValue != -1)
        		{
          		if(edgeValue%2 == 0)
          			{
            		if (edgeValue == 0)
              			countGrandFather++;
            		else if (edgeValue == 4)
              			countFather++;
            		else if (edgeValue == 6)
              			countHusband++;
          			}
          		else
          			{
            		if (edgeValue == 1)
              			countGrandMother++;
            		else if (edgeValue == 5)
              			countMother++;
            		else if (edgeValue == 7)
              			countWife++;
          			}
        		}
	      }
	    }
  
  if(countHusband >= 1)
    retVal = -1;
  else if (countWife >= 1)
    retVal = -2;  
  else if (countFather >= 1)
    retVal = -3;  
  else if (countMother >=1)
    retVal = -4;  
  else if (countGrandFather >=2)
    retVal = -5;
  else if (countGrandMother >=2)
    retVal = -6;

  return retVal;

}

/** Check the illegal logic before we add into the network if it illegal return 1
	@person1 - name of the first person of input
	@person2 - name of the second person of input
	@relationship - relationship between 2 persons from input
	@genderPerson1 - gender of the first (we know gender person1 from relationship)
	@return - If it illegal return -1 
*/
int checkLogicRelationship (char* person1,char* person2,char* relationship,char *genderPerson1)
{	
	int value = 1;					/*Value that use to check*/
	int countAdjacent1 = 0;			/*counter adjacent of first person*/
	int countAdjacent2 = 0;			/*counter adjacent of second person*/
	int error = 0;					/*Return Value*/
	countAdjacent1 = countAdjacentByKey(person1);
	countAdjacent2 = countAdjacentByKey(person2);
			
				if ((strlen(person1) == 0) || (strlen(genderPerson1) == 0))
				   	{
				   		printf("Input error - key or data empty!\n");
				
				    }
				else
					{
					if (strcasecmp(relationship,"FATHER")==0 || strcasecmp(relationship,"MOTHER")==0 || strcasecmp(relationship,"GRANDFATHER")==0 || strcasecmp(relationship,"GRANDMOTHER")==0)
						{ 
						if (countAdjacent2 != -1 && countAdjacent2 != 0)
							{
							if (strcasecmp(relationship,"FATHER")==0)
						    	{
						      	value = checkIllegal(person2);
						      	if (value == -3)
						      		error = 1;
						      	}
						  	else if (strcasecmp(relationship,"MOTHER")==0)
						    	{
						     	value = checkIllegal(person2);
						     	if (value == -4)
						      		error = 1;
						    	}
						    else if (strcasecmp(relationship,"GRANDFATHER")==0)
						    	{
						      	value = checkIllegal(person2);
						      	if (value == -5)
						      		error = 1;
						      	}
						    else if (strcasecmp(relationship,"GRANDMOTHER")==0)
						    	{
						      	value = checkIllegal(person2);
						      	if (value == -6)
						      		error = 1;
						      	}
							}
						}
					else if (strcasecmp(relationship,"SON")==0 || strcasecmp(relationship,"DAUGHTER")==0 || strcasecmp(relationship,"GRANDSON")==0 || strcasecmp(relationship,"GRANDDAUGHTER")==0)
						{
						if (countAdjacent1 != -1 && countAdjacent1 != 0)
							{
						    if (strcasecmp(relationship,"SON")==0 || strcasecmp(relationship,"DAUGHTER")==0)
						    	{
						      	value = checkIllegal(person1);
						      	if (value == -3 || value == -4)
						      		error = 1;
						      	}
						    else if (strcasecmp(relationship,"GRANDSON")==0 || strcasecmp(relationship,"GRANDDAUGHTER")==0)
						    	{
						      	value = checkIllegal(person1);
						      	if (value == -5 || value == -6)
						      		error = 1;
						      	}
					      	}
					    }
					else if (strcasecmp(relationship,"HUSBAND")==0 || strcasecmp(relationship,"WIFE")==0)      	
						{
						if (countAdjacent1 != -1 && countAdjacent1 != 0)
							{
							if (strcasecmp(relationship,"HUSBAND")==0)
					    		{
					      		value = checkIllegal(person1);
					      		if (value == - 1)
					      			error = 1;
					      		}
					      	else if (strcasecmp(relationship,"WIFE")==0)
					    		{
					      		value = checkIllegal(person1);
					      		if (value == -2)
					      			error = 1;
					      		}
					      	}
					    if (countAdjacent2 != -1 && countAdjacent2 != 0)
					    	{
							if (strcasecmp(relationship,"HUSBAND")==0)
					    		{
					      		value = checkIllegal(person2);
					      		if (value == - 1)
					      			error = 1;
					      		}
					      	else if (strcasecmp(relationship,"WIFE")==0)
					    		{
					      		value = checkIllegal(person2);
					      		if (value == -2)
					      			error = 1;
					      		}
							}
						}
					}

		return error;

}





