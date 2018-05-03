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

		struct ret smallArr[32][32];//this is the array that will be used for calculations.fixed
		
		int bigArrSize1;
		int bigArrSize2;
		
		struct ret **bigArr;
		
		FILE *retFile;
};

void t(int i){
	printf("test #%d \n",i);
}


char unpack(unsigned int encode,int i){//takes the integer and unpacks it to the iteration i within the encoded int. 
									//need a for loop to unpack all of the encoded strings
	char out;
	
	unsigned int transfer;
	
	
	transfer = encode << i;
	transfer = transfer >> 30 ;

	//printf("Encoded:%d Transfer:%d:: \n",encode,transfer);
	
	switch(transfer){
		case 0:
			out = 'A';
			break;
		case 1:
			out= 'C';
			break;
		case 2:
			out = 'G';
			break;
		case 3:
			out= 'T';
			break;
		default:
			out ='X';
			break;
	}
	
	return out;
	
	
}


struct ret maxScore(int ij,int ji, int i1j1){
	
	struct ret out;

	//i1j1 = i1j1;// + 3;
	ij= ij-2;
	ji=ji-2;
	//or 0
	
	out.score = MAX(0,MAX(i1j1,MAX(ij,ji)));
	

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
			out.from = 'X';//zero
		}
	}
	
	//printf("%d %d %d :: Score: %d From: %c  ",i1j1,ij,ji,out.score,out.from);
	
	return out;
}

void check(struct ret **score, FILE *stream1,FILE *stream2,int ipos, int jpos,int max){
	//going to need to undo the encoding 
	FILE *al;
	//char *arr1 = (char*)malloc(MAX(size1,size2)*2);
    int k=0;
    
   al = fopen("OptimalAlignment","w");
   int out[2]; //out[0] will be the nucleotide from the fseek.
   char *out1 = "-";//this is equal to a space.
   char *begin = "starts from 3' \n";
	fwrite(begin,1,16,al);
	//printf("%c\n",score[ipos][jpos].from);
	char undone1;
   while(max != 0 ){
	//get optimal alingment here too.
	fseek(stream2,jpos,SEEK_SET);//set the stream pointer
	
	fscanf(stream2,"%d",&out[0]);//get the returned nucletide
	//printf("%c\n",score[ipos][jpos].from);
	for(int i=0;i<16;i++){
		printf("%c\n", score[ipos][jpos].from);
	undone1=unpack(out[0],i*2);
	//t(out[0]);
	 switch(score[ipos][jpos].from)
	   {
	
		   case 'c':
				//arr1[k] = 'c';
				ipos--;
				jpos--;
				fprintf(al,"%c ", undone1);

				break;
				
		   case'b'://breaktie here
				//arr1[k] = 'b';
				jpos--;
				fprintf(al,"%s,",out1);
				break;
				
				
		   case 'u':
				//arr1[k] = 'u';
				ipos--;
				fprintf(al,"%s,",out1);
				break;
				
		   case 'l':
				//arr1[k] = 'l';
				
				fprintf(al,"%s,",out1);
				jpos--;
				break;
				
		   default:

		   		ipos--;
				jpos--;
				break;
		   }
		//t(max);
	   max = score[ipos][jpos].score;

	   k++;
	   //printf("%c\n", arr1[k]);
   }
	   
   }
}




