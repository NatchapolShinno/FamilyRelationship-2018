#ifndef ABSTRACTNETWORK_H
#define ABSTRACTNETWORK_H

/** Find the gender of person if him/her doesn't has gender
	and Validate the illegal gender.
	@name - person who want to check
	@genderInput - gender that user input
	@genderInput == "N" if don't know gender
	@return 1 - Male
			0 - Female 
*/
int findGenderOfPerson(char name[],char genderInput[]);

/** Find the return relationship of each relation
	@relationSequence - relation that user input
	@gender - gender that we know via reasoning of relation
	@return - return the relation sequence

*/
int findReturnRelationshipSequence(int relationSequence, char * gender);

/** Dump the information in to reload file
	@Vertex - VERTEX (name) (gender)
	@EDGE - EDGE (name1) (name2) (relationship in sequence)
*/
void dumpNetworkReloadFile(char type[],char person1[],char person2[],int relationSequence);

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
int checkSequenceOfRelationship(char *relationship);

/** Show the option to user 
	@return - option that user input
*/
int getMenuOption();

int countSpace(char input[]);

/** Ask the user to reload file
	@Yes - read the back up file and reload the graph
	@No - create the new graph
*/
void askToReloadFile(char * isReloadFile);

/** Add person to the network if that person doesn't exist in network
	and dump the information of person into backUp file
	@person1 - name of the first person
	@person2 - name of the second person
	@genderPerson1 - gender of the first person
	@genderPerson2 - gender of the second person
*/
void addPersonToNetwork (char * person1, char * person2, char * genderPerson1, char* genderPerson2);

/** Create relation between 2 person and dump the relation into back up file
	@person1 - name of the first person
	@person2 - name of the second person
	@sequenceInRelationship - sequence of relationship between 2 persons
	@genderPerson1 - gender of the first person
	@genderPerson2 - gender of the second person
*/
void addRelationshipBetweenTwoPerson (char * person1, char * person2, int sequenceInRelationship, char * genderPerson1, char * genderPerson2);


void combineRelationByStack(int pathCount);

/** Print the relationship between 2 person
	@keystring1 - name of first person
	@keystring2 - name of second person
	@return 1 if relation has exist
*/
void printRelationship(char * keystring1,char * keystring2);

/** Create the relationship via reasoning system
	@person1 - name of first person
	@person2 - name of second person
*/
int makeRelationshipsReasoningSystem(char * person1, char * person2);

/** Check input of user 
	@person - name of person
	@relationship - relation between 2 person
	@return if it all correct return 1
	@retrun - wrong return 0
*/
int checkInputRelation(char * person1,char * relationship,char *person2);

/** Check illegal character when we input gender
  @answer - Input of user
  @return if it correct return 1 but if it false return 0
*/
int checkInputGender(char * answer);

/** Check the illegal logic before we add into the network if it illegal return 1
	@person1 - name of the first person of input
	@person2 - name of the second person of input
	@relationship - relationship between 2 persons from input
	@genderPerson1 - gender of the first (we know gender person1 from relationship)
	@return - If it illegal return -1 
*/
int checkLogicRelationship (char* person1,char* person2,char* relationship,char *genderPerson1);

/** Check the Illegal relationship by chec from adjacent
	@focusPoing - the vertex that you want to check
	@return - result value
*/
int checkIllegal(char* focusPoint);

#endif