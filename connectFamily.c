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

void addPersonToNetwork (char * person1, char * person2, char * genderPerson1, char* genderPerson2);
void addRelationshipBetweenTwoPerson (char * person1, char * person2, int sequenceInRelationship, char * genderPerson1, char * genderPerson2);
int findGenderOfPerson(char name[],char genderInput[]);


/** Find gender or validate gender 
	return - gender in char* "M" or "F" 
*/
char * findGender(char * person,char * gender)
{
	int genderCheck = -1;
	char * genderReturn;
	genderCheck = findGenderOfPerson(person,gender);
	if (genderCheck == 1)
		genderReturn = "M";
	else if (genderCheck == 0)
		genderReturn = "F";
	else
		printf("Not Found Gender !\n");
	return genderReturn;
}


/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Husband" and "Wife" relationships. And then connect relationship 
  between that persons.
*/
void linkHusbandWife(char * person1,char * relationship,char * person2,char * genderPerson2)
{
	char ** adjacentKeys;
	int checkRelationSeq = -1;
	char * genderPerson1;
	char * genderTemp;
	int genCheck = -1;
	int count = -1;
	if (strcasecmp(relationship,"Husband") == 0)
	{	
		genderPerson1 = "M";

		adjacentKeys = getAdjacentVertices(person1,&count);
	    if (count > 0)
		   	{
		   	int i = 0;
		   	for (i = 0; i < count; i++)
		      	{
		      		checkRelationSeq = findEdge(person1,adjacentKeys[i]);
		      		if  (checkRelationSeq == 4)
		      		{
		      			genderTemp = findGender(adjacentKeys[i],"N");
		      			if (strcasecmp(genderTemp,"M") == 0)
		      				addRelationshipBetweenTwoPerson(adjacentKeys[i],person2,10,genderTemp,genderPerson2);
		      			else
		      				addRelationshipBetweenTwoPerson(adjacentKeys[i],person2,11,genderTemp,genderPerson2);
		      		}
		      }
		   free(adjacentKeys);
			}

		adjacentKeys = getAdjacentVertices(person2,&count);
	    if (count > 0)
		   	{
		   	int i = 0;
		   	for (i = 0; i < count; i++)
		      	{
		      		checkRelationSeq = findEdge(person2,adjacentKeys[i]);
		      		if ((checkRelationSeq == 10)||(checkRelationSeq == 11))
		      		{
		      			genderTemp = findGender(adjacentKeys[i],"N");
		      			if (strcasecmp(genderTemp,"F") == 0)
		      				addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],4,genderTemp,genderPerson1);
		      		}
		      }
		   free(adjacentKeys);
			}

	}

	if (strcasecmp(relationship,"Wife") == 0)
	{	
		genderPerson1 = "F";
		adjacentKeys = getAdjacentVertices(person1,&count);
	    if (count > 0)
		   	{
		   	int i = 0;
		   	for (i = 0; i < count; i++)
		      	{
		      		checkRelationSeq = findEdge(person1,adjacentKeys[i]);
		      		if  (checkRelationSeq == 5)
		      		{
		      			genderTemp = findGender(adjacentKeys[i],"N");
		      			if (strcasecmp(genderTemp,"M") == 0)
		      				addRelationshipBetweenTwoPerson(adjacentKeys[i],person2,10,genderTemp,genderPerson2);
		      			else
		      				addRelationshipBetweenTwoPerson(adjacentKeys[i],person2,11,genderTemp,genderPerson2);
		      		}
		      }
		   free(adjacentKeys);
			}

		adjacentKeys = getAdjacentVertices(person2,&count);
	    if (count > 0)
		   	{
		   	int i = 0;
		   	for (i = 0; i < count; i++)
		      	{
		      		checkRelationSeq = findEdge(person2,adjacentKeys[i]);
		      		if ((checkRelationSeq == 10)||(checkRelationSeq == 11))
		      		{
		      			genderTemp = findGender(adjacentKeys[i],"N");
		      			if (strcasecmp(genderTemp,"F") == 0)
		      				addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],5,genderTemp,genderPerson1);
		      		}
		      }
		   free(adjacentKeys);
			}

	}
}

/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Father" and "Mother" relationships.And then connect relationship 
  between that persons.
