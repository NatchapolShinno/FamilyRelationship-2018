#ifndef ABSTRACTCONNECT_H
#define ABSTRACTCONNECT_H
/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Father" and "Mother" relationships.
*/
void linkFatherAndMother(char* keystring1,char * relationship,char* keystring2,char * gender);

/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "GrandFather" and "GrandMother" relationships.
*/
void linkGrandFatherMother(char* person1,char* person2,char* relationship,char* genderSecond);

/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Uncle" and "Aunt" relationships.
*/
void linkUncleAndAunt(char* keystring1,char * relationship,char* keystring2,char * gender);

/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Sonr" and "Daughter" relationships.
*/
void linkSonAndDaughter(char* keystring1,char * relationship,char* keystring2,char * gender);

/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Brother" and "Sister" relationships.
*/
void linkBrotherAndSister(char* keystring1,char * relationship,char* keystring2,char * gender);

/** Check the relation from person to adjacent of each person and find the relationship
  * between person via "Husband" and "Wife" relationships.
*/
void linkHusbandWife(char * person1,char * relationship,char * person2,char * genderPerson2);
#endif