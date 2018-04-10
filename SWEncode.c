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

FILE *prePrep(char *file)//This takes the file and creates new files and titles. 
    //also takes all cases and converts to uppercase.
{	//first line of string should be ">sequence A - some descriptors then: /n the next line is the string"
	FILE *readfile;
	FILE *writefile;
	char line [128];  //make dynamic
	char fileoutputname[15];
	int filecounter=1, 
	
	readfile = fopen("test2", "r");
	int i=0;
	while(fscanf(readfile, "%s",line) != EOF){
		if(i==0){rewind(readfile);i+=1;}	
		getline(fileoutputname, 15, readfile);
		while(fgets(line, 1, readfile) != ">"){
			//make uppercase, put in outfile
			if()
		}
	}
	

	fclose(readfile);
	return out;
}


char pack(int i,char nuc1,char nuc2){//takes index i 1->4 and packs the nucleoditdes into one
	//bit shift right nuc 2 over by the index, OR the nucs, return that.
	i=i*2;
	nuc2 = nuc2 >> i;
	nuc1 = nuc1 ^ nuc2;
	return nuc1;
}

FILE * input(FILE *file)//takes in the file reads it, encodes it. outputs a file.
{
	
	FILE *out; //output
	out = fopen("Encoded.bin", "wb");
	char outArr[100];//to use in the while loop.-> make dynamic
	char wArr[4];
	
	//create a file to put the encoding.
	
	
	//put file where test is, then comment this out. used only for testing
	FILE *test1;
	test1  = fopen("test3", "r");
	
	if(test1 == 0)
	{
		printf("Did not read");
		exit(1);
	}
	else if (!out)
	{
		printf("Unable to open out file");
		exit(1);
	}
	else
	{	
		printf("Good Read file!\n");
		//do encoding here
		 
		int index =0;
		int index2=1;
		char outC;
		rewind(test1);
		while( index<99 || fscanf(test, "%s", &outArr[index]) != EOF)
		{
			//printf("test\n");
			
			//ASII -> binary file -> hex. then change to make it efficient.

			fgets(&outArr[index],2,test); //nucluetide from the line. 

			switch(outArr[index]) // convert nucluotide and store in out
			{
				
				case 'A':
					if(index2>1)
					{
						outC = pack(index2,outC, 0x00 );
					}
					else
					{
						outC = 0x00;
					}
					break;
					
					
				case 'G':

					if(index2>1)
					{
						outC = pack(index2,outC, 0x10 );
					}
					else
					{
						outC = 0x10;
					}
					break;
		
					
				case 'C':
					if(index2>1)
					{
						outC = pack(index2,outC, 0x2 );
					}
					else
					{
						outC = 0x2;
					}
					break;
					
				case 'T':
					if(index2>1)
					{
						outC = pack(index2,outC, 0x3 );
					}
					else
					{
						outC = 0x3;
					}				
									
															
				default :
					printf("%s", "Invalid character Final ");
			
			}
			if(index2 == 4){
				fwrite(&outC,1,1,out);
				index2=1;
			}
			
			else
			{
				index2+=2;
			}
			
			index+=2;

			
		}
	}

	
	//fclose(fasta);
	fclose(out);
	
	return out;
}


int main(int argc, char **argv)
{	
		//input(prePrep(*argv));
		FILE *test = NULL;
		input(test);

	return 0;
}












