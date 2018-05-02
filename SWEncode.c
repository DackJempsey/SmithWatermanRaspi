/*
 * SWEncode.c
 * 
 * Copyright 2018 Jack Dempsey <jackdempsey@rgnt2-102-74-dhcp.int.colorado.edu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 * This is the encoding code/scheme used for this project. 
 * This is to prepare the data so that the Rpi does not have to work as hard/
 * 
 *  
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void t(int i){
	printf("test #%d \n",i);
}
/*
FILE *prePrep(char *file)//This takes the file and creates new files and titles. 
    //also takes all cases and converts to uppercase.
{	//first line of string should be ">sequence A - some descriptors then: /n the next line is the string"
	
	FILE *readfile;
	FILE *writefile;
	
	char name[15];
	
	readfile = fopen("test2", "r");
	writefile = fopen("Prep.jack","w");
	
	fseek(readfile, 0L, SEEK_END);
	int size1 = ftell(readfile);
	rewind(readfile);
	
	char line[size1];
	
	int i=0;
	
	if(fgets(&name[0], 50, readfile) == '>'){	
		while(fgets(&line[i], 1, readfile) != NULL){
			//make uppercase, put in outfile
			if(line[i]>91)
			{
				line[i]=line[i]-32;
				fwrite(&line[i],1,1,writefile);
			}
			else{
				fwrite(&line[i],1,1,writefile);
			}
		}
	}
	

	fclose(readfile);
	return writefile;
}
*/


unsigned int pack(int i,unsigned int nuc1,unsigned int nuc2){//takes index i 1->14 and packs the nucleoditdes into one
	//bit shift right nuc 2 over by the index, OR the nucs, return that.

	int j = (nuc2<<i);

	nuc1 = nuc1 ^ j;

	return nuc1;
}

FILE * input(FILE *file)//takes in the file reads it, encodes it. outputs a file.
{
	
	FILE *out; //output
	out = fopen("Encoded2", "w");//create a file to put the encoding.
	
	
	//put file where test is, then comment this out. used only for testing
	FILE *test1;
	test1  = fopen("test", "r");
	//getting size of files
	fseek(test1, 0L, SEEK_END);
	int size1 = ftell(test1);
	rewind(test1);
	
	
	
	char *outArr = (char*) malloc(size1);
	
	if(test1 == 0)
	{
		printf("Did not read\n");
		exit(1);
	}
	else if (!out)
	{
		printf("Unable to open out file\n");
		exit(1);
	}
	else
	{	
		printf("Good Read file!\n");
		//do encoding here
		 
		int index =0;
		int index2=0;
		unsigned int outC=0;
		rewind(test1);
		
		while( index<=size1 )
		{
			//ASII -> binary file -> hex. then change to make it efficient.

			fgets(&outArr[index],2,test1); //nucluetide from the line. 

			switch(outArr[index]) // convert nucluotide and store in out
			{
				
				case 'A':
					if(index2 > 1)
					{
						outC = pack(index2,outC, 0 );
					}
					else
					{
						outC = 0;
					}
					break;
					
					
				case 'C':

					if(index2 > 1)
					{
						outC = pack(index2,outC, 1 );
					}
					else
					{
						outC = 1;
					}
					break;
		
					
				case 'G':
					if(index2 > 1)
					{
						outC = pack(index2,outC, 2 );
					}
					else
					{
						outC = 2;
					}
					break;
					
				case 'T':
					
					if(index2 > 1)
					{
						
						outC = pack(index2,outC, 3 );
					}
					else
					{
						outC = 3;
					}	
					//printf("%d::\n",outC);	
					break;		
					
				default :
					printf("%s %c\n", "Invalid character: ",outArr[index]);
					break;
			
			}

			if(index2 == 30){
				fprintf(out,"%d,",outC);
				index2=0;
				//printf("%d \n::",outC);
			}
			//else if(index == size1 ){//still need to deal with the extra data. this is when the size is not 0 mod 16.
		//		fprintf(out,"%d ",outC);
		//		break;//done with encoding
		//	}
			else 
			{

				index2+=2;
			}
			
			index+=1;
		}
		
		
	}
	
	
	
	fclose(test1);
	fclose(out);
	free(outArr);
	
	return out;
}


int main(int argc, char **argv)
{	
		//input(prePrep(*argv));
		FILE *test1 = NULL;
		input(test1);

	return 0;
}












