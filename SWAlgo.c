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

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

struct ret{
	int score;
	char from;//three options c - corner u-up l -left
	
};

struct stuc{

		struct ret smallArr[8][8];//this is the array that will be used for calculations.fixed
		
		int bigArrSize1;
		int bigArrSize2;
		
		struct ret **bigArr;
		
		FILE *retFile;
};

void t(int i){
	printf("test #%d \n",i);
}


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
	
	//getting size of files
	fseek(nuc1, 0L, SEEK_END);
	align.bigArrSize1 = ftell(nuc1);
	align.bigArrSize1 = align.bigArrSize1-(align.bigArrSize1%8);
	rewind(nuc1);

	fseek(nuc2,0L, SEEK_END);
    align.bigArrSize2 = ftell(nuc2);
    align.bigArrSize2 = align.bigArrSize2-(align.bigArrSize2%8);
    rewind(nuc2);
     
	printf("Size1:%d Size2:%d:: \n",align.bigArrSize1,align.bigArrSize2);


	align.bigArr = calloc((align.bigArrSize1),sizeof(struct ret*));

	for(int i=0;i<align.bigArrSize1-1;i++){
		align.bigArr[i]= calloc((align.bigArrSize2+1),sizeof(struct ret));

	}
	align.retFile = fopen("Score", "w");

	//Rowmajor-> do rows first
	int read1;//for storing in fgets
	int read2;
	int max;
	int ipos,jpos;
	
	
	for(int i=0;i<align.bigArrSize1-8;i+=8){
		
		for(int n=0;n<align.bigArrSize2-8;n+=8){
			//take values from big arr and put in small arr. only for first line
			for(int f =0;f<8;f++){
				//initializing small arr.

				align.smallArr[f][0] = align.bigArr[i+f][n];
				align.smallArr[0][f] = align.bigArr[i][n+f];
				//not optimal but gets it done, otherwise, use another for loop.
			}
			for(int j=1;j<8;j++){
				fscanf(nuc1,"%d ",&read1);
				printf("%d \n",read1);
				
				for(int k=1;k<8;k++){
					
					fscanf(nuc2,"%d ",&read2);
					//look at the three surrounding matrix entries. pick lowest. or 0.
					
					if(read1 ==read2){
						align.smallArr[j][k] = maxScore(align.smallArr[j-1][k].score,align.smallArr[j][k-1].score,(align.smallArr[j-1][k-1].score+3));
					}
					else{
						align.smallArr[j][k] = maxScore(align.smallArr[j-1][k].score,align.smallArr[j][k-1].score,(align.smallArr[j-1][k-1].score-3));
					}
					
					if(max != MAX(align.smallArr[j][k].score, max)){
						max = MAX(align.smallArr[j][k].score, max);//get the max score for traversing.
						ipos=i;
						jpos=j;//got position of max score
						printf("Max So Far:%d \n",max);
						}
					fseek(nuc1,n,SEEK_CUR);
				}
			}
			fseek(nuc2,i,SEEK_CUR);
		//transfer to larger matrix here:
		//this may be the bottleneck due to the transfer of data i.e. need to initialize smallArr for nex
		//round so that it can use previous values.

				for(int j=1;j<8;j++){
					for(int k=1;k<8;k++){
						align.smallArr[k][j] = align.bigArr[j+i][k+n];
						//printf("%d ",align.bigArr[j+i][k+n].score);
					}
					//printf("\n");
				}

		}
	}
	
	for ( int i = 0; i < align.bigArrSize1; i++ )
	{
		free(align.bigArr[i]);// getting error here 
	}
	free(align.bigArr);
	
	fclose(align.retFile);

	return align.retFile;
	
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
	FILE *test1 = fopen("Encoded1","r");
	FILE *test2 = fopen("Encoded2","r");
	retScore(alignment(test1,test2));
	fclose(test1);
	fclose(test2);
	
	
	return 0;
}

