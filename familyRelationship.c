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

int findGenderOfPerson(char name[],char genderInput[]);
int checkSequenceOfRelationship(char *relationship);
int getMenuOption();
int countSpace(char input[]);
void askToReloadFile(char * isReloadFile);
void addPersonToNetwork (char * person1, char * person2, char * genderPerson1, char* genderPerson2);
void addRelationshipBetweenTwoPerson (char * person1, char * person2, int sequenceInRelationship, char * genderPerson1, char * genderPerson2);
void makeRelationshipsReasoningSystem(char * person1, char * person2);
int checkInputRelation(char * person1,char * relationship,char * person2);
int printRelationship(char * keystring1,char * keystring2);

void linkFatherAndMother(char* keystring1,char * relationship,char* keystring2,char * gender);
void linkGrandFatherMother(char* person1,char* person2,char* relationship,char* genderSecond);
void linkUncleAndAunt(char* keystring1,char * relationship,char* keystring2,char * gender);
void linkSonAndDaughter(char* keystring1,char * relationship,char* keystring2,char * gender);
void linkBrotherAndSister(char* keystring1,char * relationship,char* keystring2,char * gender);
void linkHusbandWife(char * person1,char * relationship,char * person2,char * genderPerson2);

int checkLogicRelationship (char * person1,char* person2,char * relationship,char *genderPerson1);

int main()
{
	char input[256];
	int option = 0;					/*Option that user input*/				
	char person1[64] = "";			/*Person1 that user input*/
    char person2[64] = "";			/*Person2 that user input*/		
    char relationship[64] = "";		/*Relationship that user input*/
   	int sequenceInRelationship;		/*Sequence of relationship*/
    int retVal = 0;					/*Use to check the illegal*/
    char * genderPerson1;			/*Gender of person1*/
    char* genderPerson2;			/*GEnder of person2*/
    int countSpaceVal = 0;			/*Counter of Space*/
    int i = 0;						/*Counter*/
    int bOk = 99;					/*Check the gender*/
    int checkCharacter = 0;			/*Check the illegal input*/

	printf("\n\n\n  ! WELCOME TO FAMILY RELATIONSHIP REASONING SYSTEM !\n\n");
	printf("Do You Want To Reload Data From Backup File? ( Y/N ) : ");
	fgets(input,sizeof(input),stdin);
	sscanf(input,"%s",input);

	askToReloadFile(input);

	option = getMenuOption();

	while (option != 3)
		{
		switch (option)
			{
			case 1: 
				printf("\nMENU 1 : Add Relationship (Person Relationship Person)\n\n");
				checkCharacter = 0;

				/* Valitdate of Illegal characteristics */
				while(checkCharacter != 1)
				{
					printf("\n\t-> Input The Relationship : ");
					memset(input,0,sizeof(input));
					fgets(input,sizeof(input),stdin);
					sscanf(input,"%s %s %s",person1,relationship,person2);
					checkCharacter = checkInputRelation(person1,relationship,person2);
					if (checkCharacter != 1)
					printf("\n\tInvalid, Please Try Again !\n");
				}

				countSpaceVal = 0;
				countSpaceVal = countSpace(input);

				if ((countSpaceVal != 2) || (strlen(person1)==0) || (strlen(person2) == 0) || (strlen(relationship) == 0))
					{
					 printf("\t -> Please Enter an Input in Form (Person Relationship Person)\n");
					 break;
					}
				
				/* Change ( Char* )the relationship into ( int ) the sequence of relationship*/
				sequenceInRelationship = checkSequenceOfRelationship(relationship);
				if (sequenceInRelationship == -99)
				{
					printf("\n\tRelationship Doesn't Found \n");
					break;
				}

				/* Find the gender of first person via the relationship from input */
				else if (sequenceInRelationship%2 == 0)
					genderPerson1 = "M";
				else if (sequenceInRelationship%2 == 1)
					genderPerson1 = "F";


				if (sequenceInRelationship == 6)
					genderPerson2 = "F";
				else if (sequenceInRelationship == 7)
					genderPerson2 = "M";
				else
				{
					bOk = findGenderOfPerson(person1,genderPerson1);
					if (bOk == -1)
						break;
					bOk = 99;
					bOk = findGenderOfPerson(person2,"N");
					if (bOk == 1)
						genderPerson2 = "M";
					else if (bOk == 0)
						genderPerson2 = "F";
				}

				bOk = 99;
				bOk = checkLogicRelationship (person1, person2,relationship,genderPerson1);

				if (bOk == 1)
					printf("\n\t!! Error, illegal relationship !!\n");
				else 
				{
					if ((strlen(person1) == 0) || (strlen(genderPerson1) == 0))
					   	printf("\n\tInput Error !\n");
					else
						{ 
							/* Add Person into network (Create VERTEX) */
							addPersonToNetwork(person1, person2, genderPerson1, genderPerson2);
					   	  	if ((sequenceInRelationship > 14)||(sequenceInRelationship < 0 ))
					      		continue;

					      	/* Create the relation between people (Created the EDGE between VERTEX)
					         * And the weight of EDGE is the relationship sequence*/
					      	addRelationshipBetweenTwoPerson(person1,person2,sequenceInRelationship, genderPerson1, genderPerson2);

					      	/* Check the adjacent of each vertex of each relationship ot find some relation
					      	 * That we can connect it togther.
					      	 */
					      	if ((strcasecmp(relationship,"Husband") == 0)||(strcasecmp(relationship,"Wife") == 0))
					      		linkHusbandWife(person1,relationship,person2,genderPerson2);
					      	else if ((strcasecmp(relationship,"Father") == 0)||(strcasecmp(relationship,"Mother") == 0))
					      		linkFatherAndMother(person1,relationship,person2,genderPerson2);
					      	else if ((strcasecmp(relationship,"Son") == 0)||(strcasecmp(relationship,"Daughter") == 0))
					      		linkSonAndDaughter(person1,relationship,person2,genderPerson2);  	
					      	else if ((strcasecmp(relationship,"Brother") == 0)||(strcasecmp(relationship,"Sister") == 0))
					      		linkBrotherAndSister(person1,relationship,person2,genderPerson2);
					      	else if ((strcasecmp(relationship,"GrandFather") == 0)||(strcasecmp(relationship,"GrandMother") == 0))
					      		linkGrandFatherMother(person1,person2,relationship,genderPerson2);
					      	else if ((strcasecmp(relationship,"Uncle") == 0)||(strcasecmp(relationship,"Aunt") == 0))
					      		linkUncleAndAunt(person1,relationship,person2,genderPerson2);
					       	
					      

					    }
				}
			break;

			case 2:	
				printf("\nMENU 2 : Ask Relationship (Person Person)\n\n");
				memset(input,0,sizeof(input));
				printf("\t -> Enter The Names of 2 Persons : ");
				fgets(input,sizeof(input),stdin);
				sscanf(input,"%s %s",person1,person2);
				countSpaceVal = 0;
				countSpaceVal = countSpace(input);
				if ((countSpaceVal != 1) || (strlen(person1)==0) || (strlen(person2) == 0))
					{
					 printf("\n\t -> Please Enter an Relationship Between (Person Person)\n");
					 break;
					}
				/* Find the EDGE between there VERTEX or If EDGE doesn't exist find the path
				 * And find the relationship by using stack and 2 Arrays dimention
				 */
				makeRelationshipsReasoningSystem(person1,person2);

			break;
			case 3:	

			break;
			}
		printf("\n");		
		option = getMenuOption();
		}

	printf("\t\tGOOD BYE! \n\n");

}
