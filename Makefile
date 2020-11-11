# Makefile for demo programs for Lecture 8
# Networks
# We also need a queue and a min priority queue for this lecture

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES=familyRelationship$(EXECEXT)

all : $(EXECUTABLES)

linkedListQueue.o :	linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

familyUtil.o : familyUtil.c abstractFamily.h abstractNetwork.h networkBuilder.h abstractStack.h abstractQueue.h abstractFamily.h abstractConnect.h
	gcc -c familyUtil.c

connectFamily.o : connectFamily.c abstractFamily.h abstractNetwork.h networkBuilder.h abstractStack.h abstractQueue.h abstractConnect.h
	gcc -c connectFamily.c
linkedListStack.o :	linkedListStack.c abstractStack.h
	gcc -c linkedListStack.c

minPriorityQueue.o :	minPriorityQueue.c minPriorityQueue.h
	gcc -c minPriorityQueue.c

linkedListNetwork.o :	linkedListNetwork.c abstractNetwork.h abstractQueue.h abstractStack.h
	gcc -c linkedListNetwork.c

networkBuilder.o :	networkBuilder.c abstractNetwork.h networkBuilder.h
	gcc -c networkBuilder.c

familyRelationship.o :	familyRelationship.c abstractNetwork.h networkBuilder.h abstractStack.h abstractQueue.h abstractFamily.h abstractFamily.h
	gcc -c familyRelationship.c


familyRelationship$(EXECEXT) : familyRelationship.o linkedListNetwork.o linkedListQueue.o networkBuilder.o minPriorityQueue.o linkedListStack.o familyUtil.o connectFamily.o
	gcc -o familyRelationship$(EXECEXT) familyRelationship.o linkedListNetwork.o \
              linkedListQueue.o networkBuilder.o minPriorityQueue.o linkedListStack.o familyUtil.o connectFamily.o


clean : 
	-rm *.o
	-rm $(EXECUTABLES) 
