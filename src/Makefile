#======================================================================================/
#**    Author: Jack Dempsey                                             	           /
#**    Date:   11/21/2018                                                              /
#**    Description: MakeFile for SmithWatermanRaspi                                /
#**    After running this makefile the user will be able to run the two
#======================================================================================/
C = gcc
FLAGS = -std=c11
CVERSION 	= ${C} -dumpversion

RUN:	SWAlgo.o SWEncode.c Complete.o


SWAlgo.o:
	@printf "\n============Compiling SWAlgo============\n"
	@${C} ${FLAGS} -o SWAlgo.exe ${PWD}/SWAlgo.c

SWEncode.o:
	@printf "\n============Compiling SWEncode==========\n"
	@${C} ${FLAGS} -o SWEncode.exe ${PWD}/SWEncode.c
	
Complete.o:
	@printf "\n========COMPILATION COMPLETE=============\n"
	
clean: 
@rm -f *.o SWAlgo.exe SWEncode.exe 


#notes
#gcc -std=c11 -W src/SWAlgo.c 
