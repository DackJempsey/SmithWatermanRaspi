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
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * input(char *file)//takes in the file reads it, encodes it. outputs a file.
{
	
	FILE *out; //output
	out = fopen("FUck.bin", "wb");
	char outArr[10];//to use in the while loop.
	//first line of string should be ">sequence A - some descriptors then: /n the next line is the string"
	//create a file to put the encoding. make a new function
	//char *file = argv[1]; //if you wanna take the file as an arguement
	
	
	//put filename where test is, this is to directly load, then no need for argument.
	FILE *fasta;
	fasta  = fopen("test", "r");
	
	if(fasta == 0)
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
		//do parsing here
		//first take the line ">stuf" and throw it away
		
		//char shit[100]; //this is the size file that will store some data, possibly do a mallo with stringlen 
		while (fscanf (fasta, "%s", outArr) != EOF)
		{
			// do stuff
			//printf("%s",shit);
			//ASII to binary file. then change to make it efficient.
			char nuc;
			fgets(nuc,1,fasta); //nucluetide from the line
			switch(nuc) // convert nucluotide and store in out
			{
				case 'A':
					//convert to 00
					break;
				case 'T':
					//convert to 01
					break;
				case 'C':
					//convert to 10
					break;
				case 'G':
					//convert to 11
					break;
				default :
					printf("%s", "Invalid character");
				
			}
			
		}
	}
	

	
	fclose(fasta);
	fclose(out);
	
	return out;
}


int main(int argc, char **argv)
{	
		input(*argv);

	return 0;
}












