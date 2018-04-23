/*
 * algoTest.c
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
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

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
	{	/*
		if(out.score == ij && out.score == ji)//break tie later on
		{
			out.from = 'b';//both
			printf("Both\n");
		}
		*/
		if(out.score == ij)
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


void t(int i){
	printf("test #%d \n",i);
}

int main(int argc, char **argv)
{	
	FILE *stream1;
	FILE *stream2;
	stream1 = fopen("test4","r");
	stream2 = fopen("test5", "r");

	//getting size of files
	fseek(stream1, 0L, SEEK_END);
	int size1 = ftell(stream1);
	rewind(stream1);
	
	fseek(stream2,0L, SEEK_END);
    int size2 = ftell(stream2);
    rewind(stream2); 

	printf("%d %d:: \n",size1,size2);

		
    //struct ret score[size1][size2]; // too big for the stack. need to store on RAM. double malloc. gross.
    
	struct ret **score = (struct ret**) calloc(size1, sizeof(struct ret*));

	for ( int i = 0; i < size1; i++ )
	{
		score[i] = (struct ret*) calloc(size2, sizeof(struct ret));
	}



    char read[2];
    
    int max;
    int ipos, jpos;
   // int j=1,i;
    

    for(int i = 1; i < size1; ++i)//while(fgets(&read[0],2,stream1) != NULL) //
    {	
		fgets(&read[0],2,stream1);
		//i=1;

		 for(int j=1;j<size2;j++)//while(fgets(&read[1],2,stream2) != NULL)
		{	
			fgets(&read[1],2,stream2);
			if(read[0]==read[1]){
				score[i][j] = maxScore(score[i-1][j].score,score[i][j-1].score,(score[i-1][j-1].score+3));
			}
			else{

				score[i][j] =maxScore(score[i-1][j].score,score[i][j-1].score,(score[i-1][j-1].score-3));
			}


			if(max != MAX(score[i][j].score, max)){
				max = MAX(score[i][j].score, max);//get the max score for traversing.
				ipos=i;
				jpos=j;//got position of max score
			}
			//printf("%c;%c;%d:%d\n", read[0],read[1],i,j);//printcheck
			//printf("%d;%c;\n", score[i][j].score,score[i][j].from);
		}




		rewind(stream2);
    }
    
   printf("%d %d %d \n",max,ipos,jpos);
   
   //int ipos2 = ipos; int jpos2 = jpos; 
   int check = max;
   char *arr1 = (char*)calloc(MAX(size1,size2)*2, 8);
   
   int k=0;
   
   
   FILE *al;
   al = fopen("OptimalAlignmentTest","w");
   
   char *out1;
   char out2;
	
	int shit= 0;
	*out1 = '_';
	// use write unbuffered
	char *write = "prints from 5' \n";
	fwrite(write,1,15,al);
	
	while(check != 0 ){
	
		
		
		//get optimal alingment here too.
		fseek(stream2,jpos,SEEK_SET);//set the stream pointer
		fgets(&out2,2,stream2);//get the returned nucletide
		
		 switch(score[ipos][jpos].from)
		   {
			   case 'c':
				arr1[k] = 'c';
				ipos--;
				jpos--;
				fwrite(&out2,1,1,al);
				break;
				
				/*	
			   case'b'://breaktie here
					arr1[k] = 'b';
					ipos--;
					//fwrite(&out[1],1,1,al);
					break;*/
					
			   case 'u':
				arr1[k] = 'u';
				ipos--;
				fwrite(&out1,1,1,al);
				break;
					
			   case 'l':
				arr1[k] = 'l';
				fwrite(&out1,1,1,al);
				jpos--;
				break;
					
			   default:
				break;
			   }
		   
		   check = score[ipos][jpos].score;
		   k++;
		   //printf("%d::", k);
		   
	   }
   
  // printf("%d\n", shit);
   
    //print checks
    
    /*
    for(int i = 0; i <size1; i++)
    {
		for(int j=0;j<size2;j++)
		{
			printf("%c::%d  ", score[i][j].from,score[i][j].score);
			
		}
		printf("\n");
    }*/
    
//this array is empty
/*
   for(int i= (MAX(size1,size2)*2); arr1[i] == 0 ;i--){

	   
	   printf("%c", arr1[i]);

	   
   }
   
   printf(" \n ");
   
   */
  
    free(arr1);

    for ( int i = 0; i <size1; i++ )
	{
		free(score[i]);// getting error here 
		//t(i);

	}

	free(score);

	fclose(stream1);
	fclose(stream2);
	
	
	return 0;
}

