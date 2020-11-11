
[ README FILE]
 This file will describe how the system work overall.
 Also, show the name of Aj.Sally's files that are used in this system
 and describe the part of Aj.Sally's codes that were modified in this system

 **************************************************************************
 * This program allows user to insert the legal relationship in the graph
   by checking it before it's added to the graph.
   About the illegal relationship, there are 2types of it
      * illegal gender : it checks that the gender that will be added is conflicts with the data in the graph before or not.
         			ex- A Son B
         				A Daughter F - this relationship will be rejected because A is Male and it will be 'not' added into the graph
      * illegal relationship : it checks that the relationship between 2vertices that isn't illegal in gender but illegal in logical by checking possibility from data in the graph and analyze it.
      				ex- A(M) son B(M)
      					F(M) father A(M) - this relationship will be rejected because A already has father which is A.

  * Noted that if we don't know the gender of the persom,the system will ask for it (This case usually use with Person2)

  * The scope of the handle relationship are grandfather/grandmother, father/mother , uncle/aunt , 
  											 brother/sister , grandson/grandaughter , husband/wife , son/daughter
  											** other than this it will not handle.
  * For the limited of some relationships,
  		* each person can has only 1 father, mother , wife and husband.
  		* each person can has only 2 grandmother and grandfather(we will not count the brother/sister of the grandma/grandfa like them)
  		* other relations from 2cases before can has unlimited.
  		* We will not count that the family of the husband is the family of the wife, also the wife's family is not related to her couple family.
  		  for example, we will not count father of husband to be father of his couple
  		* We used 'Grandson' and 'Grandaughter' to both grandchild of grandma/grandpa and Uncle/Aunt
  

  * After the relationship passed all checking, the system will automatically generate the EDGE between them *both A to B and B to A*
  * Also, this program will generate the edge from the new vertices to the any vertices in the graph which relate to them. Thus, we 'almost' link all vertices together.

  * About the ask function, the system will get two vertices from user and find the relationship between them by using stack. Then, system can answer the question about their relationship.
  * After user done using, the system saves the data and allows user to reload it next time.

  * Dumpfile(BackupFile) : in this file, it will store all legal vertices and edge(relationship) of each person to the file

 **************************************************************************

Lists of Aj.Sally's file that were used.
 - abstractNetwork.h - we add "isReachablePrintPath" to this file
 - abstractQueue.h 	 
 - abstractStack.h
 - linkedlistNetwork.c
 					 - we edited Aj's function called 'traverseBreadthFirst' to be "isReahablePrintPath" - this function will print all path that was traversed.
 					 - we add function called "countAdjacentByKey" - this function will use for checking vertex and adjacent. Also, count the Adjacent of the vertex.
 - linkedListQueue.c
 - linkedListStack.c
 - minPriorityQueue.h
 - networkBuilder.c
 - networkBuilder.h


 List of our souce file.
 - familyRelationship.c  - main function
 - familyUtil.c
 - connectFamily.c
