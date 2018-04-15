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
	
	if(out.score == i1j1){ out.from = 'c';}
	else if(out.score == ij){out.from = 'l';}
	else if (out.score == ji){out.from = 'u';}
	else{out.from = '0';}
	
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
	stream1 = fopen("bigTest","r");
	stream2 = fopen("bigTest2", "r");

	//getting size of files
	fseek(stream1, 0L, SEEK_END);
	int size1 = ftell(stream1);
	rewind(stream1);
	
	fseek(stream2,0L, SEEK_END);
    int size2 = ftell(stream2);
    rewind(stream2); 

	printf("%d %d:: \n",size1,size2);

		
    //struct ret score[size1][size2]; // too big for the stack. need to store on RAM. double malloc. gross.
    
	struct ret **score = (struct ret**) calloc(size2+1, sizeof(struct ret*));

	for ( int i = 0; i < size2; i++ )
	{
		score[i] = (struct ret*) calloc(size1+1, sizeof(struct ret));
	}
	/*
    for(int i = 0; i < size1; ++i)//O(n^2)
	{
		for(int j=0;j<size2;j++)
		{
			printf("%d %c",score[i][j].score,score[i][j].from);
		}
		printf("\n  FUCKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK");
	}
	*/


    char read[2];
    
    int max;
    int ipos, jpos;
   // int j=1,i;
    

    for(int i = 1; i < size1; ++i)//while(fgets(&read[0],2,stream1) != NULL) //
    {	
		//i=1;

		 for(int j=1;j<size2;j++)//while(fgets(&read[1],2,stream2) != NULL)
		{	
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



		//j++;
		rewind(stream2);
    }
    
   printf("%d %d %d \n",max,ipos,jpos);
    
   int check = max;
   char *arr1 = (char*)calloc(MAX(size1,size2)*2, 8);
   int k=0;

   while(check != 0 ){
	
	   switch(score[ipos][jpos].from)
	   {
		   case 'c':
				arr1[k] = 'c';
				ipos--;
				jpos--;
				break;
		   case 'u':
				arr1[k] = 'u';
				ipos--;
				break;
		   case 'l':
				arr1[k] = 'l';
				jpos--;
				break;
		   default:
				break;
		   }
		   
	   
	   check = score[ipos][jpos].score;
	   k++;
   }
   
    //print checks
    
    /*
    for(int i = 0; i <size1; i++)
    {
		for(int j=0;j<size2;j++)
		{
			printf("%c %d ", score[j][i].from,score[j][i].score);
			
		}
		printf("\n");
    }
   */


   for(int i=0;i<220 || &arr1[i] == 0;i++){
	   printf("%c  ",arr1[i]);
   }
   printf("\n");
   
   
   
   
   
    free(arr1);
    
    for ( int i = 0; i < size1; i++ )
	{
		free(score[i]);
	}

	free(score);
	fclose(stream1);
	fclose(stream2);
	
	
	return 0;
}