*/
void linkFatherAndMother(char* keystring1,char * relationship,char* keystring2,char * gender)
{
	char** adjacentKeys = NULL;
	int i = 0;
	int count = 0;
	int checkRelationship = 0;
	char * personGender;
	int genderS = 0;
	int edgeValue = 0;
	char * personToInsert;
	char* genderOfPerson;
	

 if (strcasecmp(relationship,"Father") == 0)
 {
 	
    adjacentKeys = getAdjacentVertices(keystring1,&count);
  
	if (count > 0)
	   {
	   int i = 0;
	    
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2) != 0 )
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"N");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 6)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (personToInsert,keystring2,5,genderOfPerson,gender);
	      	  	}
	      	  else if (edgeValue == 4)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,8,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,9,genderOfPerson,gender);
	      	  	}
	      	  else if (edgeValue == 8)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,2,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,3,genderOfPerson,gender);
	      	  	}
	      	  else if (edgeValue == 0)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,10,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,11,genderOfPerson,gender);
	      	  	}
	      	  else if (edgeValue == 10)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,0,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,1,genderOfPerson,gender);
	      	  	}	   	  	
	      	}
	     
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	 	if ((edgeValue == 4) || (edgeValue == 5))
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,0,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 10 || edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  		if (genderS != 1)
	      	  			addRelationshipBetweenTwoPerson (keystring2,personToInsert,6,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,4,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 12 || edgeValue == 13)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,10,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 2 || edgeValue == 3)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,0,genderOfPerson,gender);
	      	  	}  	
	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
 }

 else //mother
{
	adjacentKeys = getAdjacentVertices(keystring1,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 7)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (personToInsert,keystring2,4,genderOfPerson,gender);
	      	  	}
	      	  else if (edgeValue == 5)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,8,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,9,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,2,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,3,genderOfPerson,gender);
	      	  	}
	      	  else if (edgeValue == 1)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,10,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,11,genderOfPerson,gender);
	      	  	}
	      	  else if (edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,0,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,1,genderOfPerson,gender);
	      	  	}	      	  	
	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

   if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 4 || edgeValue == 5)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,1,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 10 || edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  		if (genderS == 1)
	      	  			addRelationshipBetweenTwoPerson (keystring2,personToInsert,7,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,5,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 12 || edgeValue == 13)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,11,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 2 || edgeValue == 3)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,1,genderOfPerson,gender);
	      	  	}  	
	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
   
 }

}


/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "GrandFather" and "GrandMother" relationships.And then connect relationship 
  between that persons.
*/
void linkGrandFatherMother(char* person1,char* person2,char* relationship,char* genderSecond)
{
    char** adjacentKeys = NULL;
    int count = 0;
    int relaVal = 0;
    char* genderFirst;
    char* genderTemp;
    int genderFromVertex = -1;

    if (strcasecmp(relationship,"GrandFather") == 0)
    {
       genderFirst = "M";

       adjacentKeys = getAdjacentVertices(person2,&count);
       if (count > 0)
       {
           for(int i=0;i<count;i++)
           {
              if(strcasecmp(person1,adjacentKeys[i]) != 0 )
              {
                 genderFromVertex = findGenderOfPerson(adjacentKeys[i],"N");
                 if( genderFromVertex == 1 )
                    genderTemp = "M";
                 else
                    genderTemp = "F";

                 relaVal = findEdge(person2,adjacentKeys[i]);

                 if(relaVal == 10) 
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],4,genderFirst,genderTemp);
                 else if( relaVal == 11 ) 
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],4,genderFirst,genderTemp);
                 else if( relaVal == 8 )  
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],0,genderFirst,genderTemp);
                 else if( relaVal == 9 ) 
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],0,genderFirst,genderTemp);
              }
           }
       }

       adjacentKeys = getAdjacentVertices(person1,&count);
       if (count > 0)
       {
           for(int i=0;i<count;i++)
           {
              if(strcasecmp(person1,adjacentKeys[i]) != 0 )
              {
                 genderFromVertex = findGenderOfPerson(adjacentKeys[i],"N");
                 if( genderFromVertex == 1 )
                    genderTemp = "M";
                 else
                    genderTemp = "F";

                 relaVal = findEdge(person1,adjacentKeys[i]);
                 
                 if(relaVal == 10) 
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],4,genderSecond,genderTemp);
                 else if( relaVal == 11 ) 
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],4,genderSecond,genderTemp);
                 else if( relaVal == 8 )  
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],0,genderSecond,genderTemp);
                 else if( relaVal == 9 ) 
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],0,genderSecond,genderTemp);
              }
           }
       }
    }

    if (strcasecmp(relationship,"GrandMother") == 0)
    {
       genderFirst = "F";

       adjacentKeys = getAdjacentVertices(person2,&count);

       if (count > 0)
       {
           for(int i=0;i<count;i++)
           {
              if(strcasecmp(person2,adjacentKeys[i]) == 0 )
              {
                 genderFromVertex = findGenderOfPerson(adjacentKeys[i],"N");
                 if( genderFromVertex == 1 )
                    genderTemp = "M";
                 else
                    genderTemp = "F";

                 relaVal = findEdge(person2,adjacentKeys[i]);
                 if(relaVal == 10) 
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],5,genderSecond,genderTemp);
                 else if( relaVal == 11 )
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],5,genderSecond,genderTemp);
                 else if( relaVal == 8 )  
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],1,genderSecond,genderTemp);
                 else if( relaVal == 9 )
                     addRelationshipBetweenTwoPerson(person1,adjacentKeys[i],1,genderSecond,genderTemp);
                 
              }
           }
       }

       adjacentKeys = getAdjacentVertices(person1,&count);

       if (count > 0)
       {
           for(int i=0;i<count;i++)
           {
              if(strcasecmp(person1,adjacentKeys[i]) == 0 )
              {
                 genderFromVertex = findGenderOfPerson(adjacentKeys[i],"N");
                 if( genderFromVertex == 1 )
                    genderTemp = "M";
                 else
                    genderTemp = "F";

                 relaVal = findEdge(person1,adjacentKeys[i]);
                 if(relaVal == 10) 
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],5,genderFirst,genderTemp);
                 else if( relaVal == 11 ) 
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],5,genderFirst,genderTemp);
                 else if( relaVal == 8 )  
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],1,genderFirst,genderTemp);
                 else if( relaVal == 9 ) 
                     addRelationshipBetweenTwoPerson(person2,adjacentKeys[i],1,genderFirst,genderTemp);
              }
           }
       }
    }
}



