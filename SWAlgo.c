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

struct stuc{

		int smallArr[8][8];//this is the array that will be used for calculations.fixed
		
		int bigArrSize1;
		int bigArrSize2;
		
		int **bigArr;		
		//char bigArr[][];
		
		FILE *ret;
};

void t(int i){
	printf("test #%d \n",i);
}
struct ret{
	int score;
	char from;//three options c - corner u-up l -left
	
};


struct ret maxScore(int ij,int ji, int i1j1){
	
	struct ret out;

	//i1j1 = i1j1;// + 3;
	ij= ij-2;
	ji=ji-2;
	//or 0
	
	out.score = MAX(ji,MAX(ij,MAX(i1j1,0)));
	

	//could be the same score, but only from one place.
	
	if(out.score == i1j1){ out.from = 'c';}//always take corner case if possible.
	else 
	{
		if(out.score == ij && out.score == ji)//break tie later on
		{
			out.from = 'b';//both
		}
		else if(out.score == ij)
		{
			out.from = 'u';//from up
		}
		else if(out.score == ji)
		{
			out.from = 'l';//from left
		}
		else
		{
			out.from = '0';//zero
		}
	}
	
	//printf("%d %d %d :: Score: %d From: %c  ",i1j1,ij,ji,out.score,out.from);
	
	return out;
}

FILE *alignment(FILE *nuc1, FILE *nuc2){//takes in files of encoded nucleotides and returns alignment of the two
	//this is the actual algorithm func here
	
	
	struct stuc align;
	
	align.bigArrSize1 = 100;
	align.bigArrSize2 = 100;

	align.bigArr = malloc((align.bigArrSize1)*sizeof(int*));

	for(int i=0;i<align.bigArrSize1-1;i++){
		align.bigArr[i]= malloc((align.bigArrSize2+1)*sizeof(int));
		printf("%d\n", *align.bigArr[i]);
		align.bigArr[i]= calloc((align.bigArrSize2+1)*sizeof(int));
		//printf("%d\n", *align.bigArr[i]);

	}

	align.ret = fopen("Score", "w");

	//initialize smalArr
	for(int j=0;j<8;j++){
		align.smallArr[0][j] = 0;
		}
	for(int i=0;i<8;i++){
		align.smallArr[i][0] = 0;
	}

	//Rowmajor-> do rows first
	for(int i=0;i<align.bigArrSize1;i++){

		for(int n=0;n<align.bigArrSize2;n++){

			//takes a few at a time here:
			//calculations here

			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++){
					//look at the three surrounding matrix entries. pick lowest. or 0.
					//do an OR to check if zero(meaning it has alignment). if it is not then pick algnemnt score 
					

			
			for(int j=0;j<16;j++){
				for(int k=0;k<16;k++){
					//look at the three surrounding matrix entries. pick lowest. or 0.
					//do an OR to check if zero(meaning it has alignment). if it is not then pick algnemnt score
					fgets(); 

					
				}
			}
			printf("test\n");
		//transfer to larger matrix here:
		//this may be the bottleneck due to the transfer of data i.e. need to initialize smallArr for nex
		//round so that it can use previous values.
		
			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++){
					align.smallArr[k][j] = align.bigArr[align.bigArrSize2][align.bigArrSize1];
				}
			}
		
		
		}
	}
	
	fclose(align.ret);
	return align.ret;
	
}

int retScore(FILE *alginment){//takes in best alignment and returns a score
	int score=0;
	//go through bigArr and find the best alingment 
	
	

	return score;
}

int main(int argc, char **argv)
{
	/*
	printf("Do you want score or alignment");
	char input;
	* 
	
	scanf('%c', input);
	*/
	FILE *test1 = NULL;
	FILE *test2 = NULL;
	retScore(alignment(test1,test2));
	
	return 0;
}

