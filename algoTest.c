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

int maxScore(int ij,int ji, int i1j1){
	int score;
	i1j1 = i1j1 - 3;
	ij= ij-2;
	ji=ji-2;
	//or 0
	score = MAX(i1j1,MAX(ij,MAX(ji,0)));
	
	
	
	return score;
}

int main(int argc, char **argv)
{
	
	//char *nuc1 = argv[1];
	//char *nuc2 = argv[2]; 

	FILE *stream1;
	FILE *stream2;
	stream1 = fopen("test3","r");
	stream2 = fopen("test4", "r");

    int size1 =50;//= strlen(nuc1);
    int size2 = 50;//= strlen(nuc2); 

    //arr1 = (int*) calloc(size1, sizeof(int));//dyamically allocated array
    //arr2 = (int*) calloc(size2, sizeof(int));//arrays which store input strings
    
    int score[size1][size2];
    
    for(int i = 0; i < size1; ++i)
    {
		score[i][0] = 0;
	}
	for(int i=0;i<size2;i++)
	{
		score[0][i]=0;
	}
    
   
    char read[2];
   /* 
    if(arr1 == NULL || arr2==NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    */
    for(int i = 1; i < size1; ++i)
    {
		for(int j=1;j<size2;j++)
		{
			fgets(&read[0],2,stream1);
			fgets(&read[1],2,stream2);
			
			if(read[0]==read[1]){

				score[i][j] = score[i-1][j-1] + 3;
			}
			else{
				score[i][j]=maxScore(score[i-1][j],score[i][j-1],score[i-1][j-1]);
			}
		}
    }
    
    for(int i = 0; i < size1; ++i)
    {
		for(int j=0;j<size2;j++)
		{
			printf("%d",score[j][i]);
		}
		printf("\n");
    }
    
    //free(arr1);
    //free(arr2);
	//free(score);
	
	return 0;
}