/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Sonr" and "Daughter" relationships.And then connect relationship 
  between that persons.
*/
void linkSonAndDaughter(char* keystring1,char * relationship,char* keystring2,char * gender)
{
	char** adjacentKeys = NULL;
	int i = 0;
	int count = 0;
	int checkRelationship = 0;
	char * personGender;
	int genderS = 0;
	int edgeValue = 0;
	char * personToInsert;
	char* genderOfPerson;
	

 if (strcasecmp(relationship,"Son") == 0)
 {
 	//find the adjacentkeys of keystring1
    adjacentKeys = getAdjacentVertices(keystring1,&count);
  
	if (count > 0)
	   {
	   int i = 0;
	    
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"N");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 4)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,12,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,13,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 10)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (strcasecmp(gender,"M") != 0 && genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,6,genderOfPerson,gender);
	      	    else if (strcasecmp(gender,"M") == 0 && genderS != 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,7,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,2,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,3,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 2)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,12,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,13,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 6)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS != 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,5,genderOfPerson,gender);
	      	  	}	   	  	
	      	}
	     
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	 	if ((edgeValue == 1) || (edgeValue == 0))
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,4,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 4 || edgeValue == 5)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,8,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 10 || edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,12,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,12,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 6 || edgeValue == 7)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,10,genderOfPerson,gender);
	      	  	}  	
	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
 }

 else //daughter
{
    adjacentKeys = getAdjacentVertices(keystring1,&count);
  
	if (count > 0)
	   {
	   int i = 0;
	    
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"N");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 5)//here
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,12,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,13,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (strcasecmp(gender,"M") != 0 && genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,6,genderOfPerson,gender);
	      	    else if (strcasecmp(gender,"M") == 0 && genderS != 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,7,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,2,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,3,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 3)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,12,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,13,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 7)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,4,genderOfPerson,gender);
	      	  	}	   	  	
	      	}
	      free(adjacentKeys[i]);	     
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	 	if ((edgeValue == 1) || (edgeValue == 0))
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,5,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 4 || edgeValue == 5)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,9,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 10 || edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,13,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,13,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 6 || edgeValue == 7)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,11,genderOfPerson,gender);
	      	  	}  	
	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
   
 }
}


/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Uncle" and "Aunt" relationships.And then connect relationship 
  between that persons.
