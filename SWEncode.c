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

FILE *prePrep(char *file)//this gets ride of the line deliniators and makes it all uppercase
{	//first line of string should be ">sequence A - some descriptors then: /n the next line is the string"
	

	FILE *out; //output file
	out = fopen("prePrep.bin" , "wb");
	FILE *in;
	in = fopen(file, "r");
	
	char Arr[100];
	
	 
	getline(Arr, 1, in);
	
	
	fclose(out);
	fclose(in);
	//free(); //frees buffer made by the getline.
	
	return out;
}


FILE * input(FILE *file)//takes in the file reads it, encodes it. outputs a file.
{
	
	FILE *out; //output
	out = fopen("Encoded.bin", "wb");
	char outArr[12];//to use in the while loop.

	//create a file to put the encoding. make a new function
	
	//char *file = argv[1]; //if you wanna take the file as an arguement
	
	char encode[16];
	//initializing array for encoding
	encode[0] = '0';
	encode[1] = '1';
	encode[2] = '2';
	encode[3] = '3';	
	
	encode[4] = '4';
	encode[5] = '5';
	encode[6] = '6';
	encode[7] = '7';
	encode[8] = '8';
	encode[9] = '9';
		
	encode[10] = 'A';
	encode[11] = 'B';
	encode[12] = 'C';
	encode[13] = 'D';
	encode[14] = 'E';
	encode[15] = 'F';
		
	
	//put filename where test is, this is to directly load, then no need for argument.
	//FILE *fasta;
	//fasta  = fopen( file, "r");
	
	if(file == 0)
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
		//do parsing here
		//first take the line ">stuff" and throw it away
		
		//char shit[100]; //this is the size file that will store some data, possibly do a mallo with stringlen 
		int index =0;
		while (index<9)//fscanf (fasta, "%s", outArr) != EOF)
		{
			// do stuff
			//printf("%s",shit);
			//ASII to binary file. then change to make it efficient.
			//char nuc;
			fgets(&outArr[index],3,file); //nucluetide from the line

			switch(outArr[index]) // convert nucluotide and store in out
			{
				
				case 'A':
					switch(outArr[index+1]){
				
						case 'A'://case aa
							fwrite(&encode[0], 1, 1, out);
							break;
						case 'G'://case ag
							fwrite(&encode[4], 1, 1, out);
							break;
						case 'C': //case ac
							fwrite(&encode[8], 1, 1, out);
							break;
						case 'T': //case at
							fwrite(&encode[12], 1, 1, out);
							break;
						default :
							printf("%s", "Invalid character 1 ");
					}
					break;
					
					
				case 'G':

					switch(outArr[index+1]){
				
						case 'A'://case ga
							fwrite(&encode[1], 1, 1, out);
							break;
						case 'G'://case gg
							fwrite(&encode[5], 1, 1, out);
							break;
						case 'C': //case gc
							fwrite(&encode[9], 1, 1, out);
							break;
						case 'T': //case gt
							fwrite(&encode[13], 1, 1, out);
							break;
						default :
							printf("%s", "Invalid character 2 ");
					}
					break;
		
					
				case 'C':
					switch(outArr[index+1]){
				
						case 'A'://case ca
							fwrite(&encode[2], 1, 1, out);
							break;
						case 'G'://case cg
							fwrite(&encode[6], 1, 1, out);
							break;
						case 'C': //case cc
							fwrite(&encode[10], 1, 1, out);
							break;
						case 'T': //case ct
							fwrite(&encode[14], 1, 1, out);
							break;
						default :
							printf("%s", "Invalid character 3 ");
					}	
					break;
					
				case 'T':
					switch(outArr[index+1]){
				
						case 'A'://case ta
							fwrite(&encode[3], 1, 1, out);
							break;
						case 'G'://case tg
							fwrite(&encode[7], 1, 1, out);
							break;
						case 'C': //case tc
							fwrite(&encode[11], 1, 1, out);
							break;
						case 'T': //case tt
							fwrite(&encode[16], 1, 1, out);
							break;
						default :
							printf("%s", "Invalid character 4 ");
					}
					break;				
									
															
				default :
					printf("%s", "Invalid character Final ");
			
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
		input(prePrep(*argv));

	return 0;
}












