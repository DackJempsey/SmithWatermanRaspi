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


int main(int argc, char **argv)
{
	
	char *nuc1 = argv[1];
	char *nuc2 = argv[2]; 

	FILE *stream1;
	FILE *stream2;
	stream1 = fopen("test3","r");
	stream2 = fopen("test3", "r");

    int size1 =50;//= strlen(nuc1);
    int size2 = 50;//= strlen(nuc2); 

    //arr1 = (int*) calloc(size1, sizeof(int));//dyamically allocated array
    //arr2 = (int*) calloc(size2, sizeof(int));//arrays which store input strings
    
    int score[size1][size2];
    char read[2];
   /* 
    if(arr1 == NULL || arr2==NULL)
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    */
    for(int i = 0; i < size1; ++i)
    {
		for(int j=0;j<size2;j++)
		{
			fgets(&read[0],1,stream1);
			fgets(&read[1],1,stream2);
			
			if(read[0]==read[1]){
				score[i][j] = 0;
			}
			else{
				score[i][j]=-1;
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

	
	return 0;
}