*/
void linkUncleAndAunt(char* keystring1,char * relationship,char* keystring2,char * gender)
{
	char** adjacentKeys = NULL;
	int i = 0;
	int count = 0;
	int checkRelationship = 0;
	char * personGender;
	int genderS = 0;
	int edgeValue = 0;
	char * personToInsert;
	char* genderOfPerson;
	

 if (strcasecmp(relationship,"Uncle") == 0)
 {
 	//find the adjacentkeys of keystring1
    adjacentKeys = getAdjacentVertices(keystring1,&count);
  
	if (count > 0)
	   {
	   int i = 0;
	    
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"N");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 10)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  	 {
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,0,genderOfPerson,gender);
	      	  	}
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,1,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,2,genderOfPerson,gender);
	      	    else 
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,3,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 2)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,8,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,9,genderOfPerson,gender);
	      	  	}
	      	}
	     
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	 	if ((edgeValue == 10) || (edgeValue == 11))
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,8,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,2,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 12 || edgeValue == 13)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,10,genderOfPerson,gender);
	      	  	}
	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
 }

 else //daughter
{
    adjacentKeys = getAdjacentVertices(keystring1,&count);
  
	if (count > 0)
	   {
	   int i = 0;
	    
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"N");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,0,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,1,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,2,genderOfPerson,gender);
	      	    else 
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,3,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 3)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,8,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,9,genderOfPerson,gender);
	      	  	}
	      	}
	      free(adjacentKeys[i]);	     
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	 	if ((edgeValue == 10) || (edgeValue == 11))
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,9,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,3,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 12 || edgeValue == 13)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,11,genderOfPerson,gender);
	      	  	}
	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
   
 }
}


/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Brother" and "Sister" relationships.And then connect relationship 
  between that persons.
*/
void linkBrotherAndSister(char* keystring1,char * relationship,char* keystring2,char * gender)
{
	char** adjacentKeys = NULL;
	int i = 0;
	int count = 0;
	int checkRelationship = 0;
	char * personGender;
	int genderS = 0;
	int edgeValue = 0;
	char * personToInsert;
	char* genderOfPerson;
	

 if (strcasecmp(relationship,"Brother") == 0)
 {
 	//find the adjacentkeys of keystring1
    adjacentKeys = getAdjacentVertices(keystring1,&count);

	if (count > 0)
	   {
	   int i = 0;
	    
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"N");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	  if (edgeValue == 10)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,4,genderOfPerson,gender);
	      	    else 
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,5,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,8,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,9,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 12)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,0,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,1,genderOfPerson,gender);
	      	  	}
	      	}
	     
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	 	if ((edgeValue == 4) || (edgeValue == 5))
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,2,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 10 || edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,10,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,8,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 12 || edgeValue == 13)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,12,genderOfPerson,gender);
	      	  	}

	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
 }

 else //daughter
{
    adjacentKeys = getAdjacentVertices(keystring1,&count);
  
	if (count > 0)
	   {
	   int i = 0;
	    
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring2)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"N");
	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);
				
				if (edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	 if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,4,genderOfPerson,gender);
	      	    else 
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,5,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,8,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,9,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 13)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	    if (genderS == 1)
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,0,genderOfPerson,gender);
	      	    else
	      	  		addRelationshipBetweenTwoPerson (personToInsert,keystring2,1,genderOfPerson,gender);
	      	  	}
	      	}
	      free(adjacentKeys[i]);	     
	      }
	   free(adjacentKeys);
	 }
//start check keystring2

	 adjacentKeys = getAdjacentVertices(keystring2,&count);

    if (count > 0)
	   {
	   int i = 0;
	   
	   for (i = 0; i < count; i++)
	      {
	       if (strcasecmp(adjacentKeys[i],keystring1)!=0)
	      	{
	      		genderS = findGenderOfPerson(adjacentKeys[i],"n");

	      		if(genderS==1)
	      			genderOfPerson = "M";
	      		else
	      			genderOfPerson = "F";

	      		edgeValue = findEdge(keystring1,adjacentKeys[i]);

	      	 	if ((edgeValue == 4) || (edgeValue == 5))
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,3,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 10 || edgeValue == 11)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,11,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 8 || edgeValue == 9)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,9,genderOfPerson,gender);
	      	  	}

	      	  else if (edgeValue == 12 || edgeValue == 13)
	      	  	{
	      	  	personToInsert = adjacentKeys[i];
	      	  	addRelationshipBetweenTwoPerson (keystring2,personToInsert,13,genderOfPerson,gender);
	      	  	}

	      	}
	      free(adjacentKeys[i]);
	      }
	   free(adjacentKeys);
	 }
   
 }

}