/*
 * SWAlgo.c
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
 * This is the Algorithm for the Smith waterman on the raspberry pi.
 * It takes in packed data.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *alignment(FILE *nuc1, FILE *nuc2){//takes in files of encoded nucleotides and returns alignment of the two
	//this is the actual algorithm func here
	FILE *ret;
	
	fopen
	
	char smallArr[4][4];//this is the array that will be used for calculations.fixed
	//char bigArr[][];//this is the array that will be used for storing the calculations scores. make dynamic
	
	//initialize smalArr
	for(int j=0;j<4;j++){
		smallArr[0][j] = 0;
		}
	for(int i=0;i<4;i++){
		smallArr[i][0] = 0;
	}
	
	//Rowmajor-> do rows first
	for(int i=0;i<bigArrSize1;i++){
		for(int n=0;n<bigArrSize2;n++){
		
			//takes a few at a time here:
			//calculations here
			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++){
					//look at the three surrounding matrix entries. pick lowest. or 0.
					
					
				}
			}
			
		//transfer to larger matrix here:
			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++){
					smallArrr[k][j] = bigArr[bigArrSize2][bigArrSize1];
				}
			}
		
		
		}
	}

	
	
	return ret;
	
}

int retScore(FILE *alginment){//takes in best alignment and returns a score
	int score=0;
	
	
	

	return score;
}

int main(int argc, char **argv)
{
	printf("Do you want score or alignment");
	scanf('%s', char input)
	if(input = "score"){
		retScore(alignment(SHIT)):
	}
	return 0;
}