FILE *alignment(FILE *nuc1, FILE *nuc2){ //takes in files of encoded nucleotides and returns alignment of the two
	//this is the actual algorithm func here

	
	struct stuc align;
	
	//getting size of files
	fseek(nuc1, 0L, SEEK_END);
	align.bigArrSize1 = ftell(nuc1)*8;
	//align.bigArrSize1 = align.bigArrSize1-(align.bigArrSize1%8);
	rewind(nuc1);

	fseek(nuc2,0L, SEEK_END);
    align.bigArrSize2 = ftell(nuc2)*8;
    //align.bigArrSize2 = align.bigArrSize2-(align.bigArrSize2%8);
    rewind(nuc2);
     
	printf("Size1:%d Size2:%d:: \n",align.bigArrSize1,align.bigArrSize2);


	align.bigArr = calloc((align.bigArrSize1),sizeof(struct ret*));

	for(int i=0;i<align.bigArrSize1-1;i++){
		align.bigArr[i]= calloc((align.bigArrSize2+1),sizeof(struct ret));

	}
	//align.retFile = fopen("Score", "w");

	//Rowmajor-> do rows first
	int read1;//for storing in fgets
	int read2;
	int max=0;
	int ipos,jpos;
	
	char undone1;
	char undone2;
	
	for(int i=0;i<align.bigArrSize1-32;i+=32){
		for(int n=0;n<align.bigArrSize2-32;n+=32){
			//take values from big arr and put in small arr. only for first line'
			for(int f =0;f<32;f++){
				//initializing small arr.

				align.smallArr[f][0] = align.bigArr[i+f][n];
				align.smallArr[0][f] = align.bigArr[i][n+f];
				//not optimal but gets it done, otherwise, use another for loop.
			}

					//look at the three surrounding matrix entries. pick lowest. or 0.
					for(int l=1;l<16;l+=1){
						
						fscanf(nuc1,"%d,",&read1);
						undone1=unpack(read1,l*2);
						
						for(int m=1;m<16;m+=1){
							fscanf(nuc2,"%d,",&read2);
							undone2=unpack(read2,m*2);
							if(undone1 == undone2){
								
								align.smallArr[l][m] = maxScore(align.smallArr[l-1][m].score,align.smallArr[l][m-1].score,(align.smallArr[l-1][m-1].score+3));
							}
							else{
								
								align.smallArr[l][m] = maxScore(align.smallArr[l-1][m].score,align.smallArr[l][m-1].score,(align.smallArr[l-1][m-1].score-3));
							}
							//printf("score:\n");
							//t(align.smallArr[l][m].score);
							if(max != MAX(align.smallArr[l][m].score, max))
							{
								max = MAX(align.smallArr[l][m].score, max);//get the max score for traversing.
								ipos=i+l;
								jpos=n+m;//got position of max score
								//t(align.smallArr[l][m].score);
								//printf("Max So Far:%d i:%d j:%d from:%c \n",max,ipos,jpos,align.smallArr[l][m].from);
							}
						}
						fseek(nuc2,n,SEEK_SET);
					}
		//transfer to larger matrix here:
		//this may be the bottleneck due to the transfer of data i.e. need to initialize smallArr for nex
		//round so that it can use previous values.
				for(int j=0;j<32;j++){
					for(int k=0;k<32;k++){
						align.bigArr[j+i][k+n] = align.smallArr[j][k];
						//printf(" %d ",align.smallArr[k][j].score);
						//printf("Score:%d from:%c",align.bigArr[j+i][k+n].score,align.bigArr[j+i][k+n].from);
					}
					//printf("\n");
				}
				
		}
		
		fseek(nuc1,i,SEEK_SET);
	}
	printf("Max total:%d i:%d j:%d from:%c \n",max,ipos,jpos,align.bigArr[ipos][jpos].from);
	check(align.bigArr,nuc1,nuc2,ipos,jpos,max);

	for ( int i = 0; i < align.bigArrSize1; i++ )
	{
		free(align.bigArr[i]);// getting error here 
	}
	free(align.bigArr);
	
	//fclose(align.retFile);

	return align.retFile;
	
}


int main(int argc, char **argv)
{
	/*
	printf("Do you want score or alignment");
	char input;
	* 
	
	scanf('%c', input);
	*/
	FILE *test1 = fopen("Encoded1.jack","r");
	FILE *test2 = fopen("Encoded2.jack","r");
	
	alignment(test1,test2);
	
	
	
	fclose(test1);
	fclose(test2);
	
	
	return 0;
}

